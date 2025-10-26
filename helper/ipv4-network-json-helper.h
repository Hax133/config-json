#ifndef IPV4_NETWORK_JSON_HELPER_H
#define IPV4_NETWORK_JSON_HELPER_H

#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

#include "../model/ipv4-network-json.h"
#include "../model/link-json.h"

namespace ns3 {
using json = nlohmann::json;
/**
 * @class Ipv4NetworkJsonHelper
 * @brief Helper for building Ipv4NetworkJson objects.
 */
class Ipv4NetworkJsonHelper
{
public:

    std::shared_ptr<Ipv4NetworkJson> Build(json & j);

};

}

#endif