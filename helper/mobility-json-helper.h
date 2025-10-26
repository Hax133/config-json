/**
 * @file mobility-json-helper.h
 * @brief Helper for constructing MobilityJson objects from JSON.
 */

#ifndef MOBILITY_JSON_HELPER_H
#define MOBILITY_JSON_HELPER_H

#include <memory>
#include <vector>
#include <boost/filesystem.hpp>
#include <nlohmann/json.hpp>
#include "../model/mobility-json.h"

namespace ns3 {
using json = nlohmann::json;
/**
 * @class MobilityJsonHelper
 * @brief Builds MobilityJson and subcomponents (MobilityModelJson, PositionAllocatorJson) from JSON.
 */
class MobilityJsonHelper
{
public:
    /**
     * @brief Build the mobility configuration for a specific node.
     * @return nullptr if not found.
     */
    std::shared_ptr<MobilityJson> Build(const json& j);

private:
    // === Mobility Model Builders ===
    std::shared_ptr<MobilityModelJson> BuildMobilityModel(const json& j);
    std::shared_ptr<ConstantPositionMobilityModelJson> BuildConstantPosition(const json& j);
    std::shared_ptr<RandomWalk2dMobilityModelJson> BuildRandomWalk2d(const json& j);
    std::shared_ptr<RandomWaypointMobilityModelJson> BuildRandomWaypoint(const json& j);
    std::shared_ptr<GaussMarkovMobilityModelJson> BuildGaussMarkov(const json& j);
    std::shared_ptr<ConstantVelocityMobilityModelJson> BuildConstantVelocity(const json& j);
    std::shared_ptr<ConstantAccelerationMobilityModelJson> BuildConstantAcceleration(const json& j);
    std::shared_ptr<WaypointMobilityModelJson> BuildWaypoint(const json& j);

    // === Position Allocator Builders ===
    std::shared_ptr<PositionAllocatorJson> BuildPositionAllocator(const json& j);
    std::shared_ptr<GridPositionAllocatorJson> BuildGridAllocator(const json& j);
    std::shared_ptr<RandomRectanglePositionAllocatorJson> BuildRandomRectangleAllocator(const json& j);
    std::shared_ptr<RandomDiscPositionAllocatorJson> BuildRandomDiscAllocator(const json& j);
    std::shared_ptr<ListPositionAllocatorJson> BuildListAllocator(const json& j);
    std::shared_ptr<UniformDiscPositionAllocatorJson> BuildUniformDiscAllocator(const json& j);

};

} // namespace ns3

#endif // MOBILITY_JSON_HELPER_H
