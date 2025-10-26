#include "ipv4-routing-protocol-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{
std::shared_ptr<Ipv4RoutingProtocolJson>
Ipv4RoutingProtocolJsonHelper::Build(const json& entry)
{
    if (entry.is_null())
    {
        return nullptr;
    }
    std::string type = entry.value("type", "");
    if (type == "Static")
        return BuildStaticRouting(entry);
    else if (type == "Olsr")
        return BuildOlsrRouting(entry);
    else if (type == "Global")
        return BuildGlobalRouting(entry);

    std::cerr << "[Warning] Unknown IPv4 routing type: " << type << std::endl;
    return nullptr;
}

std::shared_ptr<Ipv4StaticRoutingProtocolJson>
Ipv4RoutingProtocolJsonHelper::BuildStaticRouting(const json& entry)
{
    auto routing = std::make_shared<Ipv4StaticRoutingProtocolJson>();
    routing->SetPriority(entry.value("priority", 0));
    routing->SetType(entry.value("type", ""));
    std::vector<Ipv4RouteEntryJson> routes;
    if (entry.contains("routes") && entry["routes"].is_array())
    {
        for (const auto& r : entry["routes"])
        {
            Ipv4RouteEntryJson route;
            route.m_ipv4Address = r.value("ipv4Address", "");
            route.m_mask = r.value("mask", "");
            route.m_nextHop = r.value("nextHop", "");
            route.m_nextLinkId = r.value("nextLinkId", 0);
            routes.push_back(route);
        }
    }
    routing->SetRoutes(routes);
    return routing;
}

std::shared_ptr<OlsrRoutingProtocolJson>
Ipv4RoutingProtocolJsonHelper::BuildOlsrRouting(const json& entry)
{
    auto routing = std::make_shared<OlsrRoutingProtocolJson>();
    routing->SetPriority(entry.value("priority", 0));
    routing->SetType(entry.value("type", ""));
    routing->SetHelloInterval(entry.value("helloInterval", ""));
    routing->SetTcInterval(entry.value("tcInterval", ""));
    routing->SetHnaInterval(entry.value("hnaInterval", ""));
    routing->SetWillingness(entry.value("willingness", 0));

    std::vector<Ipv4HnaNetworkJson> hnaList;
    if (entry.contains("hnaNetworks") && entry["hnaNetworks"].is_array())
    {
        for (const auto& n : entry["hnaNetworks"])
        {
            Ipv4HnaNetworkJson net;
            net.m_network = n.value("network", "");
            net.m_mask = n.value("mask", "");
            hnaList.push_back(net);
        }
    }
    routing->SetHnaNetworks(hnaList);
    return routing;
}

std::shared_ptr<Ipv4GlobalRoutingProtocolJson>
Ipv4RoutingProtocolJsonHelper::BuildGlobalRouting(const json& entry)
{
    auto routing = std::make_shared<Ipv4GlobalRoutingProtocolJson>();
    routing->SetPriority(entry.value("priority", 0));
    routing->SetType(entry.value("type", ""));
    routing->SetRespondToInterfaceEvents(entry.value("respondToInterfaceEvents", false));
    routing->SetRandomEcmpRouting(entry.value("randomEcmpRouting", false));
    return routing;
}

} // namespace ns3