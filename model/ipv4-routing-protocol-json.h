/**
 * @file ipv4-json.h
 * @brief Definition of IPv4 L3 protocol and routing configuration classes (JSON).
 */

#ifndef IPV4_ROUTING_PROTOCOL_JSON_H
#define IPV4_ROUTING_PROTOCOL_JSON_H

#include <string>
#include <memory>
#include <vector>

namespace ns3 {

/**
 * @brief  class for IPv4 routing configuration (JSON).
 */
class Ipv4RoutingProtocolJson
{
public:
    virtual ~Ipv4RoutingProtocolJson() = default;
    void SetPriority(uint32_t priority);
    uint32_t GetPriority() const;

    void SetType(const std::string& type);
    const std::string& GetType() const;

private:
    uint32_t m_priority = 0;
    std::string m_type;
};

/**
 * @brief IPv4 route entry.
 */
struct Ipv4RouteEntryJson
{
    std::string m_ipv4Address;
    std::string m_mask;
    std::string m_nextHop;
    uint32_t m_nextLinkId;
};

/**
 * @brief IPv4 static routing configuration.
 */
class Ipv4StaticRoutingProtocolJson : public Ipv4RoutingProtocolJson
{
public:
    void SetRoutes(const std::vector<Ipv4RouteEntryJson>& routes);
    const std::vector<Ipv4RouteEntryJson>& GetRoutes() const;

private:
    std::vector<Ipv4RouteEntryJson> m_routes;
};

/**
 * @brief IPv4 HNA network definition (used by OLSR).
 */
struct Ipv4HnaNetworkJson
{
    std::string m_network;
    std::string m_mask;
};

/**
 * @brief OLSR routing configuration.
 */
class OlsrRoutingProtocolJson : public Ipv4RoutingProtocolJson
{
public:
    void SetHelloInterval(const std::string& interval);
    void SetTcInterval(const std::string& interval);
    void SetHnaInterval(const std::string& interval);
    void SetWillingness(uint32_t w);
    void SetHnaNetworks(const std::vector<Ipv4HnaNetworkJson>& networks);

    const std::string& GetHelloInterval() const;
    const std::string& GetTcInterval() const;
    const std::string& GetHnaInterval() const;
    uint32_t GetWillingness() const;
    const std::vector<Ipv4HnaNetworkJson>& GetHnaNetworks() const;

private:
    std::string m_helloInterval;
    std::string m_tcInterval;
    std::string m_hnaInterval;
    uint32_t m_willingness = 0;
    std::vector<Ipv4HnaNetworkJson> m_hnaNetworks;
};

/**
 * @brief Global routing configuration.
 */
class Ipv4GlobalRoutingProtocolJson : public Ipv4RoutingProtocolJson
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

#endif // IPV4_JSON_H
