#include "ipv4-network-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

std::shared_ptr<Ipv4NetworkJson>
Ipv4NetworkJsonHelper::Build(json& entry)
{
    auto ipv4 = std::make_shared<Ipv4NetworkJson>();
    ipv4->SetSubnet(entry.value("subnet", ""));
    ipv4->SetMask(entry.value("mask", ""));
    ipv4->SetBase(entry.value("base", ""));
    std::vector<NetDeviceIdJson> devIds;
    for (const auto& d : entry.value("netDeviceIds", json::array()))
    {
        devIds.push_back(
            NetDeviceIdJson{d.value<uint32_t>("nodeId", 0), d.value<uint32_t>("linkId", 0)});
    }
    ipv4->SetNetDeviceIds(devIds);
    std::vector<std::shared_ptr<Ipv4AddressFixed>> fixedList;
    for (const auto& f : entry.value("fixed", json::array()))
    {
        auto fixed = std::make_shared<Ipv4AddressFixed>();
        fixed->SetIpv4Address(f.value("ipv4Address",""));
        auto d = f.value("netDeviceId", json::object());
        fixed->SetNetDeviceId(NetDeviceIdJson{d.value<uint32_t>("nodeId", 0), d.value<uint32_t>("linkId", 0)});
        fixedList.push_back(fixed);
    }
    ipv4->SetFixed(fixedList);
    return ipv4;
}

} // namespace ns3