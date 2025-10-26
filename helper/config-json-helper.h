/**
 * @file config-json-helper.h
 * @brief Helper to construct a ConfigJson object from configuration files.
 */

#ifndef CONFIG_JSON_HELPER_H
#define CONFIG_JSON_HELPER_H

#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <memory>
#include "../model/config-json.h"

namespace ns3 {
using json = nlohmann::json;
/**
 * @class ConfigJsonHelper
 * @brief High-level helper to parse config.json and build all simulation components.
 */
class ConfigJsonHelper
{
public:
    /**
     * @brief Build all JSON submodules (nodes, links, addresses...) and return a unified ConfigJson.
     */
    std::shared_ptr<ConfigJson> Build(boost::filesystem::path path);

private:
    json LoadJson(boost::filesystem::path path);
};

} // namespace ns3

#endif // CONFIG_JSON_HELPER_H
