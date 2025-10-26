/**
 * @file ipv6-json.h
 * @brief Definition of IPv6 L3 protocol and routing configuration classes (JSON).
 */

#ifndef IPV6_ROUTING_PROTOCOL_JSON_H
#define IPV6_ROUTING_PROTOCOL_JSON_H

#include <memory>
#include <string>
#include <vector>

namespace ns3
{

/**
 * @brief  class for IPv6 routing configuration (JSON).
 */
class Ipv6RoutingProtocolJson
{
  public:
    virtual ~Ipv6RoutingProtocolJson() = default;
    void SetPriority(uint32_t priority);
    uint32_t GetPriority() const;

    void SetType(const std::string& type);
    const std::string& GetType() const;

  private:
    uint32_t m_priority = 0;
    std::string m_type;
};

/**
 * @brief IPv6 route entry.
 */
struct Ipv6RouteEntryJson
{
    std::string m_dest;
    uint32_t m_prefixLength;
    std::string m_nextHop;
    uint32_t m_nextLinkId;
};

/**
 * @brief IPv6 static routing configuration.
 */
class Ipv6StaticRoutingProtocolJson : public Ipv6RoutingProtocolJson
{
  public:
    void SetRoutes(const std::vector<Ipv6RouteEntryJson>& routes);
    const std::vector<Ipv6RouteEntryJson>& GetRoutes() const;

  private:
    std::vector<Ipv6RouteEntryJson> m_routes;
};

/**
 * @brief IPv6 global routing configuration.
 */
class Ipv6GlobalRoutingProtocolJson : public Ipv6RoutingProtocolJson
{
  public:
    void SetRespondToInterfaceEvents(bool enable);
    void SetRandomEcmpRouting(bool enable);

    bool GetRespondToInterfaceEvents() const;
    bool GetRandomEcmpRouting() const;

  private:
    bool m_respondToInterfaceEvents = false;
    bool m_randomEcmpRouting = false;
};

} // namespace ns3

#endif // IPV6_JSON_H
