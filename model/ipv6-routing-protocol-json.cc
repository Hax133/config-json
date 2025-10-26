/**
 * @file ipv6-json.cc
 * @brief Implementation of IPv6 JSON configuration classes.
 */

#include "ipv6-routing-protocol-json.h"

namespace ns3 {

// ============ Ipv6RoutingProtocolJson ============
void Ipv6RoutingProtocolJson::SetPriority(uint32_t p) { m_priority = p; }
uint32_t Ipv6RoutingProtocolJson::GetPriority() const { return m_priority; }

void Ipv6RoutingProtocolJson::SetType(const std::string& type) { m_type = type; }
const std::string& Ipv6RoutingProtocolJson::GetType() const { return m_type; }

// ============ Ipv6StaticRoutingProtocolJson ============
void Ipv6StaticRoutingProtocolJson::SetRoutes(const std::vector<Ipv6RouteEntryJson>& routes) { m_routes = routes; }
const std::vector<Ipv6RouteEntryJson>& Ipv6StaticRoutingProtocolJson::GetRoutes() const { return m_routes; }

// ============ Ipv6GlobalRoutingProtocolJson ============
void Ipv6GlobalRoutingProtocolJson::SetRespondToInterfaceEvents(bool e) { m_respondToInterfaceEvents = e; }
void Ipv6GlobalRoutingProtocolJson::SetRandomEcmpRouting(bool e) { m_randomEcmpRouting = e; }
bool Ipv6GlobalRoutingProtocolJson::GetRespondToInterfaceEvents() const { return m_respondToInterfaceEvents; }
bool Ipv6GlobalRoutingProtocolJson::GetRandomEcmpRouting() const { return m_randomEcmpRouting; }

} // namespace ns3
