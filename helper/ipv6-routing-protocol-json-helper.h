/**
 * @file ipv6-routing-protocol-json-helper.h
 * @brief Helper for constructing Ipv6L3ProtocolJson and routing configurations from JSON.
 */

#ifndef IPV6_ROUTING_PROTOCOL_JSON_HELPER_H
#define IPV6_ROUTING_PROTOCOL_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../model/ipv6-routing-protocol-json.h"

namespace ns3 {

using json = nlohmann::json;
class Ipv6RoutingProtocolJsonHelper
{
public:
    /**
     * @brief Build an Ipv6L3ProtocolJson object by its id.
     * @return nullptr if not found.
     */
    std::shared_ptr<Ipv6RoutingProtocolJson> Build(const json & j);


private:
    std::shared_ptr<Ipv6StaticRoutingProtocolJson> BuildStaticRouting(const json& entry);
    std::shared_ptr<Ipv6GlobalRoutingProtocolJson> BuildGlobalRouting(const json& entry);

};

}
#endif