/**
 * @file internet-stack-json.h
 * @brief Definition of NodeJson class and its related components.
 */

#ifndef INTERNET_STACK_JSON_H
#define INTERNET_STACK_JSON_H

#include <memory>
#include <string>
#include <vector>
#include "ipv4-routing-protocol-json.h"
#include "ipv6-routing-protocol-json.h"
namespace ns3
{
class Ipv4L3ProtocolJson
{
  public:
    void SetDefaultTtl(uint32_t ttl);
    uint32_t GetDefaultTtl() const;

    void SetIpForward(bool enable);
    bool GetIpForward() const;

    void SetWeakEsModel(bool enable);
    bool GetWeakEsModel() const;

    void SetSendIcmpRedirect(bool enable);
    bool GetSendIcmpRedirect() const;

    void SetEnableMtuDiscovery(bool enable);
    bool GetEnableMtuDiscovery() const;

    void SetFragmentExpirationTimeout(const std::string& timeout);
    const std::string& GetFragmentExpirationTimeout() const;

    void SetMtuDiscoverTimeout(const std::string& timeout);
    const std::string& GetMtuDiscoverTimeout() const;

    void SetRouteCacheTimeout(const std::string& timeout);
    const std::string& GetRouteCacheTimeout() const;

    void SetEnableChecksum(bool enable);
    bool GetEnableChecksum() const;

  private:
    uint32_t m_defaultTtl = 64;
    bool m_ipForward = false;
    bool m_weakEsModel = false;
    bool m_sendIcmpRedirect = false;
    bool m_enableMtuDiscovery = false;
    std::string m_fragmentExpirationTimeout;
    std::string m_mtuDiscoverTimeout;
    std::string m_routeCacheTimeout;
    bool m_enableChecksum = false;
};

/**
 * @brief IPv6 L3 protocol configuration (top-level).
 */
class Ipv6L3ProtocolJson
{
  public:
    void SetDefaultTtl(uint32_t ttl);
    uint32_t GetDefaultTtl() const;

    void SetIpForward(bool enable);
    bool GetIpForward() const;

    void SetSendIcmpRedirect(bool enable);
    bool GetSendIcmpRedirect() const;

    void SetEnableMtuDiscovery(bool enable);
    bool GetEnableMtuDiscovery() const;

    void SetFragmentExpirationTimeout(const std::string& timeout);
    const std::string& GetFragmentExpirationTimeout() const;

    void SetMtuDiscoverTimeout(const std::string& timeout);
    const std::string& GetMtuDiscoverTimeout() const;

    void SetRouteCacheTimeout(const std::string& timeout);
    const std::string& GetRouteCacheTimeout() const;

    void SetEnableChecksum(bool enable);
    bool GetEnableChecksum() const;

  private:
    uint32_t m_defaultTtl = 64;
    bool m_ipForward = false;
    bool m_sendIcmpRedirect = false;
    bool m_enableMtuDiscovery = false;
    std::string m_fragmentExpirationTimeout;
    std::string m_mtuDiscoverTimeout;
    std::string m_routeCacheTimeout;
    bool m_enableChecksum = false;
};

/**
 * @class UdpL4ProtocolJson
 * @brief Describes the configuration of a UDP transport protocol.
 */
class UdpL4ProtocolJson
{
  public:
    // === Getters ===
    uint32_t GetSendBufferSize() const;
    uint32_t GetReceiveBufferSize() const;
    uint32_t GetPacketSize() const;
    const std::string& GetDataRate() const;
    bool GetEnableChecksum() const;
    bool GetEnableBroadcast() const;
    bool GetEnableMulticast() const;

    // === Setters ===
    void SetSendBufferSize(uint32_t size);
    void SetReceiveBufferSize(uint32_t size);
    void SetPacketSize(uint32_t size);
    void SetDataRate(const std::string& rate);
    void SetEnableChecksum(bool enable);
    void SetEnableBroadcast(bool enable);
    void SetEnableMulticast(bool enable);

  private:
    uint32_t m_sendBufferSize;
    uint32_t m_receiveBufferSize;
    uint32_t m_packetSize;
    std::string m_dataRate;
    bool m_enableChecksum;
    bool m_enableBroadcast;
    bool m_enableMulticast;
};

/**
 * @class TcpL4ProtocolJson
 * @brief Describes the configuration of a TCP transport protocol.
 */
class TcpL4ProtocolJson
{
  public:
    // === Getters ===
    uint32_t GetSendBufferSize() const;
    uint32_t GetReceiveBufferSize() const;
    const std::string& GetVariant() const;
    uint32_t GetInitialCwnd() const;
    uint32_t GetSegmentSize() const;
    uint32_t GetMaxCwnd() const;
    uint32_t GetSlowStartThreshold() const;
    uint32_t GetRetransmitTimeout() const;
    bool GetEnableSack() const;
    bool GetEnableDelayedAck() const;
    bool GetEnableNagle() const;
    bool GetEnableKeepAlive() const;

    // === Setters ===
    void SetSendBufferSize(uint32_t size);
    void SetReceiveBufferSize(uint32_t size);
    void SetVariant(const std::string& variant);
    void SetInitialCwnd(uint32_t cwnd);
    void SetSegmentSize(uint32_t size);
    void SetMaxCwnd(uint32_t cwnd);
    void SetSlowStartThreshold(uint32_t threshold);
    void SetRetransmitTimeout(uint32_t timeout);
    void SetEnableSack(bool enable);
    void SetEnableDelayedAck(bool enable);
    void SetEnableNagle(bool enable);
    void SetEnableKeepAlive(bool enable);

  private:
    uint32_t m_sendBufferSize;
    uint32_t m_receiveBufferSize;
    std::string m_variant;
    uint32_t m_initialCwnd;
    uint32_t m_segmentSize;
    uint32_t m_maxCwnd;
    uint32_t m_slowStartThreshold;
    uint32_t m_retransmitTimeout;
    bool m_enableSack;
    bool m_enableDelayedAck;
    bool m_enableNagle;
    bool m_enableKeepAlive;
};

class InternetStackJson
{
  public:
    void SetIpv4(const std::shared_ptr<Ipv4L3ProtocolJson>& ipv4);
    void SetIpv6(const std::shared_ptr<Ipv6L3ProtocolJson>& ipv6);
    void SetUdp(const std::shared_ptr<UdpL4ProtocolJson>& udp);
    void SetTcp(const std::shared_ptr<TcpL4ProtocolJson>& tcp);

    std::shared_ptr<Ipv4L3ProtocolJson> GetIpv4() const;
    std::shared_ptr<Ipv6L3ProtocolJson> GetIpv6() const;
    std::shared_ptr<UdpL4ProtocolJson> GetUdp() const;
    std::shared_ptr<TcpL4ProtocolJson> GetTcp() const;

    void SetEnableGlobalRouting(bool enable);
    bool IsEnableGlobalRouting();

  private:
    std::shared_ptr<Ipv4L3ProtocolJson> m_ipv4;
    std::shared_ptr<Ipv6L3ProtocolJson> m_ipv6;
    std::shared_ptr<UdpL4ProtocolJson> m_udp;
    std::shared_ptr<TcpL4ProtocolJson> m_tcp;
    bool m_enableGlobalRouting = false;
};

} // namespace ns3

#endif