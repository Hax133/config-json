/**
 * @file ipv4-json.cc
 * @brief Implementation of IPv4 JSON configuration classes.
 */

#include "ipv4-routing-protocol-json.h"

namespace ns3 {

// ============ Ipv4RoutingProtocolJson ============
void Ipv4RoutingProtocolJson::SetPriority(uint32_t p) { m_priority = p; }
uint32_t Ipv4RoutingProtocolJson::GetPriority() const { return m_priority; }

void Ipv4RoutingProtocolJson::SetType(const std::string& type) { m_type = type; }
const std::string& Ipv4RoutingProtocolJson::GetType() const { return m_type; }

// ============ Ipv4StaticRoutingProtocolJson ============
void Ipv4StaticRoutingProtocolJson::SetRoutes(const std::vector<Ipv4RouteEntryJson>& routes) { m_routes = routes; }
const std::vector<Ipv4RouteEntryJson>& Ipv4StaticRoutingProtocolJson::GetRoutes() const { return m_routes; }

// ============ OlsrRoutingProtocolJson ============
void OlsrRoutingProtocolJson::SetHelloInterval(const std::string& i) { m_helloInterval = i; }
void OlsrRoutingProtocolJson::SetTcInterval(const std::string& i) { m_tcInterval = i; }
void OlsrRoutingProtocolJson::SetHnaInterval(const std::string& i) { m_hnaInterval = i; }
void OlsrRoutingProtocolJson::SetWillingness(uint32_t w) { m_willingness = w; }
void OlsrRoutingProtocolJson::SetHnaNetworks(const std::vector<Ipv4HnaNetworkJson>& n) { m_hnaNetworks = n; }

const std::string& OlsrRoutingProtocolJson::GetHelloInterval() const { return m_helloInterval; }
const std::string& OlsrRoutingProtocolJson::GetTcInterval() const { return m_tcInterval; }
const std::string& OlsrRoutingProtocolJson::GetHnaInterval() const { return m_hnaInterval; }
uint32_t OlsrRoutingProtocolJson::GetWillingness() const { return m_willingness; }
const std::vector<Ipv4HnaNetworkJson>& OlsrRoutingProtocolJson::GetHnaNetworks() const { return m_hnaNetworks; }

// ============ Ipv4GlobalRoutingProtocolJson ============
void Ipv4GlobalRoutingProtocolJson::SetRespondToInterfaceEvents(bool e) { m_respondToInterfaceEvents = e; }
void Ipv4GlobalRoutingProtocolJson::SetRandomEcmpRouting(bool e) { m_randomEcmpRouting = e; }
bool Ipv4GlobalRoutingProtocolJson::GetRespondToInterfaceEvents() const { return m_respondToInterfaceEvents; }
bool Ipv4GlobalRoutingProtocolJson::GetRandomEcmpRouting() const { return m_randomEcmpRouting; }

} // namespace ns3
