#include "simulator-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{
WifiStandard
ParseWifiStandard(const std::string& str)
{
    if (str == "WIFI_STANDARD_80211a")
        return WIFI_STANDARD_80211a;
    if (str == "WIFI_STANDARD_80211b")
        return WIFI_STANDARD_80211b;
    if (str == "WIFI_STANDARD_80211g")
        return WIFI_STANDARD_80211g;
    if (str == "WIFI_STANDARD_80211n")
        return WIFI_STANDARD_80211n;
    if (str == "WIFI_STANDARD_80211ac")
        return WIFI_STANDARD_80211ac;
    if (str == "WIFI_STANDARD_80211ax")
        return WIFI_STANDARD_80211ax;
    if (str == "WIFI_STANDARD_80211be")
        return WIFI_STANDARD_80211be;
    return WIFI_STANDARD_80211a; // fallback, won't reach
}

void
SimulatorJsonHelper::InstallLink(std::shared_ptr<LinkJson> baseLink)
{
    std::string type = baseLink->GetType();
    uint32_t linkId = baseLink->GetLinkId();
    // =============================
    //  CSMA 链路
    // =============================
    if (type == "csma")
    {
        auto link = std::dynamic_pointer_cast<CsmaLinkJson>(baseLink);
        CsmaHelper csma;
        csma.SetChannelAttribute("DataRate", StringValue(link->GetDataRate()));
        csma.SetChannelAttribute("Delay", StringValue(link->GetDelay()));
        csma.SetDeviceAttribute("Mtu", UintegerValue(link->GetMtu()));
        //"InterframeGap"没能找到ns3的实现
        // csma.SetChannelAttribute("InterframeGap", StringValue(link->GetInterframeGap()));
        // 从 ns-3.35 开始，CSMA / PointToPoint / Wifi 的Queue 全部迁移到 QueueDisc 模型
        // Mode/MaxPacket等Queue参数修改需要额外配置QueueDisc
        csma.SetQueue(link->GetQueue()->GetType());

        NodeContainer nodes;
        std::vector<uint32_t> nodeIds;
        for (auto& devJson : link->GetNetDevices())
        {
            uint32_t nodeId = devJson->GetNetDeviceId().nodeId;
            nodes.Add(NodeList::GetNode(nodeId));
        }
        auto devices = csma.Install(nodes);

        for (uint32_t i = 0; i < devices.GetN(); ++i)
        {
            Ptr<NetDevice> dev = devices.Get(i);
            uint32_t nodeId = dev->GetNode()->GetId();
            m_netDevices[nodeId][linkId] = dev;
        }
    }

    // =============================
    //  点对点链路
    // =============================
    else if (type == "p2p")
    {
        auto link = std::dynamic_pointer_cast<P2pLinkJson>(baseLink);

        PointToPointHelper p2p;
        p2p.SetDeviceAttribute("DataRate", StringValue(link->GetDataRate()));
        p2p.SetChannelAttribute("Delay", StringValue(link->GetDelay()));
        p2p.SetDeviceAttribute("Mtu", UintegerValue(link->GetMtu()));
        //"InterframeGap"没能找到ns3的实现
        // p2p.SetChannelAttribute("InterframeGap", StringValue(link->GetInterframeGap()));
        // 从 ns-3.35 开始，CSMA / PointToPoint / Wifi 的Queue 全部迁移到 QueueDisc 模型
        // Mode/MaxPacket等Queue参数修改需要额外配置QueueDisc
        p2p.SetQueue(link->GetQueue()->GetType());

        NodeContainer nodes;
        std::vector<uint32_t> nodeIds;
        for (auto& devJson : link->GetNetDevices())
        {
            uint32_t nodeId = devJson->GetNetDeviceId().nodeId;
            nodes.Add(NodeList::GetNode(nodeId));
        }
        auto devices = p2p.Install(nodes);
        for (uint32_t i = 0; i < devices.GetN(); ++i)
        {
            Ptr<NetDevice> dev = devices.Get(i);
            uint32_t nodeId = dev->GetNode()->GetId();
            m_netDevices[nodeId][linkId] = dev;
        }
    }

    // =============================
    //  WiFi 链路
    // =============================
    else if (type == "wifi")
    {
        auto link = std::dynamic_pointer_cast<WifiLinkJson>(baseLink);
        WifiHelper wifi;
        wifi.SetStandard(ParseWifiStandard(link->GetStandard()));
        wifi.SetRemoteStationManager(link->GetWifiManager()->GetType(),
                                     "DataMode",
                                     StringValue(link->GetWifiManager()->GetDataMode()),
                                     "ControlMode",
                                     StringValue(link->GetWifiManager()->GetControlMode()));
        // === WifiChannel类型 ===
        const auto& wifiChannelJson = link->GetWifiChannel();
        const auto& wifiChannelType = wifiChannelJson->GetType();
        if (wifiChannelType == "YansWifiChannel")
        {
            YansWifiChannelHelper channel;
            channel.SetPropagationDelay(wifiChannelJson->GetPropagationDelay());
            channel.AddPropagationLoss(wifiChannelJson->GetPropagationLoss());
            YansWifiPhyHelper phy;
            phy.SetChannel(channel.Create());
            phy.SetErrorRateModel(link->GetErrorRateModel());
            phy.Set("ChannelSettings", StringValue(link->GetChannelSettings()));
            for (const auto& d : link->GetNetDevices())
            {
                auto devJson = std::dynamic_pointer_cast<WifiNetDeviceJson>(d);
                auto node = NodeList::GetNode(devJson->GetNetDeviceId().nodeId);
                auto macJson = devJson->GetWifiMac();
                auto phyJson = devJson->GetWifiPhy();
                phy.Set("TxPowerStart", DoubleValue(phyJson->GetTxPowerStart()));
                phy.Set("TxPowerEnd", DoubleValue(phyJson->GetTxPowerEnd()));
                phy.Set("RxSensitivity", DoubleValue(phyJson->GetRxSensitivity()));
                phy.Set("CcaEdThreshold", DoubleValue(phyJson->GetCcaEdThreshold()));
                WifiMacHelper mac;
                if (!link->GetQosSupported())
                {
                    if (macJson->GetType() == "StaWifiMac")
                    {
                        mac.SetType("ns3::StaWifiMac",
                                    "Ssid",
                                    SsidValue(Ssid(macJson->GetSsid())),
                                    "ActiveProbing",
                                    BooleanValue(macJson->GetActiveProbing()));
                    }
                    else if (macJson->GetType() == "ApWifiMac")
                    {
                        mac.SetType("ns3::ApWifiMac",
                                    "Ssid",
                                    SsidValue(Ssid(macJson->GetSsid())),
                                    "BeaconInterval",
                                    TimeValue(Time(macJson->GetBeaconInterval())));
                    }
                    else if (macJson->GetType() == "AdhocWifiMac")
                    {
                        mac.SetType("ns3::AdhocWifiMac",
                                    "Ssid",
                                    SsidValue(Ssid(macJson->GetSsid())));
                    }
                }
                // else{} 启用qos
                auto devices = wifi.Install(phy, mac, node);
                uint32_t nodeId = node->GetId();
                m_netDevices[nodeId][linkId] = devices.Get(0);
                Ptr<WifiPhy> phy = DynamicCast<WifiNetDevice>(devices.Get(0))->GetPhy();
                Ptr<Channel> chan = phy->GetChannel();
            }
        }
        else if (wifiChannelType == "SpectrumWifiChannel")
        {
            SpectrumChannelHelper channel;
            // 默认多模型
            channel.SetChannel("ns3::MultiModelSpectrumChannel");
            channel.SetPropagationDelay(wifiChannelJson->GetPropagationDelay());
            channel.AddPropagationLoss(wifiChannelJson->GetPropagationLoss());
            SpectrumWifiPhyHelper phy;
            phy.SetChannel(channel.Create());
            phy.SetErrorRateModel(link->GetErrorRateModel());
            phy.Set("ChannelSettings", StringValue(link->GetChannelSettings()));
            for (const auto& d : link->GetNetDevices())
            {
                auto devJson = std::dynamic_pointer_cast<WifiNetDeviceJson>(d);
                auto node = NodeList::GetNode(devJson->GetNetDeviceId().nodeId);
                auto macJson = devJson->GetWifiMac();
                auto phyJson = devJson->GetWifiPhy();
                phy.Set("TxPowerStart", DoubleValue(phyJson->GetTxPowerStart()));
                phy.Set("TxPowerEnd", DoubleValue(phyJson->GetTxPowerEnd()));
                phy.Set("RxSensitivity", DoubleValue(phyJson->GetRxSensitivity()));
                phy.Set("CcaEdThreshold", DoubleValue(phyJson->GetCcaEdThreshold()));
                WifiMacHelper mac;
                if (!link->GetQosSupported())
                {
                    if (macJson->GetType() == "StaWifiMac")
                    {
                        mac.SetType("ns3::StaWifiMac",
                                    "Ssid",
                                    SsidValue(Ssid(macJson->GetSsid())),
                                    "ActiveProbing",
                                    BooleanValue(macJson->GetActiveProbing()));
                    }
                    else if (macJson->GetType() == "ApWifiMac")
                    {
                        mac.SetType("ns3::ApWifiMac",
                                    "Ssid",
                                    SsidValue(Ssid(macJson->GetSsid())),
                                    "BeaconInterval",
                                    TimeValue(Time(macJson->GetBeaconInterval())));
                    }
                    else if (macJson->GetType() == "AdhocWifiMac")
                    {
                        mac.SetType("ns3::AdhocWifiMac",
                                    "Ssid",
                                    SsidValue(Ssid(macJson->GetSsid())));
                    }
                }
                // else{} 启用qos
                auto devices = wifi.Install(phy, mac, node);
                uint32_t nodeId = node->GetId();
                m_netDevices[nodeId][linkId] = devices.Get(0);
            }
        }
    }
}

void
SimulatorJsonHelper::InstallRole(std::shared_ptr<NodeJson> nodeJson)
{
    auto nodeId = nodeJson->GetNodeId();
    auto node = NodeList::GetNode(nodeId);
    auto role = nodeJson->GetRole();
    if (role == "switch")
    {
        NetDeviceContainer csmaDevices;
        // === 遍历该节点的所有 NetDevice ===
        for (auto& [linkId, dev] : m_netDevices[nodeId])
        {
            if (dev == nullptr)
            {
                continue;
            }

            // 判断设备类型
            if (dev->GetInstanceTypeId() == CsmaNetDevice::GetTypeId())
            {
                csmaDevices.Add(dev);
            }
        }
        if (csmaDevices.GetN() >= 2)
        {
            BridgeHelper bridge;
            bridge.Install(node, csmaDevices);
        }
        // === 关闭 IPv4 接口从1开始 ===
        Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
        if (ipv4 != nullptr)
        {
            uint32_t nIfaces = ipv4->GetNInterfaces();
            for (uint32_t i = 1; i < nIfaces; ++i)
            {
                ipv4->SetDown(i); // 关闭该接口
            }
        }
        // === 关闭 IPv6 接口（如果启用了 IPv6） ===
        Ptr<Ipv6> ipv6 = node->GetObject<Ipv6>();
        if (ipv6 != nullptr)
        {
            uint32_t nIfaces = ipv6->GetNInterfaces();
            for (uint32_t i = 1; i < nIfaces; ++i)
            {
                ipv6->SetDown(i);
            }
        }
    }
}

void
SimulatorJsonHelper::InstallInternet(std::shared_ptr<InternetStackJson> internet,
                                     std::vector<std::shared_ptr<NodeJson>> nodeList)
{
    // === ipv4/6(pass) tcp/udp(pass) routinglist默认参数修改 ===
    InternetStackHelper stack;
    if (internet->IsEnableGlobalRouting())
    {
        stack.SetRoutingHelper(Ipv4GlobalRoutingHelper());
        stack.InstallAll();
    }
    else
    {
        for (const auto& nodeJson : nodeList)
        {
            auto nodeId = nodeJson->GetNodeId();
            Ipv4ListRoutingHelper ipv4list;
            for (auto& routeConf : nodeJson->GetIpv4RoutingProtocols())
            {
                std::string type = routeConf->GetType();
                uint32_t priority = routeConf->GetPriority();
                if (type == "Static")
                {
                    Ipv4StaticRoutingHelper ipv4StaticRoutingHelper;
                    ipv4list.Add(ipv4StaticRoutingHelper, priority);
                }
                else if (type == "Olsr")
                {
                    OlsrHelper olsrHelper;
                    auto olsrRouting =
                        std::dynamic_pointer_cast<OlsrRoutingProtocolJson>(routeConf);
                    olsrHelper.Set("HelloInterval",
                                   TimeValue(Time(olsrRouting->GetHelloInterval())));
                    olsrHelper.Set("TcInterval", TimeValue(Time(olsrRouting->GetTcInterval())));
                    olsrHelper.Set("HnaInterval", TimeValue(Time(olsrRouting->GetHnaInterval())));
                    olsrHelper.Set("Willingness", EnumValue(olsrRouting->GetWillingness()));
                    ipv4list.Add(olsrHelper, priority);
                }
            }
            Ipv6ListRoutingHelper ipv6list;
            for (auto& routeConf : nodeJson->GetIpv6RoutingProtocols())
            {
                std::string type = routeConf->GetType();
                int priority = routeConf->GetPriority();
                if (type == "Static")
                {
                    Ipv6StaticRoutingHelper ipv6StaticRoutingHelper;
                    ipv6list.Add(ipv6StaticRoutingHelper, priority);
                }
            }
            stack.SetRoutingHelper(ipv4list);
            // stack.SetRoutingHelper(ipv6list);
            stack.Install(NodeList::GetNode(nodeId));
        }
    }
}

void
SimulatorJsonHelper::InstallIpv4Network(std::shared_ptr<Ipv4NetworkJson> ipv4Network)
{
    auto fixeds = ipv4Network->GetFixed();
    auto subnet = ipv4Network->GetSubnet().c_str();
    auto mask = ipv4Network->GetMask().c_str();
    auto base = ipv4Network->GetBase().c_str();

    // 遍历 fixed 地址，找最大主机部分
    for (const auto& f : fixeds)
    {
        auto devId = f->GetNetDeviceId();
        Ptr<Node> node = NodeList::GetNode(devId.nodeId);
        Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
        int32_t interface = ipv4->AddInterface(m_netDevices[devId.nodeId][devId.linkId]);
        // 指定 IP 地址和掩码
        Ipv4InterfaceAddress ipv4Addr = Ipv4InterfaceAddress(f->GetIpv4Address().c_str(), mask);
        ipv4->AddAddress(interface, ipv4Addr);
        ipv4->SetUp(interface);
    }
    Ipv4AddressHelper address;
    address.SetBase(subnet, mask, base);
    NetDeviceContainer devs;
    for (const auto& devId : ipv4Network->GetNetDeviceIds())
    {
        devs.Add(m_netDevices[devId.nodeId][devId.linkId]);
    }
    address.Assign(devs);
}

void
SimulatorJsonHelper::InstallIpv6Network(std::shared_ptr<Ipv6NetworkJson> ipv6Network)
{
    auto fixeds = ipv6Network->GetFixed();
    auto subnet = ipv6Network->GetSubnet().c_str();
    auto prefixLength = ipv6Network->GetPrefixLength();
    auto base = ipv6Network->GetBase().c_str();

    // === 遍历 fixed 地址，找出最大主机部分 ===
    for (const auto& f : fixeds)
    {
        auto devId = f->GetNetDeviceId();
        Ptr<Node> node = NodeList::GetNode(devId.nodeId);
        Ptr<Ipv6> ipv6 = node->GetObject<Ipv6>();
        int32_t interface = ipv6->AddInterface(m_netDevices[devId.nodeId][devId.linkId]);
        // 指定 IPv6 地址和前缀
        Ipv6InterfaceAddress ipv6Addr(Ipv6Address(f->GetIpv6Address().c_str()), prefixLength);
        ipv6->AddAddress(interface, ipv6Addr);
        ipv6->SetUp(interface);
    }
    Ipv6AddressHelper address;
    address.SetBase(subnet, prefixLength, base);
    NetDeviceContainer devs;
    for (const auto& devId : ipv6Network->GetNetDeviceIds())
    {
        devs.Add(m_netDevices[devId.nodeId][devId.linkId]);
    }

    address.Assign(devs);
}

void
SimulatorJsonHelper::InstallIpv4Routing(std::shared_ptr<NodeJson> nodeJson)
{
    auto nodeId = nodeJson->GetNodeId();
    auto node = NodeList::GetNode(nodeId);
    // === ipv4 静态路由配置 ===
    auto ipv4RoutingList = nodeJson->GetIpv4RoutingProtocols();
    for (const auto& routing : ipv4RoutingList)
    {
        std::string type = routing->GetType();
        if (type == "Static")
        {
            // --- 静态路由表项 ---
            auto staticRouting = std::dynamic_pointer_cast<Ipv4StaticRoutingProtocolJson>(routing);
            for (const auto& route : staticRouting->GetRoutes())
            {
                std::string network = route.m_ipv4Address;
                std::string mask = route.m_mask;
                std::string nextHop = route.m_nextHop;
                uint32_t nextLinkId = route.m_nextLinkId;
                Ipv4StaticRoutingHelper ipv4StaticRoutingHelper;
                Ptr<Ipv4> ipv4 = node->GetObject<Ipv4>();
                Ptr<Ipv4StaticRouting> staticRouting =
                    ipv4StaticRoutingHelper.GetStaticRouting(ipv4);
                uint32_t nextInterface =
                    ipv4->GetInterfaceForDevice(m_netDevices[nodeId][nextLinkId]);
                staticRouting->AddNetworkRouteTo(network.c_str(),
                                                 mask.c_str(),
                                                 nextHop.c_str(),
                                                 nextInterface);
            }
        }
        else if (type == "Olsr")
        {
            // 添加 HNA 网络
            auto olsrRoutingJson = std::dynamic_pointer_cast<OlsrRoutingProtocolJson>(routing);
            for (const auto& hna : olsrRoutingJson->GetHnaNetworks())
            {
                auto ipv4 = node->GetObject<Ipv4>();
                auto olsrRouting = Ipv4RoutingHelper::GetRouting<olsr::RoutingProtocol>(
                    node->GetObject<Ipv4>()->GetRoutingProtocol());
                if (olsrRouting)
                {
                    olsrRouting->AddHostNetworkAssociation(Ipv4Address(hna.m_network.c_str()),
                                                           Ipv4Mask(hna.m_mask.c_str()));
                }
            }
        }
    }
}

void
SimulatorJsonHelper::InstallIpv6Routing(std::shared_ptr<NodeJson> nodeJson)
{
    auto nodeId = nodeJson->GetNodeId();
    auto node = NodeList::GetNode(nodeId);
    // === ipv6 静态路由配置 ===
    auto ipv6RoutingList = nodeJson->GetIpv6RoutingProtocols();
    for (const auto& routing : ipv6RoutingList)
    {
        std::string type = routing->GetType();
        if (type == "Static")
        {
            // --- 静态路由表项 ---
            auto staticRouting = std::dynamic_pointer_cast<Ipv6StaticRoutingProtocolJson>(routing);
            for (const auto& route : staticRouting->GetRoutes())
            {
                std::string network = route.m_dest;
                uint32_t prefixLength = route.m_prefixLength;
                std::string nextHop = route.m_nextHop;
                uint32_t nextLinkId = route.m_nextLinkId;
                Ipv6StaticRoutingHelper ipv6StaticRoutingHelper;
                Ptr<Ipv6> ipv6 = node->GetObject<Ipv6>();
                Ptr<Ipv6StaticRouting> staticRouting =
                    ipv6StaticRoutingHelper.GetStaticRouting(ipv6);
                uint32_t nextInterface =
                    ipv6->GetInterfaceForDevice(m_netDevices[nodeId][nextLinkId]);
                staticRouting->AddNetworkRouteTo(Ipv6Address(network.c_str()),
                                                 prefixLength,
                                                 Ipv6Address(nextHop.c_str()),
                                                 nextInterface);
            }
        }
    }
}

void
SimulatorJsonHelper::InstallMobility(std::shared_ptr<NodeJson> nodeJson)
{
    auto nodeId = nodeJson->GetNodeId();
    auto node = NodeList::GetNode(nodeId);
    // === 节点移动模型安装 ===
    auto mob = nodeJson->GetMobility();
    if (mob)
    {
        MobilityHelper mobility;
        // === 位置分配器 ===
        auto alloc = mob->GetPositionAllocator();
        if (alloc)
        {
            std::string allocType = alloc->GetType();

            if (allocType == "GridPositionAllocator")
            {
                auto grid = std::dynamic_pointer_cast<GridPositionAllocatorJson>(alloc);
                mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                              "MinX",
                                              DoubleValue(grid->GetMinX()),
                                              "MinY",
                                              DoubleValue(grid->GetMinY()),
                                              "DeltaX",
                                              DoubleValue(grid->GetDeltaX()),
                                              "DeltaY",
                                              DoubleValue(grid->GetDeltaY()),
                                              "GridWidth",
                                              UintegerValue(grid->GetGridWidth()),
                                              "LayoutType",
                                              StringValue(grid->GetLayoutType()));
            }
            else if (allocType == "ListPositionAllocator")
            {
                auto list = std::dynamic_pointer_cast<ListPositionAllocatorJson>(alloc);
                Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator>();
                for (const auto& pos : list->GetPositions())
                {
                    positionAlloc->Add(Vector(pos[0], pos[1], pos[2]));
                }
                mobility.SetPositionAllocator(positionAlloc);
            }
            else if (allocType == "RandomRectanglePositionAllocator")
            {
                auto rect = std::dynamic_pointer_cast<RandomRectanglePositionAllocatorJson>(alloc);
                std::ostringstream xStr, yStr;
                xStr << "ns3::UniformRandomVariable[Min=" << rect->GetXMin()
                     << "|Max=" << rect->GetXMax() << "]";
                yStr << "ns3::UniformRandomVariable[Min=" << rect->GetYMin()
                     << "|Max=" << rect->GetYMax() << "]";
                mobility.SetPositionAllocator("ns3::RandomRectanglePositionAllocator",
                                              "X",
                                              StringValue(xStr.str()),
                                              "Y",
                                              StringValue(yStr.str()));
            }
        }
        if (mob->GetType() == "ns3")
        {
            // === 移动模型 ===
            auto model = mob->GetMobilityModel();
            if (model)
            {
                std::string modelType = model->GetType();

                if (modelType == "ConstantPositionMobilityModel")
                {
                    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
                }
                else if (modelType == "RandomWalk2dMobilityModel")
                {
                    auto walk = std::dynamic_pointer_cast<RandomWalk2dMobilityModelJson>(model);
                    mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                                              "Bounds",
                                              RectangleValue(Rectangle(walk->GetXMin(),
                                                                       walk->GetXMax(),
                                                                       walk->GetYMin(),
                                                                       walk->GetYMax())),
                                              "Distance",
                                              DoubleValue(walk->GetDistance()),
                                              "Speed",
                                              StringValue(walk->GetSpeed()));
                }
            }
        }
        else if (mob->GetType() == "gazebo")
        {
            mobility.SetMobilityModel("ns3::WaypointMobilityModel");
        }
        mobility.Install(node);
    }
}

void
SimulatorJsonHelper::InstallApplications(std::shared_ptr<NodeJson> nodeJson)
{
    auto nodeId = nodeJson->GetNodeId();
    auto node = NodeList::GetNode(nodeId);
    // 暂时只有Inet4/6SocketAddress
    for (auto& appJson : nodeJson->GetApplications())
    {
        std::string type = appJson->GetType();
        auto socket = appJson->GetSocket();
        auto socketType = socket->GetType();
        auto port = socket->GetPort();
        auto start = appJson->GetStartTime();
        auto stop = appJson->GetStopTime();
        Ipv4Address dstIpv4Addr = Ipv4Address::GetAny();
        Ipv6Address dstIpv6Addr = Ipv6Address::GetAny();
        if (!socket->IsAny())
        {
            auto socketNodeId = socket->GetNetDeviceId().nodeId;
            auto socketLinkId = socket->GetNetDeviceId().linkId;
            if (socketType == "ipv4")
            {
                auto ipv4 = NodeList::GetNode(socketNodeId)->GetObject<Ipv4>();
                int32_t interface =
                    ipv4->GetInterfaceForDevice(m_netDevices[socketNodeId][socketLinkId]);
                dstIpv4Addr = ipv4->GetAddress(interface, 0).GetLocal();
            }
            else if (socketType == "ipv6")
            {
                auto ipv6 = NodeList::GetNode(socketNodeId)->GetObject<Ipv6>();
                int32_t interface =
                    ipv6->GetInterfaceForDevice(m_netDevices[socketNodeId][socketLinkId]);
                dstIpv6Addr = ipv6->GetAddress(interface, 0).GetAddress();
            }
        }
        ApplicationContainer app;
        if (type == "onOff")
        {
            auto onOffJson = std::dynamic_pointer_cast<OnOffJson>(appJson);
            if (socketType == "ipv6")
            {
                Inet6SocketAddress dst6(dstIpv6Addr, port);
                OnOffHelper onOff("ns3::UdpSocketFactory", dst6);
                onOff.SetAttribute("DataRate", DataRateValue(DataRate(onOffJson->GetDataRate())));
                onOff.SetAttribute("PacketSize", UintegerValue(onOffJson->GetPacketSize()));
                app = onOff.Install(node);
            }
            else
            {
                InetSocketAddress dst4(dstIpv4Addr, port);
                OnOffHelper onOff("ns3::UdpSocketFactory", dst4);
                onOff.SetAttribute("DataRate", DataRateValue(DataRate(onOffJson->GetDataRate())));
                onOff.SetAttribute("PacketSize", UintegerValue(onOffJson->GetPacketSize()));
                app = onOff.Install(node);
            }
        }

        // ===============================
        // PacketSink 应用（接收端）
        // ===============================
        else if (type == "packetSink")
        {
            auto sinkJson = std::dynamic_pointer_cast<PacketSinkJson>(appJson);
            if (socketType == "ipv6")
            {
                PacketSinkHelper sink(sinkJson->GetProtocol(),
                                      Inet6SocketAddress(dstIpv6Addr, port));
                app = sink.Install(node);
            }
            else
            {
                PacketSinkHelper sink(sinkJson->GetProtocol(),
                                      InetSocketAddress(dstIpv4Addr, port));
                app = sink.Install(node);
            }
        }

        // ===============================
        // UDP Echo Server 应用
        // ===============================
        else if (type == "udpEchoServer")
        {
            auto serverJson = std::dynamic_pointer_cast<UdpEchoServerJson>(appJson);
            UdpEchoServerHelper echoServer(port);
            app = echoServer.Install(node);
        }
        else if (type == "udpEchoClient")
        {
            auto udpEchoClientJson = std::dynamic_pointer_cast<UdpEchoClientJson>(appJson);
            if (socketType == "ipv6")
            {
                UdpEchoClientHelper echoClient(Inet6SocketAddress(dstIpv6Addr, port));
                echoClient.SetAttribute("MaxPackets",
                                        UintegerValue(udpEchoClientJson->GetMaxPackets()));
                echoClient.SetAttribute("Interval",
                                        TimeValue(Time(udpEchoClientJson->GetInterval())));
                echoClient.SetAttribute("PacketSize",
                                        UintegerValue(udpEchoClientJson->GetPacketSize()));
                app = echoClient.Install(node);
            }
            else
            {
                UdpEchoClientHelper echoClient(InetSocketAddress(dstIpv4Addr, port));
                echoClient.SetAttribute("MaxPackets",
                                        UintegerValue(udpEchoClientJson->GetMaxPackets()));
                echoClient.SetAttribute("Interval",
                                        TimeValue(Time(udpEchoClientJson->GetInterval())));
                echoClient.SetAttribute("PacketSize",
                                        UintegerValue(udpEchoClientJson->GetPacketSize()));
                app = echoClient.Install(node);
            }
        }
        app.Start(Time(start));
        app.Stop(Time(stop));
    }
}

void
SimulatorJsonHelper::Install(std::shared_ptr<ConfigJson> config)
{
    auto nodeList = config->GetNodes();
    auto links = config->GetLinks();
    auto internet = config->GetInternetStack();
    auto ipv4Networks = config->GetIpv4Networks();
    auto ipv6Networks = config->GetIpv6Networks();
    // === 节点创建 ===
    for (uint32_t i = 0; i < nodeList.size(); i++)
    {
        CreateObject<Node>();
    }
    // === 链路与 NetDevice 安装 ===
    for (const auto& baseLink : links)
    {
        InstallLink(baseLink);
    }
    // === 配置协议栈和路由协议
    InstallInternet(internet, nodeList);
    // === IPv4 接口配置 ===
    for (const auto& ipv4Network : ipv4Networks)
    {
        InstallIpv4Network(ipv4Network);
    }
    // === IPv6 接口配置 ===
    for (const auto& ipv6Network : ipv6Networks)
    {
        InstallIpv6Network(ipv6Network);
    }
    // === 特殊角色配置 ===
    for (const auto& nodeJson : nodeList)
    {
        InstallRole(nodeJson);
    }
    // === 路由表项添加 ===
    if (internet->IsEnableGlobalRouting())
    {
        Ipv4GlobalRoutingHelper::PopulateRoutingTables();
    }
    else
    {
        for (const auto& nodeJson : nodeList)
        {
            InstallIpv4Routing(nodeJson);
            InstallIpv6Routing(nodeJson);
        }
    }
    // === 移动模型和业务配置 ===
    for (const auto& nodeJson : nodeList)
    {
        InstallMobility(nodeJson);
        InstallApplications(nodeJson);
    }
}

const std::map<uint32_t, std::map<uint32_t, Ptr<NetDevice>>>&
SimulatorJsonHelper::GetNetDevicesMap() const
{
    return m_netDevices;
}

void
SimulatorJsonHelper::DumpNetDevicesMap()
{
    std::cout << "\n================= m_netDevices Map Dump =================\n";
    for (const auto& nodePair : m_netDevices)
    {
        uint32_t nodeId = nodePair.first;
        const auto& linkMap = nodePair.second;
        std::cout << "Node ID " << nodeId << " (" << linkMap.size() << " devices):" << std::endl;

        for (const auto& linkPair : linkMap)
        {
            uint32_t linkId = linkPair.first;
            Ptr<NetDevice> dev = linkPair.second;

            std::cout << "  ├─ Link ID: " << linkId;

            if (dev)
            {
                Ptr<Channel> channel = dev->GetChannel();
                std::string channelType = channel ? channel->GetInstanceTypeId().GetName() : "None";
                std::cout << " | Type: " << dev->GetInstanceTypeId().GetName()
                          << " | Channel: " << channelType;
            }
            else
            {
                std::cout << " |  Device pointer is null!";
            }

            std::cout << std::endl;
        }
    }
    std::cout << "=======================================================\n";
}

void
DefaultSink(Ptr<PcapFileWrapper> file, Ptr<const Packet> packet)
{
    if (!file || !packet)
    {
        return;
    }
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
SimulatorJsonHelper::EnablePcapAuto(const std::string &prefix,
                                    const std::vector<uint32_t> &linkIdsToTrace,
                                    bool promiscuous)
{
    PcapHelper pcapHelper;

    // === 外层遍历所有节点 ===
    for (const auto &[nodeId, linkMap] : m_netDevices)
    {
        // === 内层遍历需要抓取的 linkId ===
        for (uint32_t linkId : linkIdsToTrace)
        {
            auto it = linkMap.find(linkId);
            if (it == linkMap.end() || !it->second)
            {
                continue;
            }

            Ptr<NetDevice> dev = it->second;
            std::cout << "Enable pcap: node " << nodeId
                      << " link " << linkId << std::endl;

            // 每个 NetDevice 独立文件名
            std::string filename = prefix
                                 + "-link" + std::to_string(linkId)
                                 + "-node" + std::to_string(nodeId)
                                 + ".pcap";

            // === CSMA 设备 ===
            if (dev->GetObject<CsmaNetDevice>())
            {
                Ptr<PcapFileWrapper> file =
                    pcapHelper.CreateFile(filename, std::ios::out, PcapHelper::DLT_EN10MB);

                std::string traceName = promiscuous ? "PromiscSniffer" : "Sniffer";
                dev->TraceConnectWithoutContext(traceName,
                                                MakeBoundCallback(&DefaultSink, file));
                continue;
            }

            // === Point-to-Point 设备 ===
            if (dev->GetObject<PointToPointNetDevice>())
            {
                Ptr<PcapFileWrapper> file =
                    pcapHelper.CreateFile(filename, std::ios::out, PcapHelper::DLT_PPP);

                dev->TraceConnectWithoutContext("PromiscSniffer",
                                                MakeBoundCallback(&DefaultSink, file));
                continue;
            }

            // === Wi-Fi 设备 ===
            if (dev->GetObject<WifiNetDevice>())
            {
                Ptr<WifiNetDevice> wifiDev = dev->GetObject<WifiNetDevice>();
                Ptr<WifiPhy> phy = wifiDev->GetPhy();

                Ptr<PcapFileWrapper> file =
                    pcapHelper.CreateFile(filename, std::ios::out, PcapHelper::DLT_IEEE802_11);

                phy->TraceConnectWithoutContext("MonitorSnifferRx",
                                                MakeBoundCallback(&WifiPcapSink, file));
                continue;
            }
        }
    }
}


} // namespace ns3
