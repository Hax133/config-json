/**
 * @file link-json-helper.h
 * @brief Helper for constructing LinkJson and derived link classes from JSON.
 */

#ifndef LINK_JSON_HELPER_H
#define LINK_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>

#include "../model/link-json.h"

namespace ns3 {
using json = nlohmann::json;

/**
 * @class LinkJsonHelper
 * @brief Builds link objects (P2P / CSMA / WiFi) from JSON using existing NodeJson references.
 */
class LinkJsonHelper
{

public:

    std::shared_ptr<LinkJson> Build(const json& data);

private:
    std::shared_ptr<P2pQueueJson> BuildP2pQueue(const json& data);
    std::shared_ptr<CsmaQueueJson> BuildCsmaQueue(const json& data);

    std::shared_ptr<WifiPhyJson> BuildWifiPhy(const json& data);
    std::shared_ptr<WifiMacJson> BuildWifiMac(const json& data);
    std::shared_ptr<WifiChannelJson> BuildWifiChannel(const json& data);
    std::shared_ptr<WifiManagerJson> BuildWifiManager(const json& data);
    std::shared_ptr<WifiNetDeviceJson> BuildWifiNetDevice(const json& data, uint32_t linkId);
    std::shared_ptr<CsmaNetDeviceJson> BuildCsmaNetDevice(const json& data, uint32_t linkId);
    std::shared_ptr<P2pNetDeviceJson> BuildP2pNetDevice(const json& data, uint32_t linkId);

    std::shared_ptr<CsmaLinkJson> BuildCsmaLink(const json& data);
    std::shared_ptr<P2pLinkJson> BuildP2pLink(const json& data);
    std::shared_ptr<WifiLinkJson> BuildWifiLink(const json& data);

};

} // namespace ns3

#endif // LINK_JSON_HELPER_H
