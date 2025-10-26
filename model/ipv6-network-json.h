/**
 * @file ipv6-network-json.h
 * @brief Definition of IPv6  address configuration classes (JSON).
 */

#ifndef IPV6_NETWORK_JSON_H
#define IPV6_NETWORK_JSON_H

#include "link-json.h"

#include <memory>
#include <string>
#include <vector>

namespace ns3
{

/**
 * @brief IPv6 fixed address entry.
 */
class Ipv6AddressFixed
{
  public:
    void SetNetDeviceId(NetDeviceIdJson id);
    NetDeviceIdJson GetNetDeviceId() const;

    void SetIpv6Address(const std::string& address);
    const std::string& GetIpv6Address() const;

  private:
    NetDeviceIdJson m_netDeviceId;
    std::string m_ipv6Address;
};

/**
 * @brief IPv6 address configuration.
 */
class Ipv6NetworkJson
{
  public:
    void SetSubnet(const std::string& subnet);
    const std::string& GetSubnet() const;

    void SetPrefixLength(uint32_t prefixLength);
    uint32_t GetPrefixLength() const;

    void SetBase(const std::string& base);
    const std::string& GetBase() const;

    void SetNetDeviceIds(const std::vector<NetDeviceIdJson> ids);
    const std::vector<NetDeviceIdJson> GetNetDeviceIds() const;

    void SetFixed(const std::vector<std::shared_ptr<Ipv6AddressFixed>>& fixed);
    const std::vector<std::shared_ptr<Ipv6AddressFixed>>& GetFixed() const;

  private:
    std::string m_subnet;
    uint32_t m_prefixLength;
    std::string m_base;
    std::vector<NetDeviceIdJson> m_netDeviceIds;
    std::vector<std::shared_ptr<Ipv6AddressFixed>> m_fixed;
};

} // namespace ns3

#endif