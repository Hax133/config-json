/**
 * @file node-json-helper.h
 * @brief Helper for constructing NodeJson and all its dependent objects from JSON.
 */

#ifndef NODE_JSON_HELPER_H
#define NODE_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>

#include "../model/node-json.h"
#include "mobility-json-helper.h"
#include "application-json-helper.h"
#include "ipv4-routing-protocol-json-helper.h"
#include "ipv6-routing-protocol-json-helper.h"

namespace ns3 {
using json = nlohmann::json;
/**
 * @class NodeJsonHelper
 * @brief Recursively builds NodeJson and all sub-layer configurations.
 */
class NodeJsonHelper
{

public:
    /**
     * @brief Build a single node by nodeId.
     */
    std::shared_ptr<NodeJson> Build(const json& jn,
                      const json& jm,
                      const json& j4rs,
                      const json& j6rs,
                      const std::vector<json>& jas);


private:

};

} // namespace ns3

#endif // NODE_JSON_HELPER_H
