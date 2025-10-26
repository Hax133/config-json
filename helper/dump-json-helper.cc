#include "dump-json-helper.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace ns3
{

static std::string
Indent(int level)
{
    return std::string(level * 2, ' ');
}

DumpJsonHelper::DumpJsonHelper(std::shared_ptr<ConfigJson> config)
    : m_config(config)
{
}

void
DumpJsonHelper::PrintAll() const
{
    std::ostringstream oss;
    oss << "========== CONFIG JSON DUMP (Structured) ==========\n{\n";

    DumpNodes(oss, 1);
    oss << ",\n";
    DumpLinks(oss, 1);
    oss << ",\n";
    DumpIpv4Networks(oss, 1);
    oss << ",\n";
    DumpIpv6Networks(oss, 1);
    oss << ",\n";
    DumpInternetStack(oss, 1);
    oss << "}\n=====================================\n";
    std::cout << oss.str();
}

/**
 * Dump all nodes
 */
void
DumpJsonHelper::DumpNodes(std::ostream& os, int level) const
{
    const auto& nodes = m_config->GetNodes();
    os << Indent(level) << "\"nodes\": [\n";
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        const auto& node = nodes[i];
        os << Indent(level + 1) << "{\n";
        os << Indent(level + 2) << "\"nodeId\": " << node->GetNodeId() << ",\n";
        os << Indent(level + 2) << "\"role\": \"" << node->GetRole() << "\",\n";

        // === Applications ===
        os << Indent(level + 2) << "\"applications\": [\n";
        const auto& apps = node->GetApplications();
        for (size_t j = 0; j < apps.size(); ++j)
        {
            const auto& app = apps[j];
            os << Indent(level + 3) << "{ \"type\": \"" << app->GetType() << "\" }";
            if (j + 1 < apps.size())
                os << ",";
            os << "\n";
        }
        os << Indent(level + 2) << "],\n";

        // === Mobility ===
        if (auto mob = node->GetMobility())
        {
            os << Indent(level + 2) << "\"mobility\": {\n";
            os << Indent(level + 3) << "\"type\": \"" << mob->GetType() << "\"";
            if (auto model = mob->GetMobilityModel())
                os << ",\n"
                   << Indent(level + 3) << "\"mobilityModel\": \"" << model->GetType() << "\"";
            if (auto alloc = mob->GetPositionAllocator())
                os << ",\n"
                   << Indent(level + 3) << "\"positionAllocator\": \"" << alloc->GetType() << "\"";
            os << "\n" << Indent(level + 2) << "},\n";
        }

        // === IPv4 / IPv6 Routing ===
        os << Indent(level + 2) << "\"ipv4RoutingProtocols\": [\n";
        const auto& ipv4R = node->GetIpv4RoutingProtocols();
        for (size_t k = 0; k < ipv4R.size(); ++k)
        {
            const auto& proto = ipv4R[k];
            os << Indent(level + 3) << "{ \"type\": \"" << proto->GetType()
               << "\", \"priority\": " << proto->GetPriority() << " }";
            if (k + 1 < ipv4R.size())
                os << ",";
            os << "\n";
        }
        os << Indent(level + 2) << "],\n";

        os << Indent(level + 2) << "\"ipv6RoutingProtocols\": [\n";
        const auto& ipv6R = node->GetIpv6RoutingProtocols();
        for (size_t k = 0; k < ipv6R.size(); ++k)
        {
            const auto& proto = ipv6R[k];
            os << Indent(level + 3) << "{ \"type\": \"" << proto->GetType()
               << "\", \"priority\": " << proto->GetPriority() << " }";
            if (k + 1 < ipv6R.size())
                os << ",";
            os << "\n";
        }
        os << Indent(level + 2) << "]\n";

        os << Indent(level + 1) << "}";
        if (i + 1 < nodes.size())
            os << ",";
        os << "\n";
    }
    os << Indent(level) << "]";
}

/**
 * Dump link list
 */
void
DumpJsonHelper::DumpLinks(std::ostream& os, int level) const
{
    const auto& links = m_config->GetLinks();
    os << Indent(level) << "\"links\": [\n";
    for (size_t i = 0; i < links.size(); ++i)
    {
        const auto& link = links[i];
        os << Indent(level + 1) << "{\n";
        os << Indent(level + 2) << "\"linkId\": " << link->GetLinkId() << ",\n";
        os << Indent(level + 2) << "\"type\": \"" << link->GetType() << "\",\n";
        os << Indent(level + 2) << "\"netDevices\": [\n";
        const auto& devs = link->GetNetDevices();
        for (size_t j = 0; j < devs.size(); ++j)
        {
            const auto& d = devs[j];
            os << Indent(level + 3) << "{ \"netDeviceId\": "
               << " { \"nodeId\": " << (d->GetNetDeviceId()).nodeId
               << "  ,\"linkId\": " << (d->GetNetDeviceId()).linkId << " } }, \"type\": \""
               << d->GetType() << "\" }";
            if (j + 1 < devs.size())
                os << ",";
            os << "\n";
        }
        os << Indent(level + 2) << "]\n";
        os << Indent(level + 1) << "}";
        if (i + 1 < links.size())
            os << ",";
        os << "\n";
    }
    os << Indent(level) << "]";
}

/**
 * Dump IPv4 networks
 */
void
DumpJsonHelper::DumpIpv4Networks(std::ostream& os, int level) const
{
    const auto& ipv4s = m_config->GetIpv4Networks();
    os << Indent(level) << "\"ipv4Networks\": [\n";
    for (size_t i = 0; i < ipv4s.size(); ++i)
    {
        const auto& net = ipv4s[i];
        os << Indent(level + 1) << "{\n";
        os << Indent(level + 2) << "\"subnet\": \"" << net->GetSubnet() << "\",\n";
        os << Indent(level + 2) << "\"mask\": \"" << net->GetMask() << "\",\n";
        os << Indent(level + 2) << "\"fixed\": [\n";
        const auto& fixed = net->GetFixed();
        for (size_t j = 0; j < fixed.size(); ++j)
        {
            const auto& f = fixed[j];
            os << Indent(level + 3) << "{ \"netDeviceId\": "
               << " { \"nodeId\": " << (f->GetNetDeviceId()).nodeId
               << "  ,\"linkId\": " << (f->GetNetDeviceId()).linkId << " } }, \"ipv4\": \""
               << f->GetIpv4Address() << "\" }";
            if (j + 1 < fixed.size())
                os << ",";
            os << "\n";
        }
        os << Indent(level + 2) << "]\n";
        os << Indent(level + 1) << "}";
        if (i + 1 < ipv4s.size())
            os << ",";
        os << "\n";
    }
    os << Indent(level) << "]";
}

/**
 * Dump IPv6 networks
 */
void
DumpJsonHelper::DumpIpv6Networks(std::ostream& os, int level) const
{
    const auto& ipv6s = m_config->GetIpv6Networks();
    os << Indent(level) << "\"ipv6Networks\": [\n";
    for (size_t i = 0; i < ipv6s.size(); ++i)
    {
        const auto& net = ipv6s[i];
        os << Indent(level + 1) << "{\n";
        os << Indent(level + 2) << "\"subnet\": \"" << net->GetSubnet() << "\",\n";
        os << Indent(level + 2) << "\"prefixLength\": " << net->GetPrefixLength() << ",\n";
        os << Indent(level + 2) << "\"fixed\": [\n";
        const auto& fixed = net->GetFixed();
        for (size_t j = 0; j < fixed.size(); ++j)
        {
            const auto& f = fixed[j];
            os << Indent(level + 3) << "{ \"netDeviceId\": "
               << " { \"nodeId\": " << (f->GetNetDeviceId()).nodeId
               << "  ,\"linkId\": " << (f->GetNetDeviceId()).linkId << " } }, \"ipv6\": \""
               << f->GetIpv6Address() << "\" }";
            if (j + 1 < fixed.size())
                os << ",";
            os << "\n";
        }
        os << Indent(level + 2) << "]\n";
        os << Indent(level + 1) << "}";
        if (i + 1 < ipv6s.size())
            os << ",";
        os << "\n";
    }
    os << Indent(level) << "]";
}

/**
 * Dump InternetStack
 */
void
DumpJsonHelper::DumpInternetStack(std::ostream& os, int level) const
{
    if (auto stack = m_config->GetInternetStack())
    {
        os << Indent(level) << "\"internetStack\": {\n";

        if (auto ipv4 = stack->GetIpv4())
            os << Indent(level + 1) << "\"ipv4\": { \"defaultTtl\": " << ipv4->GetDefaultTtl()
               << ", \"ipForward\": " << (ipv4->GetIpForward() ? "true" : "false")
               << ", \"enableChecksum\": " << (ipv4->GetEnableChecksum() ? "true" : "false")
               << " },\n";

        if (auto ipv6 = stack->GetIpv6())
            os << Indent(level + 1) << "\"ipv6\": { \"defaultTtl\": " << ipv6->GetDefaultTtl()
               << ", \"ipForward\": " << (ipv6->GetIpForward() ? "true" : "false")
               << ", \"enableChecksum\": " << (ipv6->GetEnableChecksum() ? "true" : "false")
               << " },\n";

        if (auto udp = stack->GetUdp())
            os << Indent(level + 1)
               << "\"udp\": { \"enableChecksum\": " << (udp->GetEnableChecksum() ? "true" : "false")
               << " },\n";

        if (auto tcp = stack->GetTcp())
            os << Indent(level + 1) << "\"tcp\": { \"variant\": \"" << tcp->GetVariant()
               << "\" }\n";

        os << Indent(level) << "}";
    }
}

} // namespace ns3
