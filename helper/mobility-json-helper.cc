#include "mobility-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

using json = nlohmann::json;

std::shared_ptr<MobilityJson>
MobilityJsonHelper::Build(const json& data)
{
    auto mobility = std::make_shared<MobilityJson>();
    auto type = data.value("type", "");
    mobility->SetType(type);
    if (type == "ns3")
    {
        mobility->SetPositionAllocator(
            BuildPositionAllocator(data.value("positionAllocator", json::object())));
        mobility->SetMobilityModel(BuildMobilityModel(data.value("mobilityModel", json::object())));
    }
    return mobility;
}

/**
 * ===========================
 *  Mobility Model Buildrs
 * ===========================
 */
std::shared_ptr<MobilityModelJson>
MobilityJsonHelper::BuildMobilityModel(const json& j)
{
    std::string type = j.value("type", "");
    std::shared_ptr<MobilityModelJson> model;
    if (type == "ConstantPositionMobilityModel")
        model = BuildConstantPosition(j);
    else if (type == "RandomWalk2dMobilityModel")
        model = BuildRandomWalk2d(j);
    else if (type == "RandomWaypointMobilityModel")
        model = BuildRandomWaypoint(j);
    else if (type == "GaussMarkovMobilityModel")
        model = BuildGaussMarkov(j);
    else if (type == "ConstantVelocityMobilityModel")
        model = BuildConstantVelocity(j);
    else if (type == "ConstantAccelerationMobilityModel")
        model = BuildConstantAcceleration(j);
    else if (type == "WaypointMobilityModel")
        model = BuildWaypoint(j);
    else
    {
        std::cerr << "[Warning] Unknown mobility model type: " << type << std::endl;
        return nullptr;
    }
    model->SetType(type);
    return model;
}

std::shared_ptr<ConstantPositionMobilityModelJson>
MobilityJsonHelper::BuildConstantPosition(const json& j)
{
    auto model = std::make_shared<ConstantPositionMobilityModelJson>();
    model->SetPositionX(j.value("x", 0.0));
    model->SetPositionY(j.value("y", 0.0));
    model->SetPositionZ(j.value("z", 0.0));
    return model;
}

std::shared_ptr<RandomWalk2dMobilityModelJson>
MobilityJsonHelper::BuildRandomWalk2d(const json& j)
{
    auto model = std::make_shared<RandomWalk2dMobilityModelJson>();
    model->SetXMin(j.value("minX", 0.0));
    model->SetXMax(j.value("maxX", 0.0));
    model->SetYMin(j.value("minY", 0.0));
    model->SetYMax(j.value("maxY", 0.0));
    model->SetSpeed(j.value("speed", ""));
    model->SetDistance(j.value("distance", 0.0));
    return model;
}

std::shared_ptr<RandomWaypointMobilityModelJson>
MobilityJsonHelper::BuildRandomWaypoint(const json& j)
{
    auto model = std::make_shared<RandomWaypointMobilityModelJson>();
    model->SetSpeed(j.value("speed", ""));
    model->SetPause(j.value("pause", ""));
    model->SetPositionAllocator(j.value("positionAllocator", ""));
    return model;
}

std::shared_ptr<GaussMarkovMobilityModelJson>
MobilityJsonHelper::BuildGaussMarkov(const json& j)
{
    auto model = std::make_shared<GaussMarkovMobilityModelJson>();
    model->SetMeanVelocity(j.value("meanVelocity", 0.0));
    model->SetMeanDirection(j.value("meanDirection", 0.0));
    model->SetMeanPitch(j.value("meanPitch", 0.0));
    model->SetNormalVelocity(j.value("normalVelocity", 0.0));
    model->SetNormalDirection(j.value("normalDirection", 0.0));
    model->SetNormalPitch(j.value("normalPitch", 0.0));
    model->SetTimeStep(j.value("timeStep", 0.0));
    model->SetAlpha(j.value("alpha", 0.0));
    model->SetBounds(j.value("bounds", ""));
    return model;
}

std::shared_ptr<ConstantVelocityMobilityModelJson>
MobilityJsonHelper::BuildConstantVelocity(const json& j)
{
    auto model = std::make_shared<ConstantVelocityMobilityModelJson>();
    model->SetVelocityX(j.value("velocityX", 0.0));
    model->SetVelocityY(j.value("velocityY", 0.0));
    model->SetVelocityZ(j.value("velocityZ", 0.0));
    return model;
}

std::shared_ptr<ConstantAccelerationMobilityModelJson>
MobilityJsonHelper::BuildConstantAcceleration(const json& j)
{
    auto model = std::make_shared<ConstantAccelerationMobilityModelJson>();
    model->SetAccelerationX(j.value("accelerationX", 0.0));
    model->SetAccelerationY(j.value("accelerationY", 0.0));
    model->SetAccelerationZ(j.value("accelerationZ", 0.0));
    model->SetVelocityX(j.value("velocityX", 0.0));
    model->SetVelocityY(j.value("velocityY", 0.0));
    model->SetVelocityZ(j.value("velocityZ", 0.0));
    return model;
}

std::shared_ptr<WaypointMobilityModelJson>
MobilityJsonHelper::BuildWaypoint(const json& j)
{
    auto model = std::make_shared<WaypointMobilityModelJson>();
    std::vector<WaypointJson> points;

    if (j.contains("waypoints") && j["waypoints"].is_array())
    {
        for (const auto& wp : j["waypoints"])
        {
            WaypointJson p{};
            p.m_time = wp.value("time", 0.0);
            p.m_x = wp.value("x", 0.0);
            p.m_y = wp.value("y", 0.0);
            p.m_z = wp.value("z", 0.0);
            points.push_back(p);
        }
    }
    model->SetWaypoints(points);
    return model;
}

/**
 * ===========================
 *  Position Allocator Buildrs
 * ===========================
 */
std::shared_ptr<PositionAllocatorJson>
MobilityJsonHelper::BuildPositionAllocator(const json& j)
{
    std::string type = j.value("type", "");
    std::shared_ptr<PositionAllocatorJson> allocator;
    if (type == "GridPositionAllocator")
        allocator = BuildGridAllocator(j);
    else if (type == "RandomRectanglePositionAllocator")
        allocator = BuildRandomRectangleAllocator(j);
    else if (type == "RandomDiscPositionAllocator")
        allocator = BuildRandomDiscAllocator(j);
    else if (type == "ListPositionAllocator")
        allocator = BuildListAllocator(j);
    else if (type == "UniformDiscPositionAllocator")
        allocator = BuildUniformDiscAllocator(j);
    else
    {
        std::cerr << "[Warning] Unknown PositionAllocator type: " << type << std::endl;
        return nullptr;
    }
    std::shared_ptr<MobilityModelJson> model;
    allocator->SetType(type);
    return allocator;
}

std::shared_ptr<GridPositionAllocatorJson>
MobilityJsonHelper::BuildGridAllocator(const json& j)
{
    auto alloc = std::make_shared<GridPositionAllocatorJson>();
    alloc->SetMinX(j.value("minX", 0.0));
    alloc->SetMinY(j.value("minY", 0.0));
    alloc->SetDeltaX(j.value("deltaX", 0.0));
    alloc->SetDeltaY(j.value("deltaY", 0.0));
    alloc->SetGridWidth(j.value("gridWidth", 0));
    alloc->SetLayoutType(j.value("layoutType", ""));
    return alloc;
}

std::shared_ptr<RandomRectanglePositionAllocatorJson>
MobilityJsonHelper::BuildRandomRectangleAllocator(const json& j)
{
    auto alloc = std::make_shared<RandomRectanglePositionAllocatorJson>();
    alloc->SetXMin(j.value("minX", 0.0));
    alloc->SetXMax(j.value("maxX", 0.0));
    alloc->SetYMin(j.value("minY", 0.0));
    alloc->SetYMax(j.value("maxY", 0.0));
    return alloc;
}

std::shared_ptr<RandomDiscPositionAllocatorJson>
MobilityJsonHelper::BuildRandomDiscAllocator(const json& j)
{
    auto alloc = std::make_shared<RandomDiscPositionAllocatorJson>();
    alloc->SetX(j.value("x", 0.0));
    alloc->SetY(j.value("y", 0.0));
    alloc->SetRho(j.value("rho", 0.0));
    return alloc;
}

std::shared_ptr<ListPositionAllocatorJson>
MobilityJsonHelper::BuildListAllocator(const json& j)
{
    auto alloc = std::make_shared<ListPositionAllocatorJson>();
    std::vector<std::array<double, 3>> positions;
    if (j.contains("positions") && j["positions"].is_array())
    {
        for (const auto& p : j["positions"])
        {
            positions.push_back({p.value("x", 0.0), p.value("y", 0.0), p.value("z", 0.0)});
        }
    }
    alloc->SetPositions(positions);
    return alloc;
}

std::shared_ptr<UniformDiscPositionAllocatorJson>
MobilityJsonHelper::BuildUniformDiscAllocator(const json& j)
{
    auto alloc = std::make_shared<UniformDiscPositionAllocatorJson>();
    alloc->SetX(j.value("x", 0.0));
    alloc->SetY(j.value("x", 0.0));
    alloc->SetRadius(j.value("radius", 0.0));
    return alloc;
}

} // namespace ns3
