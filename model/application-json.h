/**
 * @file application-json.h
 * @brief Definition of application configuration classes (JSON).
 */

#ifndef APPLICATION_JSON_H
#define APPLICATION_JSON_H

#include <string>
#include <memory>
#include <vector>

#include "link-json.h"

namespace ns3 {


/**
 * @brief Socket configuration structure.
 */
class SocketJson
{
public:
    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetNetDeviceId(NetDeviceIdJson id);
    NetDeviceIdJson GetNetDeviceId() const;


    void SetAddressId(uint32_t id);
    uint32_t GetAddressId() const;

    void SetPort(uint32_t port);
    uint32_t GetPort() const;

    void SetAny(bool any);
    bool IsAny() const;
private:
    std::string m_type;
    NetDeviceIdJson m_netDeviceId;
    uint32_t m_addressId = 0;
    uint32_t m_port = 0;
    bool m_any = false;
};

/**
 * @brief  class for all application configurations.
 */
class ApplicationJson
{
public:
    virtual ~ApplicationJson() = default;
    void SetApplicationId(uint32_t id);
    uint32_t GetApplicationId() const;

    void SetSocket(const std::shared_ptr<SocketJson>& socket);
    std::shared_ptr<SocketJson> GetSocket() const;

    void SetStartTime(const std::string& time);
    const std::string& GetStartTime() const;

    void SetStopTime(const std::string& time);
    const std::string& GetStopTime() const;
    
    void SetType(const std::string& type);
    const std::string& GetType() const;

private:
    uint32_t m_applicationId = 0;
    std::string m_type;
    std::shared_ptr<SocketJson> m_socket;
    std::string m_startTime;
    std::string m_stopTime;
};

/**
 * @brief OnOff application configuration.
 */
class OnOffJson : public ApplicationJson
{
public:
    void SetProtocol(const std::string& proto);
    const std::string& GetProtocol() const;

    void SetPacketSize(uint32_t size);
    uint32_t GetPacketSize() const;

    void SetDataRate(const std::string& rate);
    const std::string& GetDataRate() const;

private:
    std::string m_protocol;
    uint32_t m_packetSize = 0;
    std::string m_dataRate;
};

/**
 * @brief UDP Echo Server configuration.
 */
class UdpEchoServerJson : public ApplicationJson
{
    // No additional fields
};

/**
 * @brief UDP Echo Client configuration.
 */
class UdpEchoClientJson : public ApplicationJson
{
public:
    void SetInterval(const std::string& interval);
    const std::string& GetInterval() const;

    void SetPacketSize(uint32_t size);
    uint32_t GetPacketSize() const;

    void SetMaxPackets(uint32_t count);
    uint32_t GetMaxPackets() const;

private:
    std::string m_interval;
    uint32_t m_packetSize = 0;
    uint32_t m_maxPackets = 0;
};

/**
 * @brief PacketSink application configuration.
 */
class PacketSinkJson : public ApplicationJson
{
public:
    void SetProtocol(const std::string& proto);
    const std::string& GetProtocol() const;

private:
    std::string m_protocol;
};

} // namespace ns3

#endif // APPLICATION_JSON_H
