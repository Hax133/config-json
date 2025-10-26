#include "mobility-json.h"

namespace ns3 {

void MobilityModelJson::SetType(const std::string& type) { m_type = type; }
const std::string& MobilityModelJson::GetType() const { return m_type; }

void PositionAllocatorJson::SetType(const std::string& type) { m_type = type; }
const std::string& PositionAllocatorJson::GetType() const { return m_type; }

// === ConstantPositionMobilityModelJson ===
void ConstantPositionMobilityModelJson::SetPositionX(double x){ m_positionX=x; }
void ConstantPositionMobilityModelJson::SetPositionY(double y){ m_positionY=y; }
void ConstantPositionMobilityModelJson::SetPositionZ(double z){ m_positionZ=z; }
double ConstantPositionMobilityModelJson::GetPositionX() const{ return m_positionX; }
double ConstantPositionMobilityModelJson::GetPositionY() const{ return m_positionY; }
double ConstantPositionMobilityModelJson::GetPositionZ() const{ return m_positionZ; }

// === RandomWalk2dMobilityModelJson ===
void RandomWalk2dMobilityModelJson::SetBounds(const std::string& b){ m_bounds=b; }
void RandomWalk2dMobilityModelJson::SetSpeed(const std::string& s){ m_speed=s; }
void RandomWalk2dMobilityModelJson::SetDistance(double d){ m_distance=d; }
const std::string& RandomWalk2dMobilityModelJson::GetBounds() const{ return m_bounds; }
const std::string& RandomWalk2dMobilityModelJson::GetSpeed() const{ return m_speed; }
double RandomWalk2dMobilityModelJson::GetDistance() const{ return m_distance; }

void RandomWalk2dMobilityModelJson::SetXMin(double x){ m_xMin=x; }
void RandomWalk2dMobilityModelJson::SetXMax(double x){ m_xMax=x; }
void RandomWalk2dMobilityModelJson::SetYMin(double y){ m_yMin=y; }
void RandomWalk2dMobilityModelJson::SetYMax(double y){ m_yMax=y; }
double RandomWalk2dMobilityModelJson::GetXMin() const{ return m_xMin; }
double RandomWalk2dMobilityModelJson::GetXMax() const{ return m_xMax; }
double RandomWalk2dMobilityModelJson::GetYMin() const{ return m_yMin; }
double RandomWalk2dMobilityModelJson::GetYMax() const{ return m_yMax; }

// === RandomWaypointMobilityModelJson ===
void RandomWaypointMobilityModelJson::SetSpeed(const std::string& s){ m_speed=s; }
void RandomWaypointMobilityModelJson::SetPause(const std::string& p){ m_pause=p; }
void RandomWaypointMobilityModelJson::SetPositionAllocator(const std::string& a){ m_positionAllocator=a; }
const std::string& RandomWaypointMobilityModelJson::GetSpeed() const{ return m_speed; }
const std::string& RandomWaypointMobilityModelJson::GetPause() const{ return m_pause; }
const std::string& RandomWaypointMobilityModelJson::GetPositionAllocator() const{ return m_positionAllocator; }

// === GaussMarkovMobilityModelJson ===
void GaussMarkovMobilityModelJson::SetMeanVelocity(double v){ m_meanVelocity=v; }
void GaussMarkovMobilityModelJson::SetMeanDirection(double d){ m_meanDirection=d; }
void GaussMarkovMobilityModelJson::SetMeanPitch(double p){ m_meanPitch=p; }
void GaussMarkovMobilityModelJson::SetNormalVelocity(double v){ m_normalVelocity=v; }
void GaussMarkovMobilityModelJson::SetNormalDirection(double d){ m_normalDirection=d; }
void GaussMarkovMobilityModelJson::SetNormalPitch(double p){ m_normalPitch=p; }
void GaussMarkovMobilityModelJson::SetTimeStep(double s){ m_timeStep=s; }
void GaussMarkovMobilityModelJson::SetAlpha(double a){ m_alpha=a; }
void GaussMarkovMobilityModelJson::SetBounds(const std::string& b){ m_bounds=b; }

double GaussMarkovMobilityModelJson::GetMeanVelocity() const{ return m_meanVelocity; }
double GaussMarkovMobilityModelJson::GetMeanDirection() const{ return m_meanDirection; }
double GaussMarkovMobilityModelJson::GetMeanPitch() const{ return m_meanPitch; }
double GaussMarkovMobilityModelJson::GetNormalVelocity() const{ return m_normalVelocity; }
double GaussMarkovMobilityModelJson::GetNormalDirection() const{ return m_normalDirection; }
double GaussMarkovMobilityModelJson::GetNormalPitch() const{ return m_normalPitch; }
double GaussMarkovMobilityModelJson::GetTimeStep() const{ return m_timeStep; }
double GaussMarkovMobilityModelJson::GetAlpha() const{ return m_alpha; }
const std::string& GaussMarkovMobilityModelJson::GetBounds() const{ return m_bounds; }

// === ConstantVelocityMobilityModelJson ===
void ConstantVelocityMobilityModelJson::SetVelocityX(double x){ m_velocityX=x; }
void ConstantVelocityMobilityModelJson::SetVelocityY(double y){ m_velocityY=y; }
void ConstantVelocityMobilityModelJson::SetVelocityZ(double z){ m_velocityZ=z; }
double ConstantVelocityMobilityModelJson::GetVelocityX() const{ return m_velocityX; }
double ConstantVelocityMobilityModelJson::GetVelocityY() const{ return m_velocityY; }
double ConstantVelocityMobilityModelJson::GetVelocityZ() const{ return m_velocityZ; }

// === ConstantAccelerationMobilityModelJson ===
void ConstantAccelerationMobilityModelJson::SetAccelerationX(double x){ m_accelerationX=x; }
void ConstantAccelerationMobilityModelJson::SetAccelerationY(double y){ m_accelerationY=y; }
void ConstantAccelerationMobilityModelJson::SetAccelerationZ(double z){ m_accelerationZ=z; }
void ConstantAccelerationMobilityModelJson::SetVelocityX(double x){ m_velocityX=x; }
void ConstantAccelerationMobilityModelJson::SetVelocityY(double y){ m_velocityY=y; }
void ConstantAccelerationMobilityModelJson::SetVelocityZ(double z){ m_velocityZ=z; }
double ConstantAccelerationMobilityModelJson::GetAccelerationX() const{ return m_accelerationX; }
double ConstantAccelerationMobilityModelJson::GetAccelerationY() const{ return m_accelerationY; }
double ConstantAccelerationMobilityModelJson::GetAccelerationZ() const{ return m_accelerationZ; }
double ConstantAccelerationMobilityModelJson::GetVelocityX() const{ return m_velocityX; }
double ConstantAccelerationMobilityModelJson::GetVelocityY() const{ return m_velocityY; }
double ConstantAccelerationMobilityModelJson::GetVelocityZ() const{ return m_velocityZ; }

// === WaypointMobilityModelJson ===
void WaypointMobilityModelJson::SetWaypoints(const std::vector<WaypointJson>& w){ m_waypoints=w; }
const std::vector<WaypointJson>& WaypointMobilityModelJson::GetWaypoints() const{ return m_waypoints; }

// === GridPositionAllocatorJson ===
void GridPositionAllocatorJson::SetMinX(double x){ m_minX=x; }
void GridPositionAllocatorJson::SetMinY(double y){ m_minY=y; }
void GridPositionAllocatorJson::SetDeltaX(double dx){ m_deltaX=dx; }
void GridPositionAllocatorJson::SetDeltaY(double dy){ m_deltaY=dy; }
void GridPositionAllocatorJson::SetGridWidth(uint32_t w){ m_gridWidth=w; }
void GridPositionAllocatorJson::SetLayoutType(const std::string& l){ m_layoutType=l; }
double GridPositionAllocatorJson::GetMinX() const{ return m_minX; }
double GridPositionAllocatorJson::GetMinY() const{ return m_minY; }
double GridPositionAllocatorJson::GetDeltaX() const{ return m_deltaX; }
double GridPositionAllocatorJson::GetDeltaY() const{ return m_deltaY; }
uint32_t GridPositionAllocatorJson::GetGridWidth() const{ return m_gridWidth; }
const std::string& GridPositionAllocatorJson::GetLayoutType() const{ return m_layoutType; }

// === RandomRectanglePositionAllocatorJson ===
void RandomRectanglePositionAllocatorJson::SetXMin(double x){ m_xMin=x; }
void RandomRectanglePositionAllocatorJson::SetXMax(double x){ m_xMax=x; }
void RandomRectanglePositionAllocatorJson::SetYMin(double y){ m_yMin=y; }
void RandomRectanglePositionAllocatorJson::SetYMax(double y){ m_yMax=y; }
double RandomRectanglePositionAllocatorJson::GetXMin() const{ return m_xMin; }
double RandomRectanglePositionAllocatorJson::GetXMax() const{ return m_xMax; }
double RandomRectanglePositionAllocatorJson::GetYMin() const{ return m_yMin; }
double RandomRectanglePositionAllocatorJson::GetYMax() const{ return m_yMax; }

// === RandomDiscPositionAllocatorJson ===
void RandomDiscPositionAllocatorJson::SetX(double x){ m_x=x; }
void RandomDiscPositionAllocatorJson::SetY(double y){ m_y=y; }
void RandomDiscPositionAllocatorJson::SetRho(double r){ m_rho=r; }
double RandomDiscPositionAllocatorJson::GetX() const{ return m_x; }
double RandomDiscPositionAllocatorJson::GetY() const{ return m_y; }
double RandomDiscPositionAllocatorJson::GetRho() const{ return m_rho; }

// === ListPositionAllocatorJson ===
void ListPositionAllocatorJson::SetPositions(const std::vector<std::array<double,3>>& p){ m_positions=p; }
const std::vector<std::array<double,3>>& ListPositionAllocatorJson::GetPositions() const{ return m_positions; }

// === UniformDiscPositionAllocatorJson ===
void UniformDiscPositionAllocatorJson::SetX(double x){ m_x=x; }
void UniformDiscPositionAllocatorJson::SetY(double y){ m_y=y; }
void UniformDiscPositionAllocatorJson::SetRadius(double r){ m_radius=r; }
double UniformDiscPositionAllocatorJson::GetX() const{ return m_x; }
double UniformDiscPositionAllocatorJson::GetY() const{ return m_y; }
double UniformDiscPositionAllocatorJson::GetRadius() const{ return m_radius; }

// === MobilityJson ===

void MobilityJson::SetType(const std::string& type) { m_type = type; }
const std::string& MobilityJson::GetType() const { return m_type; }

void MobilityJson::SetMobilityModel(const std::shared_ptr<MobilityModelJson>& m){ m_mobilityModel=m; }
std::shared_ptr<MobilityModelJson> MobilityJson::GetMobilityModel() const{ return m_mobilityModel; }

void MobilityJson::SetPositionAllocator(const std::shared_ptr<PositionAllocatorJson>& a){ m_positionAllocator=a; }
std::shared_ptr<PositionAllocatorJson> MobilityJson::GetPositionAllocator() const{ return m_positionAllocator; }

} // namespace ns3
