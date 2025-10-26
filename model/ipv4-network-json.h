/**
 * @file ipv4-network-json.h
 * @brief Definition of IPv4  address configuration classes (JSON).
 */

#ifndef IPV4_NETWORK_JSON_H
#define IPV4_NETWORK_JSON_H

#include <string>
#include <memory>
#include <vector>
#include "link-json.h"

namespace ns3{


/**
 * @brief IPv4 fixed address entry.
 */
class Ipv4AddressFixed
{
public:

    void SetNetDeviceId(NetDeviceIdJson id);
    NetDeviceIdJson GetNetDeviceId() const;

    void SetIpv4Address(const std::string& address);
    const std::string& GetIpv4Address() const;

private:
    NetDeviceIdJson m_netDeviceId;
    std::string m_ipv4Address;
};

/**
 * @brief IPv4 address configuration.
 */
class Ipv4NetworkJson
{
public:

    void SetSubnet(const std::string& subnet);
    const std::string& GetSubnet() const;

    void SetBase(const std::string& mask);
    const std::string& GetBase() const;

    void SetMask(const std::string& mask);
    const std::string& GetMask() const;

    void SetNetDeviceIds(const std::vector<NetDeviceIdJson> ids);
    const std::vector<NetDeviceIdJson> GetNetDeviceIds() const;

    void SetFixed(const std::vector<std::shared_ptr<Ipv4AddressFixed>>& fixed);
    const std::vector<std::shared_ptr<Ipv4AddressFixed>>& GetFixed() const;

private:
    std::string m_subnet;
    std::string m_mask;
    std::string m_base;
    std::vector<NetDeviceIdJson> m_netDeviceIds;
    std::vector<std::shared_ptr<Ipv4AddressFixed>> m_fixed;
};


    
}



#endif