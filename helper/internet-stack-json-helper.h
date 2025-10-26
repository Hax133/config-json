/**
 * @file transport-json-helper.h
 * @brief Helper for constructing TCP/UDP L4 protocol JSON objects.
 */

#ifndef INTERNET_STACK_JSON_HELPER_H
#define INTERNET_STACK_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../model/internet-stack-json.h"
namespace ns3 {
using json = nlohmann::json;
/**
 * @class InternetStackJsonHelper
 * @brief Builds TCP and UDP L4 protocol configuration objects from JSON.
 */
class InternetStackJsonHelper
{
public:
    std::shared_ptr<InternetStackJson> Build(const json& j);

private:
    std::shared_ptr<Ipv4L3ProtocolJson> BuildIpv4(const json & j);

    std::shared_ptr<Ipv6L3ProtocolJson> BuildIpv6(const json & j);

    std::shared_ptr<TcpL4ProtocolJson> BuildTcp(const json & j);

    std::shared_ptr<UdpL4ProtocolJson> BuildUdp(const json & j);
};

} // namespace ns3

#endif // TRANSPORT_JSON_HELPER_H
