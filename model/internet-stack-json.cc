#include "internet-stack-json.h"

namespace ns3
{
// ====== ipv4======

void
Ipv4L3ProtocolJson::SetDefaultTtl(uint32_t t)
{
    m_defaultTtl = t;
}

uint32_t
Ipv4L3ProtocolJson::GetDefaultTtl() const
{
    return m_defaultTtl;
}

void
Ipv4L3ProtocolJson::SetIpForward(bool e)
{
    m_ipForward = e;
}

bool
Ipv4L3ProtocolJson::GetIpForward() const
{
    return m_ipForward;
}

void
Ipv4L3ProtocolJson::SetWeakEsModel(bool e)
{
    m_weakEsModel = e;
}

bool
Ipv4L3ProtocolJson::GetWeakEsModel() const
{
    return m_weakEsModel;
}

void
Ipv4L3ProtocolJson::SetSendIcmpRedirect(bool e)
{
    m_sendIcmpRedirect = e;
}

bool
Ipv4L3ProtocolJson::GetSendIcmpRedirect() const
{
    return m_sendIcmpRedirect;
}

void
Ipv4L3ProtocolJson::SetEnableMtuDiscovery(bool e)
{
    m_enableMtuDiscovery = e;
}

bool
Ipv4L3ProtocolJson::GetEnableMtuDiscovery() const
{
    return m_enableMtuDiscovery;
}

void
Ipv4L3ProtocolJson::SetFragmentExpirationTimeout(const std::string& t)
{
    m_fragmentExpirationTimeout = t;
}

const std::string&
Ipv4L3ProtocolJson::GetFragmentExpirationTimeout() const
{
    return m_fragmentExpirationTimeout;
}

void
Ipv4L3ProtocolJson::SetMtuDiscoverTimeout(const std::string& t)
{
    m_mtuDiscoverTimeout = t;
}

const std::string&
Ipv4L3ProtocolJson::GetMtuDiscoverTimeout() const
{
    return m_mtuDiscoverTimeout;
}

void
Ipv4L3ProtocolJson::SetRouteCacheTimeout(const std::string& t)
{
    m_routeCacheTimeout = t;
}

const std::string&
Ipv4L3ProtocolJson::GetRouteCacheTimeout() const
{
    return m_routeCacheTimeout;
}

void
Ipv4L3ProtocolJson::SetEnableChecksum(bool e)
{
    m_enableChecksum = e;
}

bool
Ipv4L3ProtocolJson::GetEnableChecksum() const
{
    return m_enableChecksum;
}

// ====== ipv6======

void
Ipv6L3ProtocolJson::SetDefaultTtl(uint32_t t)
{
    m_defaultTtl = t;
}

uint32_t
Ipv6L3ProtocolJson::GetDefaultTtl() const
{
    return m_defaultTtl;
}

void
Ipv6L3ProtocolJson::SetIpForward(bool e)
{
    m_ipForward = e;
}

bool
Ipv6L3ProtocolJson::GetIpForward() const
{
    return m_ipForward;
}

void
Ipv6L3ProtocolJson::SetSendIcmpRedirect(bool e)
{
    m_sendIcmpRedirect = e;
}

bool
Ipv6L3ProtocolJson::GetSendIcmpRedirect() const
{
    return m_sendIcmpRedirect;
}

void
Ipv6L3ProtocolJson::SetEnableMtuDiscovery(bool e)
{
    m_enableMtuDiscovery = e;
}

bool
Ipv6L3ProtocolJson::GetEnableMtuDiscovery() const
{
    return m_enableMtuDiscovery;
}

void
Ipv6L3ProtocolJson::SetFragmentExpirationTimeout(const std::string& t)
{
    m_fragmentExpirationTimeout = t;
}

const std::string&
Ipv6L3ProtocolJson::GetFragmentExpirationTimeout() const
{
    return m_fragmentExpirationTimeout;
}

void
Ipv6L3ProtocolJson::SetMtuDiscoverTimeout(const std::string& t)
{
    m_mtuDiscoverTimeout = t;
}

const std::string&
Ipv6L3ProtocolJson::GetMtuDiscoverTimeout() const
{
    return m_mtuDiscoverTimeout;
}

void
Ipv6L3ProtocolJson::SetRouteCacheTimeout(const std::string& t)
{
    m_routeCacheTimeout = t;
}

const std::string&
Ipv6L3ProtocolJson::GetRouteCacheTimeout() const
{
    return m_routeCacheTimeout;
}

void
Ipv6L3ProtocolJson::SetEnableChecksum(bool e)
{
    m_enableChecksum = e;
}

bool
Ipv6L3ProtocolJson::GetEnableChecksum() const
{
    return m_enableChecksum;
}

// ========================== TCP =============================

void
TcpL4ProtocolJson::SetSendBufferSize(uint32_t s)
{
    m_sendBufferSize = s;
}

uint32_t
TcpL4ProtocolJson::GetSendBufferSize() const
{
    return m_sendBufferSize;
}

void
TcpL4ProtocolJson::SetReceiveBufferSize(uint32_t s)
{
    m_receiveBufferSize = s;
}

uint32_t
TcpL4ProtocolJson::GetReceiveBufferSize() const
{
    return m_receiveBufferSize;
}

void
TcpL4ProtocolJson::SetVariant(const std::string& v)
{
    m_variant = v;
}

const std::string&
TcpL4ProtocolJson::GetVariant() const
{
    return m_variant;
}

void
TcpL4ProtocolJson::SetInitialCwnd(uint32_t c)
{
    m_initialCwnd = c;
}

uint32_t
TcpL4ProtocolJson::GetInitialCwnd() const
{
    return m_initialCwnd;
}

void
TcpL4ProtocolJson::SetSegmentSize(uint32_t s)
{
    m_segmentSize = s;
}

uint32_t
TcpL4ProtocolJson::GetSegmentSize() const
{
    return m_segmentSize;
}

void
TcpL4ProtocolJson::SetMaxCwnd(uint32_t c)
{
    m_maxCwnd = c;
}

uint32_t
TcpL4ProtocolJson::GetMaxCwnd() const
{
    return m_maxCwnd;
}

void
TcpL4ProtocolJson::SetSlowStartThreshold(uint32_t t)
{
    m_slowStartThreshold = t;
}

uint32_t
TcpL4ProtocolJson::GetSlowStartThreshold() const
{
    return m_slowStartThreshold;
}

void
TcpL4ProtocolJson::SetRetransmitTimeout(uint32_t t)
{
    m_retransmitTimeout = t;
}

uint32_t
TcpL4ProtocolJson::GetRetransmitTimeout() const
{
    return m_retransmitTimeout;
}

void
TcpL4ProtocolJson::SetEnableSack(bool e)
{
    m_enableSack = e;
}

bool
TcpL4ProtocolJson::GetEnableSack() const
{
    return m_enableSack;
}

void
TcpL4ProtocolJson::SetEnableDelayedAck(bool e)
{
    m_enableDelayedAck = e;
}

bool
TcpL4ProtocolJson::GetEnableDelayedAck() const
{
    return m_enableDelayedAck;
}

void
TcpL4ProtocolJson::SetEnableNagle(bool e)
{
    m_enableNagle = e;
}

bool
TcpL4ProtocolJson::GetEnableNagle() const
{
    return m_enableNagle;
}

void
TcpL4ProtocolJson::SetEnableKeepAlive(bool e)
{
    m_enableKeepAlive = e;
}

bool
TcpL4ProtocolJson::GetEnableKeepAlive() const
{
    return m_enableKeepAlive;
}

// ========================== UDP =============================

void
UdpL4ProtocolJson::SetSendBufferSize(uint32_t s)
{
    m_sendBufferSize = s;
}

uint32_t
UdpL4ProtocolJson::GetSendBufferSize() const
{
    return m_sendBufferSize;
}

void
UdpL4ProtocolJson::SetReceiveBufferSize(uint32_t s)
{
    m_receiveBufferSize = s;
}

uint32_t
UdpL4ProtocolJson::GetReceiveBufferSize() const
{
    return m_receiveBufferSize;
}

void
UdpL4ProtocolJson::SetPacketSize(uint32_t s)
{
    m_packetSize = s;
}

uint32_t
UdpL4ProtocolJson::GetPacketSize() const
{
    return m_packetSize;
}

void
UdpL4ProtocolJson::SetDataRate(const std::string& r)
{
    m_dataRate = r;
}

const std::string&
UdpL4ProtocolJson::GetDataRate() const
{
    return m_dataRate;
}

void
UdpL4ProtocolJson::SetEnableChecksum(bool e)
{
    m_enableChecksum = e;
}

bool
UdpL4ProtocolJson::GetEnableChecksum() const
{
    return m_enableChecksum;
}

void
UdpL4ProtocolJson::SetEnableBroadcast(bool e)
{
    m_enableBroadcast = e;
}

bool
UdpL4ProtocolJson::GetEnableBroadcast() const
{
    return m_enableBroadcast;
}

void
UdpL4ProtocolJson::SetEnableMulticast(bool e)
{
    m_enableMulticast = e;
}

bool
UdpL4ProtocolJson::GetEnableMulticast() const
{
    return m_enableMulticast;
}

// ====== network======
void
InternetStackJson::SetIpv4(const std::shared_ptr<Ipv4L3ProtocolJson>& ipv4)
{
    m_ipv4 = ipv4;
}

void
InternetStackJson::SetIpv6(const std::shared_ptr<Ipv6L3ProtocolJson>& ipv6)
{
    m_ipv6 = ipv6;
}

void
InternetStackJson::SetUdp(const std::shared_ptr<UdpL4ProtocolJson>& udp)
{
    m_udp = udp;
}

void
InternetStackJson::SetTcp(const std::shared_ptr<TcpL4ProtocolJson>& tcp)
{
    m_tcp = tcp;
}

std::shared_ptr<Ipv4L3ProtocolJson>
InternetStackJson::GetIpv4() const
{
    return m_ipv4;
}

std::shared_ptr<Ipv6L3ProtocolJson>
InternetStackJson::GetIpv6() const
{
    return m_ipv6;
}

std::shared_ptr<UdpL4ProtocolJson>
InternetStackJson::GetUdp() const
{
    return m_udp;
}

std::shared_ptr<TcpL4ProtocolJson>
InternetStackJson::GetTcp() const
{
    return m_tcp;
}

void
InternetStackJson::SetEnableGlobalRouting(bool enable)
{
    m_enableGlobalRouting = enable;
}

bool
InternetStackJson::IsEnableGlobalRouting()
{
    return m_enableGlobalRouting;
}

} // namespace ns3