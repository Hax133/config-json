#include "config-json-helper.h"

#include "internet-stack-json-helper.h"
#include "ipv4-network-json-helper.h"
#include "ipv6-network-json-helper.h"
#include "link-json-helper.h"
#include "node-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

json
ConfigJsonHelper::LoadJson(boost::filesystem::path path)
{
    std::ifstream ifs(path.string());
    if (!ifs.is_open())
    {
        throw std::runtime_error("ConfigJsonHelper: cannot open config file: " + path.string());
    }
    json j;
    ifs >> j;
    return j;
}

std::shared_ptr<ConfigJson>
ConfigJsonHelper::Build(boost::filesystem::path configPath)
{
    boost::filesystem::path baseDir = configPath.parent_path();
    json config = LoadJson(configPath);
    if (!config.contains("file") || !config["file"].is_object())
    {
        throw std::runtime_error("ConfigJsonHelper: missing 'file' section in " +
                                 configPath.string());
    }

    const json& files = config.value("file", json::object());

    json jNodes, jWifiChannel, jLinks, jInternetStack;
    json jIpv4Networks, jIpv6Networks;
    json jIpv4RoutingProtocols, jIpv6RoutingProtocols;
    json jMobilitys, jApplications;

    if (files.contains("nodes"))
        jNodes = LoadJson(baseDir / files.value("nodes", ""));
    if (files.contains("wifiChannel"))
        jWifiChannel = LoadJson(baseDir / files.value("wifiChannel", ""));
    if (files.contains("links"))
        jLinks = LoadJson(baseDir / files.value("links", ""));
    if (files.contains("internetStack"))
        jInternetStack = LoadJson(baseDir / files.value("internetStack", ""));
    if (files.contains("ipv4Network"))
        jIpv4Networks = LoadJson(baseDir / files.value("ipv4Network", ""));
    if (files.contains("ipv6Network"))
        jIpv6Networks = LoadJson(baseDir / files.value("ipv6Network", ""));
    if (files.contains("ipv4RoutingProtocol"))
        jIpv4RoutingProtocols = LoadJson(baseDir / files.value("ipv4RoutingProtocol", ""));
    if (files.contains("ipv6RoutingProtocol"))
        jIpv6RoutingProtocols = LoadJson(baseDir / files.value("ipv6RoutingProtocol", ""));
    if (files.contains("mobility"))
        jMobilitys = LoadJson(baseDir / files.value("mobility", ""));
    if (files.contains("applications"))
        jApplications = LoadJson(baseDir / files.value("applications", ""));
    
    NodeJsonHelper njh;
    LinkJsonHelper ljh;
    InternetStackJsonHelper isjh;
    Ipv4NetworkJsonHelper i4njh;
    Ipv6NetworkJsonHelper i6njh;

    std::vector<std::shared_ptr<NodeJson>> nodes;
    std::vector<std::shared_ptr<LinkJson>> links;
    std::shared_ptr<InternetStackJson> internet;
    std::vector<std::shared_ptr<Ipv4NetworkJson>> ipv4Networks;
    std::vector<std::shared_ptr<Ipv6NetworkJson>> ipv6Networks;
    for (auto& jNode : jNodes)
    {
        auto nodeId = jNode.value<uint32_t>("nodeId", 0);
        json jIpv4RoutingProtocol, jIpv6RoutingProtocol, jMobility;
        std::vector<json> jApplication;
        for (auto& entry : jIpv4RoutingProtocols)
        {
            if (entry.value<uint32_t>("nodeId", 0) == nodeId)
            {
                jIpv4RoutingProtocol = entry;
            }
        }
        for (auto& entry : jIpv6RoutingProtocols)
        {
            if (entry.value<uint32_t>("nodeId", 0) == nodeId)
            {
                jIpv6RoutingProtocol = entry;
            }
        }
        for (auto& entry : jMobilitys)
        {
            if (entry.value<uint32_t>("nodeId", 0) == nodeId)
            {
                jMobility = entry;
            }
        }
        for (auto& entry : jApplications)
        {
            if (entry.value<uint32_t>("nodeId", 0) == nodeId)
            {
                jApplication.push_back(entry);
            }
        }
        nodes.push_back(
            njh.Build(jNode, jMobility, jIpv4RoutingProtocol, jIpv6RoutingProtocol, jApplication));
    }
    for (auto& jLink : jLinks)
    {
        links.push_back(ljh.Build(jLink));
    }
    internet = isjh.Build(jInternetStack);
    for (auto& jIpv4Network : jIpv4Networks)
    {
        ipv4Networks.push_back(i4njh.Build(jIpv4Network));
    }
    for (auto& jIpv6Network : jIpv6Networks)
    {
        ipv6Networks.push_back(i6njh.Build(jIpv6Network));
    }
    auto cfg = std::make_shared<ConfigJson>();
    cfg->SetNodes(nodes);
    cfg->SetLinks(links);
    cfg->SetInternetStack(internet);
    cfg->SetIpv4Networks(ipv4Networks);
    cfg->SetIpv6Networks(ipv6Networks);

    return cfg;
}

} // namespace ns3
