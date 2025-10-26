void
DefaultSink(Ptr<PcapFileWrapper> file, Ptr<const Packet> packet)
{
    if (!file || !packet)
    {
        return;
    }
    // 写入当前仿真时间与包内容
    file->Write(Simulator::Now(), packet);
}

void
WifiPcapSink(Ptr<PcapFileWrapper> file,
             Ptr<const Packet> packet,
             uint16_t channelFreqMhz,
             WifiTxVector txVector,
             MpduInfo mpduInfo,
             SignalNoiseDbm signalNoise,
             uint16_t staId)
{
    if (!file || !packet)
    {
        return;
    }
    file->Write(Simulator::Now(), packet);
}

void
EnablePcapOnDeviceAuto(Ptr<NetDevice> dev, const std::string& prefix, bool promiscuous = true)
{
    if (!dev)
    {
        return;
    }

    PcapHelper pcapHelper;
    std::string filename = pcapHelper.GetFilenameFromDevice(prefix, dev);

    // === CSMA 设备 ===
    if (dev->GetObject<CsmaNetDevice>())
    {
        Ptr<PcapFileWrapper> file =
            pcapHelper.CreateFile(filename, std::ios::out, PcapHelper::DLT_EN10MB);

        std::string traceName = promiscuous ? "PromiscSniffer" : "Sniffer";
        dev->TraceConnectWithoutContext(traceName, MakeBoundCallback(&DefaultSink, file));

        return;
    }

    // === Point-to-Point 设备 ===
    if (dev->GetObject<PointToPointNetDevice>())
    {
        Ptr<PcapFileWrapper> file =
            pcapHelper.CreateFile(filename, std::ios::out, PcapHelper::DLT_PPP);

        std::string traceName = "PromiscSniffer";
        dev->TraceConnectWithoutContext(traceName, MakeBoundCallback(&DefaultSink, file));

        return;
    }

    // ===  Wi-Fi 设备 ===
    if (dev->GetObject<WifiNetDevice>())
    {
        Ptr<WifiNetDevice> wifiDev = dev->GetObject<WifiNetDevice>();
        Ptr<WifiPhy> phy = wifiDev->GetPhy();

        Ptr<PcapFileWrapper> file =
            pcapHelper.CreateFile(filename, std::ios::out, PcapHelper::DLT_IEEE802_11);

        // PHY 层抓包点
        phy->TraceConnectWithoutContext("MonitorSnifferRx", MakeBoundCallback(&WifiPcapSink, file));

        return;
    }
}

void
EnablePcapOnChannel(Ptr<Channel> channel, const std::string& prefix, bool promiscuous = true)
{
    if (!channel)
    {
        return;
    }

    for (uint32_t i = 0; i < channel->GetNDevices(); ++i)
    {
        Ptr<NetDevice> dev = channel->GetDevice(i);
        EnablePcapOnDeviceAuto(dev, prefix, promiscuous);
    }
}

void
EnableLinkPcapByIds(const std::vector<uint32_t>& linkIdsToTrace,
                    const std::map<uint32_t, std::map<uint32_t, Ptr<NetDevice>>>& m_netDevices,
                    const std::string& prefix,
                    bool promiscuous = true)
{
    for (uint32_t linkId : linkIdsToTrace)
    {
        Ptr<NetDevice> sampleDev = nullptr;
        // ===在所有节点中查找该 linkId 的任意设备 ===
        for (const auto& [nodeId, linkMap] : m_netDevices)
        {
            auto it = linkMap.find(linkId);
            if (it != linkMap.end() && it->second)
            {
                sampleDev = it->second;
                break;
            }
        }
        if (!sampleDev)
        {
            continue;
        }
        // ===获取 Channel 并启用 PCAP ===
        Ptr<Channel> channel = sampleDev->GetChannel();
        if (!channel)
        {
            continue;
        }
        std::string filename = prefix + "-link" + std::to_string(linkId);
        EnablePcapOnChannel(channel, filename, promiscuous);
    }
}