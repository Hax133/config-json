#include "ipv4-network-json.h"

namespace ns3 {

// ========== Ipv4AddressFixed ==========

void Ipv4AddressFixed::SetNetDeviceId(NetDeviceIdJson netDeviceId) { m_netDeviceId = netDeviceId; }
NetDeviceIdJson Ipv4AddressFixed::GetNetDeviceId() const { return m_netDeviceId; }

void Ipv4AddressFixed::SetIpv4Address(const std::string& address)
{
    m_ipv4Address = address;
}
const std::string& Ipv4AddressFixed::GetIpv4Address() const
{
    return m_ipv4Address;
}

// ========== Ipv4NetworkJson ==========

void Ipv4NetworkJson::SetSubnet(const std::string& subnet)
{
    m_subnet = subnet;
}
const std::string& Ipv4NetworkJson::GetSubnet() const
{
    return m_subnet;
}

void Ipv4NetworkJson::SetMask(const std::string& mask)
{
    m_mask = mask;
}
const std::string& Ipv4NetworkJson::GetMask() const
{
    return m_mask;
}

void Ipv4NetworkJson::SetBase(const std::string& base)
{
    m_base = base;
}
const std::string& Ipv4NetworkJson::GetBase() const
{
    return m_base;
}

void Ipv4NetworkJson::SetNetDeviceIds(const std::vector<NetDeviceIdJson> netDeviceIds) { m_netDeviceIds = netDeviceIds; }
const std::vector<NetDeviceIdJson> Ipv4NetworkJson::GetNetDeviceIds() const { return m_netDeviceIds; }

void Ipv4NetworkJson::SetFixed(const std::vector<std::shared_ptr<Ipv4AddressFixed>>& fixed)
{
    m_fixed = fixed;
}
const std::vector<std::shared_ptr<Ipv4AddressFixed>>& Ipv4NetworkJson::GetFixed() const
{
    return m_fixed;
}

}