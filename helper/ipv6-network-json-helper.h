#ifndef IPV6_NETWORK_JSON_HELPER_H
#define IPV6_NETWORK_JSON_HELPER_H

#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include <memory>
#include <vector>

#include "../model/ipv6-network-json.h"
#include "../model/link-json.h"

namespace ns3 {
using json = nlohmann::json;
/**
 * @class Ipv6NetworkJsonHelper
 * @brief Helper for building Ipv6NetworkJson objects.
 */
class Ipv6NetworkJsonHelper
{
public:

    std::shared_ptr<Ipv6NetworkJson> Build(json & j);

};

}

#endif