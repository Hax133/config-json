#include "node-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

using json = nlohmann::json;

std::shared_ptr<NodeJson>
NodeJsonHelper::Build(const json& jn,
                      const json& jm,
                      const json& j4rList,
                      const json& j6rList,
                      const std::vector<json>& jas)
{
    
    MobilityJsonHelper mjh;
    Ipv4RoutingProtocolJsonHelper rjh4;
    Ipv6RoutingProtocolJsonHelper rjh6;
    ApplicationJsonHelper ajh;

    auto mobility = std::make_shared<MobilityJson>();
    std::vector<std::shared_ptr<Ipv4RoutingProtocolJson>> routing4s;
    std::vector<std::shared_ptr<Ipv6RoutingProtocolJson>> routing6s;
    std::vector<std::shared_ptr<ApplicationJson>> apps;

    if(!jm.is_null())
    {
        mobility = mjh.Build(jm);
    }
    json j4rs, j6rs;
    if(!j4rList.is_null()){j4rs = j4rList.value("ipv4RoutingList",json::array());}
    if(!j6rList.is_null()){j6rs = j6rList.value("ipv6RoutingList",json::array());}
    for (auto& j4r : j4rs)
    {
        routing4s.push_back(rjh4.Build(j4r));
    }
    for (auto& j6r : j6rs)
    {
        routing6s.push_back(rjh6.Build(j6r));
    }
    for (auto& ja : jas)
    {
        apps.push_back(ajh.Build(ja));
    }


    auto node = std::make_shared<NodeJson>();
    node->SetNodeId(jn.value<uint32_t>("nodeId", 0));
    node->SetRole(jn.value("role", ""));
    node->SetMobility(mobility);
    node->SetIpv4RoutingProtocols(routing4s);
    node->SetIpv6RoutingProtocols(routing6s);
    node->SetApplications(apps);
    return node;
}

} // namespace ns3
