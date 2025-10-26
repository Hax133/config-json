#include "link-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{
using json = nlohmann::json;

std::shared_ptr<P2pQueueJson>
LinkJsonHelper::BuildP2pQueue(const json& data)
{
    if (!data.is_object())
        return nullptr;

    auto queue = std::make_shared<P2pQueueJson>();
    queue->SetType(data.value("type", ""));
    queue->SetMode(data.value("mode", ""));
    queue->SetMaxPackets(data.value<uint32_t>("maxPackets", 0));
    return queue;
}

std::shared_ptr<CsmaQueueJson>
LinkJsonHelper::BuildCsmaQueue(const json& data)
{
    if (!data.is_object())
        return nullptr;

    auto queue = std::make_shared<CsmaQueueJson>();
    queue->SetType(data.value("type", ""));
    queue->SetMode(data.value("mode", ""));
    queue->SetMaxPackets(data.value<uint32_t>("maxPackets", 0));
    return queue;
}

// ====== PHY ======
std::shared_ptr<WifiPhyJson>
LinkJsonHelper::BuildWifiPhy(const json& jphy)
{
    auto phy = std::make_shared<WifiPhyJson>();
    phy->SetTxPowerStart(jphy.value("txPowerStart", 0.0));
    phy->SetTxPowerEnd(jphy.value("txPowerEnd", 0.0));
    phy->SetRxSensitivity(jphy.value("rxSensitivity", 0.0));
    phy->SetCcaEdThreshold(jphy.value("ccaEdThreshold", 0.0));
    return phy;
}

// ====== MAC ======
std::shared_ptr<WifiMacJson>
LinkJsonHelper::BuildWifiMac(const json& jmac)
{
    auto mac = std::make_shared<WifiMacJson>();
    mac->SetType(jmac.value("type", ""));
    mac->SetSsid(jmac.value("ssid", ""));
    mac->SetBeaconInterval(jmac.value("beaconInterval", ""));
    mac->SetActiveProbing(jmac.value("activeProbing", false));
    return mac;
}

// ====== MANAGER ======
std::shared_ptr<WifiManagerJson>
LinkJsonHelper::BuildWifiManager(const json& jm)
{
    auto manager = std::make_shared<WifiManagerJson>();
    manager->SetType(jm.value("type", ""));
    manager->SetDataMode(jm.value("dataMode", ""));
    manager->SetControlMode(jm.value("controlMode", ""));
    return manager;
}

// ====== WIFICHANNEL ======
std::shared_ptr<WifiChannelJson>
LinkJsonHelper::BuildWifiChannel(const json& jch)
{
    auto channel = std::make_shared<WifiChannelJson>();
    channel->SetType(jch.value("type", ""));
    channel->SetPropagationDelay(jch.value("propagationDelay", ""));
    channel->SetPropagationLoss(jch.value("propagationLoss", ""));
    return channel;
}

std::shared_ptr<WifiNetDeviceJson>
LinkJsonHelper::BuildWifiNetDevice(const json& data, uint32_t linkId)
{
    auto wifiDev = std::make_shared<WifiNetDeviceJson>();
    wifiDev->SetNetDeviceId(NetDeviceIdJson{data.value<uint32_t>("nodeId", 0), linkId});
    wifiDev->SetType("wifiNetDevice");
    wifiDev->SetWifiPhy(BuildWifiPhy(data.value("wifiPhy", json::object())));
    wifiDev->SetWifiMac(BuildWifiMac(data.value("wifiMac", json::object())));
    return wifiDev;
}

std::shared_ptr<CsmaNetDeviceJson>
LinkJsonHelper::BuildCsmaNetDevice(const json& data, uint32_t linkId)
{
    auto wifiDev = std::make_shared<CsmaNetDeviceJson>();
    wifiDev->SetNetDeviceId(NetDeviceIdJson{data.value<uint32_t>("nodeId", 0), linkId});
    wifiDev->SetType("csmaNetDevice");
    return wifiDev;
}

std::shared_ptr<P2pNetDeviceJson>
LinkJsonHelper::BuildP2pNetDevice(const json& data, uint32_t linkId)
{
    auto wifiDev = std::make_shared<P2pNetDeviceJson>();
    wifiDev->SetNetDeviceId(NetDeviceIdJson{data.value<uint32_t>("nodeId", 0), linkId});
    wifiDev->SetType("p2pNetDevice");
    return wifiDev;
}

/** ---------------------- P2P ---------------------- */
std::shared_ptr<P2pLinkJson>
LinkJsonHelper::BuildP2pLink(const json& data)
{
    auto p2pLink = std::make_shared<P2pLinkJson>();
    p2pLink->SetLinkId(data.value<uint32_t>("linkId", 0));
    p2pLink->SetType("p2p");
    std::vector<std::shared_ptr<NetDeviceJson>> netDevices;
    for (const auto& entry : data.value("netDevices", json::array()))
    {
        netDevices.push_back(BuildP2pNetDevice(entry, data.value<uint32_t>("linkId", 0)));
    }
    p2pLink->SetNetDevices(netDevices);
    p2pLink->SetDataRate(data.value("dataRate", ""));
    p2pLink->SetDelay(data.value("delay", ""));
    p2pLink->SetMtu(data.value<uint32_t>("mtu", 0));
    p2pLink->SetInterframeGap(data.value("interframeGap", ""));
    p2pLink->SetQueue(BuildP2pQueue(data.value("queue", json::object())));
    return p2pLink;
}

/** ---------------------- WIFI ---------------------- */
std::shared_ptr<WifiLinkJson>
LinkJsonHelper::BuildWifiLink(const json& data)
{
    auto wifiLink = std::make_shared<WifiLinkJson>();

    wifiLink->SetLinkId(data.value<uint32_t>("linkId", 0));
    wifiLink->SetType("wifi");
    std::vector<std::shared_ptr<NetDeviceJson>> netDevices;
    for (const auto& entry : data.value("netDevices", json::array()))
    {
        netDevices.push_back(BuildWifiNetDevice(entry, data.value<uint32_t>("linkId", 0)));
    }
    wifiLink->SetNetDevices(netDevices);
    wifiLink->SetStandard(data.value("wifiStandard", ""));
    wifiLink->SetChannelSettings(data.value("channelSettings", ""));
    wifiLink->SetErrorRateModel(data.value("errorRateModel", ""));
    wifiLink->SetQosSupported(data.value("qosSupported", false));
    wifiLink->SetWifiManager(BuildWifiManager(data.value("wifiManager", json::object())));
    wifiLink->SetWifiChannel(BuildWifiChannel(data.value("wifiChannel", json::object())));
    return wifiLink;
}

/** ---------------------- CSMA ---------------------- */

std::shared_ptr<CsmaLinkJson>
LinkJsonHelper::BuildCsmaLink(const json& data)
{
    auto csmaLink = std::make_shared<CsmaLinkJson>();
    csmaLink->SetLinkId(data.value<uint32_t>("linkId", 0));
    csmaLink->SetType("csma");
    std::vector<std::shared_ptr<NetDeviceJson>> netDevices;
    for (const auto& entry : data.value("netDevices", json::array()))
    {
        netDevices.push_back(BuildCsmaNetDevice(entry, data.value<uint32_t>("linkId", 0)));
    }
    csmaLink->SetNetDevices(netDevices);
    csmaLink->SetDataRate(data.value("dataRate", ""));
    csmaLink->SetDelay(data.value("delay", ""));
    csmaLink->SetMtu(data.value<uint32_t>("mtu", 0));
    csmaLink->SetInterframeGap(data.value("interframeGap", ""));
    csmaLink->SetQueue(BuildCsmaQueue(data.value("queue", json::object())));
    return csmaLink;
}

std::shared_ptr<LinkJson>
LinkJsonHelper::Build(const json& data)
{
    uint32_t linkId = data.value<uint32_t>("linkId", 0);
    std::string type = data.value("type", "");
    // === 选择对应类型 ===
    if (type == "p2p")
    {
        return BuildP2pLink(data);
    }
    else if (type == "csma")
    {
        return BuildCsmaLink(data);
    }
    else if (type == "wifi")
    {
        return BuildWifiLink(data);
    }
    std::cerr << "Unknown link type: " << type << " for linkId " << linkId << std::endl;
    return nullptr;
}

} // namespace ns3
