#include "ipv6-network-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

std::shared_ptr<Ipv6NetworkJson>
Ipv6NetworkJsonHelper::Build(json& entry)
{
    auto ipv6 = std::make_shared<Ipv6NetworkJson>();
    ipv6->SetSubnet(entry.value("subnet", ""));
    ipv6->SetPrefixLength(entry.value<uint32_t>("prefixLength", 0));
    ipv6->SetBase(entry.value("base", ""));
    std::vector<NetDeviceIdJson> devIds;
    for (const auto& d : entry.value("netDeviceIds", json::array()))
    {
        devIds.push_back(
            NetDeviceIdJson{d.value<uint32_t>("nodeId", 0), d.value<uint32_t>("linkId", 0)});
    }
    ipv6->SetNetDeviceIds(devIds);
    std::vector<std::shared_ptr<Ipv6AddressFixed>> fixedList;
    for (const auto& f : entry.value("fixed", json::array()))
    {
        auto fixed = std::make_shared<Ipv6AddressFixed>();
        fixed->SetIpv6Address(f.value("ipv6Address",""));
        auto d = f.value("netDeviceId", json::object());
        fixed->SetNetDeviceId(NetDeviceIdJson{d.value<uint32_t>("nodeId", 0), d.value<uint32_t>("linkId", 0)});
        fixedList.push_back(fixed);
    }
    ipv6->SetFixed(fixedList);
    return ipv6;
}

} // namespace ns3