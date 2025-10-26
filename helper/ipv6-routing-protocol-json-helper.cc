#include "ipv6-routing-protocol-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

std::shared_ptr<Ipv6RoutingProtocolJson>
Ipv6RoutingProtocolJsonHelper::Build(const json& entry)
{
    if (entry.is_null())
    {
        return nullptr;
    }
    std::string type = entry.value("type", "");
    if (type == "Static")
        return BuildStaticRouting(entry);
    else if (type == "Global")
        return BuildGlobalRouting(entry);

    std::cerr << "[Warning] Unknown IPv6 routing type: " << type << std::endl;
    return nullptr;
}

std::shared_ptr<Ipv6StaticRoutingProtocolJson>
Ipv6RoutingProtocolJsonHelper::BuildStaticRouting(const json& entry)
{
    auto routing = std::make_shared<Ipv6StaticRoutingProtocolJson>();
    routing->SetPriority(entry.value("priority", 0));
    routing->SetType(entry.value("type", ""));
    std::vector<Ipv6RouteEntryJson> routes;
    if (entry.contains("routes") && entry["routes"].is_array())
    {
        for (const auto& r : entry["routes"])
        {
            Ipv6RouteEntryJson route;
            route.m_dest = r.value("ipv6Address", "");
            route.m_prefixLength = r.value("prefixLength", 0);
            route.m_nextHop = r.value("nextHop", "");
            route.m_nextLinkId = r.value("nextLinkId", 0);
            routes.push_back(route);
        }
    }
    routing->SetRoutes(routes);
    return routing;
}

std::shared_ptr<Ipv6GlobalRoutingProtocolJson>
Ipv6RoutingProtocolJsonHelper::BuildGlobalRouting(const json& entry)
{
    auto routing = std::make_shared<Ipv6GlobalRoutingProtocolJson>();
    routing->SetPriority(entry.value("priority", 0));
    routing->SetType(entry.value("type", ""));
    routing->SetRespondToInterfaceEvents(entry.value("respondToInterfaceEvents", false));
    routing->SetRandomEcmpRouting(entry.value("randomEcmpRouting", false));
    return routing;
}

} // namespace ns3
