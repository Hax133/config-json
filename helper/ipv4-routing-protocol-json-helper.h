/**
 * @file ipv4-routing-protocol-json-helper.h
 * @brief Helper for constructing Ipv4L3ProtocolJson and routing configurations from JSON.
 */

#ifndef IPV4_ROUTING_PROTOCOL_JSON_HELPER_H
#define IPV4_ROUTING_PROTOCOL_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../model/ipv4-routing-protocol-json.h"

namespace ns3 {

using json = nlohmann::json;
class Ipv4RoutingProtocolJsonHelper
{
public:
    /**
     * @brief Build an Ipv4L3ProtocolJson object by its id.
     * @return nullptr if not found.
     */
    std::shared_ptr<Ipv4RoutingProtocolJson> Build(const json & j);


private:

    // === Routing factory ===
    std::shared_ptr<Ipv4StaticRoutingProtocolJson> BuildStaticRouting(const json& entry);
    std::shared_ptr<OlsrRoutingProtocolJson> BuildOlsrRouting(const json& entry);
    std::shared_ptr<Ipv4GlobalRoutingProtocolJson> BuildGlobalRouting(const json& entry);

};

}
#endif