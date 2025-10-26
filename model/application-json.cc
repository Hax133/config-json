/**
 * @file application-json.cc
 * @brief Implementation of application configuration classes.
 */

#include "application-json.h"
namespace ns3 {

// ======== SocketJson ========
void SocketJson::SetType(const std::string& type) { m_type = type; }
const std::string& SocketJson::GetType() const { return m_type; }

void SocketJson::SetNetDeviceId(NetDeviceIdJson netDeviceId) { m_netDeviceId = netDeviceId; }
NetDeviceIdJson SocketJson::GetNetDeviceId() const { return m_netDeviceId; }

void SocketJson::SetAddressId(uint32_t id) { m_addressId = id; }
uint32_t SocketJson::GetAddressId() const { return m_addressId; }

void SocketJson::SetPort(uint32_t port) { m_port = port; }
uint32_t SocketJson::GetPort() const { return m_port; }

void SocketJson::SetAny(bool any) { m_any = any; }
bool SocketJson::IsAny() const { return (m_any); }

// ======== ApplicationJson ========
void ApplicationJson::SetApplicationId(uint32_t id) { m_applicationId = id; }
uint32_t ApplicationJson::GetApplicationId() const { return m_applicationId; }

void ApplicationJson::SetType(const std::string& type) { m_type = type; }
const std::string& ApplicationJson::GetType() const { return m_type; }

void ApplicationJson::SetSocket(const std::shared_ptr<SocketJson>& socket) {m_socket = socket; }
std::shared_ptr<SocketJson> ApplicationJson::GetSocket() const { return m_socket; }

void ApplicationJson::SetStartTime(const std::string& t) { m_startTime = t; }
const std::string& ApplicationJson::GetStartTime() const { return m_startTime; }

void ApplicationJson::SetStopTime(const std::string& t) { m_stopTime = t; }
const std::string& ApplicationJson::GetStopTime() const { return m_stopTime; }

// ======== OnOffJson ========
void OnOffJson::SetProtocol(const std::string& p) {m_protocol = p; }
const std::string& OnOffJson::GetProtocol() const { return m_protocol; }

void OnOffJson::SetPacketSize(uint32_t s) { m_packetSize = s; }
uint32_t OnOffJson::GetPacketSize() const { return m_packetSize; }

void OnOffJson::SetDataRate(const std::string& r) { m_dataRate = r; }
const std::string& OnOffJson::GetDataRate() const { return m_dataRate; }

// ======== UdpEchoClientJson ========
void UdpEchoClientJson::SetInterval(const std::string& i) { m_interval = i; }
const std::string& UdpEchoClientJson::GetInterval() const { return m_interval; }

void UdpEchoClientJson::SetPacketSize(uint32_t s) { m_packetSize = s; }
uint32_t UdpEchoClientJson::GetPacketSize() const { return m_packetSize; }

void UdpEchoClientJson::SetMaxPackets(uint32_t c) { m_maxPackets = c; }
uint32_t UdpEchoClientJson::GetMaxPackets() const { return m_maxPackets; }

// ======== PacketSinkJson ========
void PacketSinkJson::SetProtocol(const std::string& p) { m_protocol = p; }
const std::string& PacketSinkJson::GetProtocol() const { return m_protocol; }

} // namespace ns3
