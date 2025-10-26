/**
 * @file config-json.h
 * @brief Definition of top-level configuration container for JSON-d simulation setup.
 */

#ifndef CONFIG_JSON_H
#define CONFIG_JSON_H

#include <string>
#include <memory>
#include <vector>

#include "node-json.h"
#include "link-json.h"
#include "internet-stack-json.h"
#include "ipv4-network-json.h"
#include "ipv6-network-json.h"


namespace ns3 {
/**
 * @brief Root configuration object aggregating nodes, links, and address info.
 */

class ConfigJson
{
public:
    // ====== Nodes ======
    void SetNodes(const std::vector<std::shared_ptr<NodeJson>>& nodes);
    const std::vector<std::shared_ptr<NodeJson>>& GetNodes() const;

    // ====== Links ======
    void SetLinks(const std::vector<std::shared_ptr<LinkJson>>& links);
    const std::vector<std::shared_ptr<LinkJson>>& GetLinks() const;

    // ====== InternetStack ======
    void SetInternetStack(const std::shared_ptr<InternetStackJson>& internetStack);
    const std::shared_ptr<InternetStackJson>& GetInternetStack() const;

    // ====== IPv4 Networks ======
    void SetIpv4Networks(const std::vector<std::shared_ptr<Ipv4NetworkJson>>& ipv4);
    const std::vector<std::shared_ptr<Ipv4NetworkJson>>& GetIpv4Networks() const;

    // ====== IPv6 Networks ======
    void SetIpv6Networks(const std::vector<std::shared_ptr<Ipv6NetworkJson>>& ipv6);
    const std::vector<std::shared_ptr<Ipv6NetworkJson>>& GetIpv6Networks() const;

private:
    std::vector<std::shared_ptr<NodeJson>> m_nodes;
    std::vector<std::shared_ptr<LinkJson>> m_links;
    std::shared_ptr<InternetStackJson> m_internetStack;
    std::vector<std::shared_ptr<Ipv4NetworkJson>> m_ipv4Networks;
    std::vector<std::shared_ptr<Ipv6NetworkJson>> m_ipv6Networks;
};

} // namespace ns3

#endif // CONFIG_JSON_H
