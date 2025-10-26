/**
 * @file node-json.h
 * @brief Definition of NodeJson class and its related components.
 */

#ifndef NODE_JSON_H
#define NODE_JSON_H

#include "application-json.h"
#include "ipv4-routing-protocol-json.h"
#include "ipv6-routing-protocol-json.h"
#include "mobility-json.h"

#include <memory>
#include <string>
#include <vector>

namespace ns3
{

/**
 * @class NodeJson
 * @brief Represents a network node and its configuration.
 */
class NodeJson
{
  public:
    NodeJson() = default;
    ~NodeJson() = default;

    // === ID and Role ===
    void SetNodeId(uint32_t nodeId);
    uint32_t GetNodeId() const;

    void SetRole(std::string role);
    std::string GetRole() const;

    // === Applications ===
    void SetApplications(const std::vector<std::shared_ptr<ApplicationJson>>& applications);
    const std::vector<std::shared_ptr<ApplicationJson>>& GetApplications() const;

    // === Mobility ===
    void SetMobility(const std::shared_ptr<MobilityJson>& mobility);
    std::shared_ptr<MobilityJson> GetMobility() const;

    void SetIpv4RoutingProtocols(const std::vector<std::shared_ptr<Ipv4RoutingProtocolJson>>& ipv4RoutingProtocolJson);
    void SetIpv6RoutingProtocols(const std::vector<std::shared_ptr<Ipv6RoutingProtocolJson>>& ipv6RoutingProtocolJson);
    std::vector<std::shared_ptr<Ipv4RoutingProtocolJson>> GetIpv4RoutingProtocols() const;
    std::vector<std::shared_ptr<Ipv6RoutingProtocolJson>> GetIpv6RoutingProtocols() const;

  private:
    uint32_t m_nodeId = 0;
    std::string m_role;
    std::vector<std::shared_ptr<Ipv4RoutingProtocolJson>> m_ipv4RoutingProtocolJson;
    std::vector<std::shared_ptr<Ipv6RoutingProtocolJson>> m_ipv6RoutingProtocolJson;
    std::vector<std::shared_ptr<ApplicationJson>> m_applications;
    std::shared_ptr<MobilityJson> m_mobility;
};

} // namespace ns3

#endif // NODE_JSON_H
