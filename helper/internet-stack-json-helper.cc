#include "internet-stack-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

std::shared_ptr<InternetStackJson>
InternetStackJsonHelper::Build(const json& j)
{
    auto internet = std::make_shared<InternetStackJson>();
    if (j.contains("ipv4"))
    {
        internet->SetIpv4(BuildIpv4(j["ipv4"]));
    }

    if (j.contains("ipv6"))
    {
        internet->SetIpv6(BuildIpv6(j["ipv6"]));
    }

    if (j.contains("tcp"))
    {
        internet->SetTcp(BuildTcp(j["tcp"]));
    }

    if (j.contains("udp"))
    {
        internet->SetUdp(BuildUdp(j["udp"]));
    }
    internet->SetEnableGlobalRouting(j.value("enableGlobalRouting", false));
    return internet;
}

/* =================Ipv4 PART============================= */
std::shared_ptr<Ipv4L3ProtocolJson>
InternetStackJsonHelper::BuildIpv4(const json& entry)
{
    auto ipv4 = std::make_shared<Ipv4L3ProtocolJson>();
    ipv4->SetDefaultTtl(entry.value("defaultTtl", 64));
    ipv4->SetIpForward(entry.value("ipForward", false));
    ipv4->SetWeakEsModel(entry.value("weakEsModel", false));
    ipv4->SetSendIcmpRedirect(entry.value("sendIcmpRedirect", false));
    ipv4->SetEnableMtuDiscovery(entry.value("enableMtuDiscovery", false));
    ipv4->SetFragmentExpirationTimeout(entry.value("fragmentExpirationTimeout", ""));
    ipv4->SetMtuDiscoverTimeout(entry.value("mtuDiscoverTimeout", ""));
    ipv4->SetRouteCacheTimeout(entry.value("routeCacheTimeout", ""));
    ipv4->SetEnableChecksum(entry.value("enableChecksum", false));
    return ipv4;
}

/* =================Ipv6 PART============================= */
std::shared_ptr<Ipv6L3ProtocolJson>
InternetStackJsonHelper::BuildIpv6(const json& entry)
{
    auto ipv6 = std::make_shared<Ipv6L3ProtocolJson>();
    ipv6->SetDefaultTtl(entry.value("defaultTtl", 64));
    ipv6->SetIpForward(entry.value("ipForward", false));
    ipv6->SetSendIcmpRedirect(entry.value("sendIcmpv6Redirect", false));
    ipv6->SetEnableMtuDiscovery(entry.value("enableMtuDiscovery", false));
    ipv6->SetFragmentExpirationTimeout(entry.value("fragmentExpirationTimeout", ""));
    ipv6->SetMtuDiscoverTimeout(entry.value("mtuDiscoverTimeout", ""));
    ipv6->SetRouteCacheTimeout(entry.value("routeCacheTimeout", ""));
    ipv6->SetEnableChecksum(entry.value("enableChecksum", false));

    return ipv6;
}

/* =================TCP PART============================= */

std::shared_ptr<TcpL4ProtocolJson>
InternetStackJsonHelper::BuildTcp(const json& entry)
{
    auto tcp = std::make_shared<TcpL4ProtocolJson>();
    tcp->SetSendBufferSize(entry.value("sendBufferSize", 0));
    tcp->SetReceiveBufferSize(entry.value("receiveBufferSize", 0));
    tcp->SetVariant(entry.value("variant", ""));
    tcp->SetInitialCwnd(entry.value("initialCwnd", 0));
    tcp->SetSegmentSize(entry.value("segmentSize", 0));
    tcp->SetMaxCwnd(entry.value("maxCwnd", 0));
    tcp->SetSlowStartThreshold(entry.value("slowStartThreshold", 0));
    tcp->SetRetransmitTimeout(entry.value("retransmitTimeout", 0));
    tcp->SetEnableSack(entry.value("enableSack", false));
    tcp->SetEnableDelayedAck(entry.value("enableDelayedAck", false));
    tcp->SetEnableNagle(entry.value("enableNagle", false));
    tcp->SetEnableKeepAlive(entry.value("enableKeepAlive", false));
    return tcp;
}

/* =================UDP PART======================== */

std::shared_ptr<UdpL4ProtocolJson>
InternetStackJsonHelper::BuildUdp(const json& entry)
{
    auto udp = std::make_shared<UdpL4ProtocolJson>();
    udp->SetSendBufferSize(entry.value("sendBufferSize", 0));
    udp->SetReceiveBufferSize(entry.value("receiveBufferSize", 0));
    udp->SetPacketSize(entry.value("packetSize", 0));
    udp->SetDataRate(entry.value("dataRate", ""));
    udp->SetEnableChecksum(entry.value("enableChecksum", false));
    udp->SetEnableBroadcast(entry.value("enableBroadcast", false));
    udp->SetEnableMulticast(entry.value("enableMulticast", false));
    return udp;
}

} // namespace ns3
