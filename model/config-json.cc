/**
 * @file config-json.cc
 * @brief Implementation of top-level JSON configuration container.
 */

#include "config-json.h"

namespace ns3
{

// ====== Nodes ======
void
ConfigJson::SetNodes(const std::vector<std::shared_ptr<NodeJson>>& nodes)
{
    m_nodes = nodes;
}

const std::vector<std::shared_ptr<NodeJson>>&
ConfigJson::GetNodes() const
{
    return m_nodes;
}

// ====== Links ======
void
ConfigJson::SetLinks(const std::vector<std::shared_ptr<LinkJson>>& links)
{
    m_links = links;
}

const std::vector<std::shared_ptr<LinkJson>>&
ConfigJson::GetLinks() const
{
    return m_links;
}

// ====== InternetStack ======
void
ConfigJson::SetInternetStack(const std::shared_ptr<InternetStackJson>& internetStack)
{
    m_internetStack = internetStack;
}

const std::shared_ptr<InternetStackJson>&
ConfigJson::GetInternetStack() const
{
    return m_internetStack;
}

// ====== IPv4 Networks ======
void
ConfigJson::SetIpv4Networks(const std::vector<std::shared_ptr<Ipv4NetworkJson>>& ipv4)
{
    m_ipv4Networks = ipv4;
}

const std::vector<std::shared_ptr<Ipv4NetworkJson>>&
ConfigJson::GetIpv4Networks() const
{
    return m_ipv4Networks;
}

// ====== IPv6 Networks ======
void
ConfigJson::SetIpv6Networks(const std::vector<std::shared_ptr<Ipv6NetworkJson>>& ipv6)
{
    m_ipv6Networks = ipv6;
}

const std::vector<std::shared_ptr<Ipv6NetworkJson>>&
ConfigJson::GetIpv6Networks() const
{
    return m_ipv6Networks;
}

} // namespace ns3
