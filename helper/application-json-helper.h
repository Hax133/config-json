/**
 * @file application-json-helper.h
 * @brief Helper for constructing ApplicationJson objects from JSON.
 */

#ifndef APPLICATION_JSON_HELPER_H
#define APPLICATION_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../model/application-json.h"

namespace ns3 {
using json = nlohmann::json;
/**
 * @class ApplicationJsonHelper
 * @brief Build ApplicationJson (and derived) instances per node.
 */
class ApplicationJsonHelper
{
public:
    /**
     * @brief Build all ApplicationJson objects for a given node.
     */
    std::shared_ptr<ApplicationJson> Build(const json & j);

private:

    // === internal factory helpers ===
    std::shared_ptr<SocketJson> BuildSocket(const json& j);
    std::shared_ptr<OnOffJson> BuildOnOff(const json& entry);
    std::shared_ptr<UdpEchoServerJson> BuildUdpEchoServer(const json& entry);
    std::shared_ptr<UdpEchoClientJson> BuildUdpEchoClient(const json& entry);
    std::shared_ptr<PacketSinkJson> BuildPacketSink(const json& entry);

};

} // namespace ns3

#endif // APPLICATION_JSON_HELPER_H
