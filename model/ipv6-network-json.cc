#include "ipv6-network-json.h"

namespace ns3 {

// ========== Ipv6AddressFixed ==========

void Ipv6AddressFixed::SetNetDeviceId(NetDeviceIdJson netDeviceId) { m_netDeviceId = netDeviceId; }
NetDeviceIdJson Ipv6AddressFixed::GetNetDeviceId() const { return m_netDeviceId; }

void Ipv6AddressFixed::SetIpv6Address(const std::string& address)
{
    m_ipv6Address = address;
}
const std::string& Ipv6AddressFixed::GetIpv6Address() const
{
    return m_ipv6Address;
}

// ========== Ipv6AddressJson ==========

void Ipv6NetworkJson::SetSubnet(const std::string& subnet)
{
    m_subnet = subnet;
}
const std::string& Ipv6NetworkJson::GetSubnet() const
{
    return m_subnet;
}

void Ipv6NetworkJson::SetPrefixLength(uint32_t prefixLength)
{
    m_prefixLength = prefixLength;
}
uint32_t Ipv6NetworkJson::GetPrefixLength() const
{
    return m_prefixLength;
}

void Ipv6NetworkJson::SetBase(const std::string& base)
{
    m_base = base;
}
const std::string& Ipv6NetworkJson::GetBase() const
{
    return m_base;
}

void Ipv6NetworkJson::SetNetDeviceIds(const std::vector<NetDeviceIdJson> netDeviceIds) { m_netDeviceIds = netDeviceIds; }
const std::vector<NetDeviceIdJson> Ipv6NetworkJson::GetNetDeviceIds() const { return m_netDeviceIds; }

void Ipv6NetworkJson::SetFixed(const std::vector<std::shared_ptr<Ipv6AddressFixed>>& fixed)
{
    m_fixed = fixed;
}
const std::vector<std::shared_ptr<Ipv6AddressFixed>>& Ipv6NetworkJson::GetFixed() const
{
    return m_fixed;
}

}