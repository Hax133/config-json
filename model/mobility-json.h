/**
 * @file mobility-json.h
 * @brief Definition of MobilityJson and all related mobility and position allocator classes.
 */

#ifndef MOBILITY_JSON_H
#define MOBILITY_JSON_H

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace ns3
{

/**
 * @brief  class for all mobility model JSON representations.
 */
class MobilityModelJson
{
  public:
    virtual ~MobilityModelJson() = default;
    void SetType(const std::string& type);
    const std::string& GetType() const;

  private:
    std::string m_type;
};

/**
 * @brief Constant position mobility model.
 */
class ConstantPositionMobilityModelJson : public MobilityModelJson
{
  public:
    void SetPositionX(double x);
    void SetPositionY(double y);
    void SetPositionZ(double z);

    double GetPositionX() const;
    double GetPositionY() const;
    double GetPositionZ() const;

  private:
    double m_positionX = 0.0;
    double m_positionY = 0.0;
    double m_positionZ = 0.0;
};

/**
 * @brief Random walk mobility model (2D).
 */
class RandomWalk2dMobilityModelJson : public MobilityModelJson
{
  public:
    void SetBounds(const std::string& bounds);
    void SetSpeed(const std::string& speed);
    void SetDistance(double distance);

    const std::string& GetBounds() const;
    const std::string& GetSpeed() const;
    double GetDistance() const;
    void SetXMin(double xMin);
    void SetXMax(double xMax);
    void SetYMin(double yMin);
    void SetYMax(double yMax);

    double GetXMin() const;
    double GetXMax() const;
    double GetYMin() const;
    double GetYMax() const;

  private:
    std::string m_bounds;
    double m_xMin = 0.0;
    double m_xMax = 0.0;
    double m_yMin = 0.0;
    double m_yMax = 0.0;
    std::string m_speed;
    double m_distance = 0.0;
};

/**
 * @brief Random waypoint mobility model.
 */
class RandomWaypointMobilityModelJson : public MobilityModelJson
{
  public:
    void SetSpeed(const std::string& speed);
    void SetPause(const std::string& pause);
    void SetPositionAllocator(const std::string& allocator);

    const std::string& GetSpeed() const;
    const std::string& GetPause() const;
    const std::string& GetPositionAllocator() const;

  private:
    std::string m_speed;
    std::string m_pause;
    std::string m_positionAllocator;
};

/**
 * @brief Gauss-Markov mobility model.
 */
class GaussMarkovMobilityModelJson : public MobilityModelJson
{
  public:
    void SetMeanVelocity(double v);
    void SetMeanDirection(double d);
    void SetMeanPitch(double p);
    void SetNormalVelocity(double v);
    void SetNormalDirection(double d);
    void SetNormalPitch(double p);
    void SetTimeStep(double step);
    void SetAlpha(double alpha);
    void SetBounds(const std::string& bounds);

    double GetMeanVelocity() const;
    double GetMeanDirection() const;
    double GetMeanPitch() const;
    double GetNormalVelocity() const;
    double GetNormalDirection() const;
    double GetNormalPitch() const;
    double GetTimeStep() const;
    double GetAlpha() const;
    const std::string& GetBounds() const;

  private:
    double m_meanVelocity = 0.0;
    double m_meanDirection = 0.0;
    double m_meanPitch = 0.0;
    double m_normalVelocity = 0.0;
    double m_normalDirection = 0.0;
    double m_normalPitch = 0.0;
    double m_timeStep = 0.0;
    double m_alpha = 0.0;
    std::string m_bounds;
};

/**
 * @brief Constant velocity mobility model.
 */
class ConstantVelocityMobilityModelJson : public MobilityModelJson
{
  public:
    void SetVelocityX(double vx);
    void SetVelocityY(double vy);
    void SetVelocityZ(double vz);

    double GetVelocityX() const;
    double GetVelocityY() const;
    double GetVelocityZ() const;

  private:
    double m_velocityX = 0.0;
    double m_velocityY = 0.0;
    double m_velocityZ = 0.0;
};

/**
 * @brief Constant acceleration mobility model.
 */
class ConstantAccelerationMobilityModelJson : public MobilityModelJson
{
  public:
    void SetAccelerationX(double ax);
    void SetAccelerationY(double ay);
    void SetAccelerationZ(double az);
    void SetVelocityX(double vx);
    void SetVelocityY(double vy);
    void SetVelocityZ(double vz);

    double GetAccelerationX() const;
    double GetAccelerationY() const;
    double GetAccelerationZ() const;
    double GetVelocityX() const;
    double GetVelocityY() const;
    double GetVelocityZ() const;

  private:
    double m_accelerationX = 0.0;
    double m_accelerationY = 0.0;
    double m_accelerationZ = 0.0;
    double m_velocityX = 0.0;
    double m_velocityY = 0.0;
    double m_velocityZ = 0.0;
};

/**
 * @brief Waypoint structure.
 */
struct WaypointJson
{
    double m_time;
    double m_x;
    double m_y;
    double m_z;
};

/**
 * @brief Waypoint-d mobility model.
 */
class WaypointMobilityModelJson : public MobilityModelJson
{
  public:
    void SetWaypoints(const std::vector<WaypointJson>& waypoints);
    const std::vector<WaypointJson>& GetWaypoints() const;

  private:
    std::vector<WaypointJson> m_waypoints;
};

/**
 * @brief  class for position allocator JSONs.
 */
class PositionAllocatorJson
{
  public:
    virtual ~PositionAllocatorJson() = default;
    void SetType(const std::string& type);
    const std::string& GetType() const;

  private:
    std::string m_type;
};

/**
 * @brief Grid position allocator.
 */
class GridPositionAllocatorJson : public PositionAllocatorJson
{
  public:
    void SetMinX(double minX);
    void SetMinY(double minY);
    void SetDeltaX(double deltaX);
    void SetDeltaY(double deltaY);
    void SetGridWidth(uint32_t width);
    void SetLayoutType(const std::string& layout);

    double GetMinX() const;
    double GetMinY() const;
    double GetDeltaX() const;
    double GetDeltaY() const;
    uint32_t GetGridWidth() const;
    const std::string& GetLayoutType() const;

  private:
    double m_minX = 0.0;
    double m_minY = 0.0;
    double m_deltaX = 0.0;
    double m_deltaY = 0.0;
    uint32_t m_gridWidth = 0;
    std::string m_layoutType;
};

/**
 * @brief Random rectangle position allocator.
 */
class RandomRectanglePositionAllocatorJson : public PositionAllocatorJson
{
  public:
    void SetXMin(double xMin);
    void SetXMax(double xMax);
    void SetYMin(double yMin);
    void SetYMax(double yMax);

    double GetXMin() const;
    double GetXMax() const;
    double GetYMin() const;
    double GetYMax() const;

  private:
    double m_xMin = 0.0;
    double m_xMax = 0.0;
    double m_yMin = 0.0;
    double m_yMax = 0.0;
};

/**
 * @brief Random disc position allocator.
 */
class RandomDiscPositionAllocatorJson : public PositionAllocatorJson
{
  public:
    void SetX(double x);
    void SetY(double y);
    void SetRho(double rho);

    double GetX() const;
    double GetY() const;
    double GetRho() const;

  private:
    double m_x = 0.0;
    double m_y = 0.0;
    double m_rho = 0.0;
};

/**
 * @brief List position allocator.
 */
class ListPositionAllocatorJson : public PositionAllocatorJson
{
  public:
    void SetPositions(const std::vector<std::array<double, 3>>& positions);
    const std::vector<std::array<double, 3>>& GetPositions() const;

  private:
    std::vector<std::array<double, 3>> m_positions;
};

/**
 * @brief Uniform disc position allocator.
 */
class UniformDiscPositionAllocatorJson : public PositionAllocatorJson
{
  public:
    void SetX(double x);
    void SetY(double y);
    void SetRadius(double r);

    double GetX() const;
    double GetY() const;
    double GetRadius() const;

  private:
    double m_x = 0.0;
    double m_y = 0.0;
    double m_radius = 0.0;
};

/**
 * @brief Top-level mobility configuration object.
 */
class MobilityJson
{
  public:
    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetMobilityModel(const std::shared_ptr<MobilityModelJson>& model);
    std::shared_ptr<MobilityModelJson> GetMobilityModel() const;

    void SetPositionAllocator(const std::shared_ptr<PositionAllocatorJson>& allocator);
    std::shared_ptr<PositionAllocatorJson> GetPositionAllocator() const;

  private:
    std::string m_type;
    std::shared_ptr<MobilityModelJson> m_mobilityModel;
    std::shared_ptr<PositionAllocatorJson> m_positionAllocator;
};

} // namespace ns3

#endif // MOBILITY_JSON_H
