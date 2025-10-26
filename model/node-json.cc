/**
 * @file node-json.cc
 * @brief Implementation of NodeJson class.
 */

#include "node-json.h"

namespace ns3
{

// === ID and Role ===
void
NodeJson::SetNodeId(uint32_t nodeId)
{
    m_nodeId = nodeId;
}

uint32_t
NodeJson::GetNodeId() const
{
    return m_nodeId;
}

void
NodeJson::SetRole(std::string role)
{
    m_role = role;
}

std::string
NodeJson::GetRole() const
{
    return m_role;
}

// === Applications ===
void
NodeJson::SetApplications(const std::vector<std::shared_ptr<ApplicationJson>>& applications)
{
    m_applications = applications;
}

const std::vector<std::shared_ptr<ApplicationJson>>&
NodeJson::GetApplications() const
{
    return m_applications;
}

// === Mobility ===
void
NodeJson::SetMobility(const std::shared_ptr<MobilityJson>& mobility)
{
    m_mobility = mobility;
}

std::shared_ptr<MobilityJson>
NodeJson::GetMobility() const
{
    return m_mobility;
}

void
NodeJson::SetIpv4RoutingProtocols(const std::vector<std::shared_ptr<Ipv4RoutingProtocolJson>>& ipv4RoutingProtocolJson)
{
    m_ipv4RoutingProtocolJson = ipv4RoutingProtocolJson;
}

void
NodeJson::SetIpv6RoutingProtocols(const std::vector<std::shared_ptr<Ipv6RoutingProtocolJson>>& ipv6RoutingProtocolJson)
{
    m_ipv6RoutingProtocolJson = ipv6RoutingProtocolJson;
}

// Getter
std::vector<std::shared_ptr<Ipv4RoutingProtocolJson>>
NodeJson::GetIpv4RoutingProtocols() const
{
    return m_ipv4RoutingProtocolJson;
}

std::vector<std::shared_ptr<Ipv6RoutingProtocolJson>>
NodeJson::GetIpv6RoutingProtocols() const
{
    return m_ipv6RoutingProtocolJson;
}

} // namespace ns3
