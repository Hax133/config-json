#ifndef SIMULATOR_JSON_HELPER_H
#define SIMULATOR_JSON_HELPER_H

#include "../model/config-json.h"

#include "ns3/applications-module.h"
#include "ns3/bridge-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/olsr-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/spectrum-helper.h"
#include "ns3/spectrum-wifi-helper.h"
#include "ns3/wifi-module.h"

#include <boost/filesystem.hpp>
#include <memory>
#include <nlohmann/json.hpp>
#include <vector>

namespace ns3
{

class SimulatorJsonHelper
{
  public:
    void InstallLink(std::shared_ptr<LinkJson> link);
    void InstallRole(std::shared_ptr<NodeJson> nodeJson);
    void InstallIpv4Network(std::shared_ptr<Ipv4NetworkJson> ipv4Network);
    void InstallIpv6Network(std::shared_ptr<Ipv6NetworkJson> ipv6Network);
    void InstallInternet(std::shared_ptr<InternetStackJson> internet,
                         std::vector<std::shared_ptr<NodeJson>> nodeList);
    void InstallIpv4Routing(std::shared_ptr<NodeJson> nodeJson);
    void InstallIpv6Routing(std::shared_ptr<NodeJson> nodeJson);
    void InstallMobility(std::shared_ptr<NodeJson> nodeJson);
    void InstallApplications(std::shared_ptr<NodeJson> nodeJson);
    void Install(std::shared_ptr<ConfigJson> cfg);
    void DumpNetDevicesMap();
    void EnablePcapAuto(const std::string& prefix,
                        const std::vector<uint32_t>& linkIdsToTrace,
                        bool promiscuous = true);
    const std::map<uint32_t, std::map<uint32_t, Ptr<NetDevice>>>& GetNetDevicesMap() const;

  private:
    std::map<uint32_t, std::map<uint32_t, Ptr<NetDevice>>> m_netDevices;
};

} // namespace ns3

#endif