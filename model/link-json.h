/**
 * @file link-json.h
 * @brief Definition of link configuration classes (JSON).
 */

#ifndef LINK_JSON_H
#define LINK_JSON_H
#include <memory>
#include <string>
#include <vector>

namespace ns3
{

struct NetDeviceIdJson
{
    uint32_t nodeId;
    uint32_t linkId;
};

/**
 * @brief Queue configuration for CSMA links.
 */
class CsmaQueueJson
{
  public:
    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetMode(const std::string& mode);
    const std::string& GetMode() const;

    void SetMaxPackets(uint32_t count);
    uint32_t GetMaxPackets() const;

  private:
    std::string m_type;
    std::string m_mode;
    uint32_t m_maxPackets = 0;
};

/**
 * @brief Queue configuration for P2P links.
 */
class P2pQueueJson
{
  public:
    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetMode(const std::string& mode);
    const std::string& GetMode() const;

    void SetMaxPackets(uint32_t count);
    uint32_t GetMaxPackets() const;

  private:
    std::string m_type;
    std::string m_mode;
    uint32_t m_maxPackets = 0;
};


/**
 * @brief Channel configuration for WiFi links.
 */
class WifiChannelJson
{
public:

    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetPropagationLoss(const std::string& loss);
    const std::string& GetPropagationLoss() const;

    void SetPropagationDelay(const std::string& delay);
    const std::string& GetPropagationDelay() const;

private:
    std::string m_type;
    std::string m_propagationLoss;
    std::string m_propagationDelay;
};


/**
 * @brief WiFi PHY layer configuration.
 */
class WifiPhyJson
{
  public:
    void SetTxPowerStart(double value);
    double GetTxPowerStart() const;

    void SetTxPowerEnd(double value);
    double GetTxPowerEnd() const;

    void SetRxSensitivity(double value);
    double GetRxSensitivity() const;

    void SetCcaEdThreshold(double value);
    double GetCcaEdThreshold() const;

  private:
    double m_txPowerStart = 0.0;
    double m_txPowerEnd = 0.0;
    double m_rxSensitivity = 0.0;
    double m_ccaEdThreshold = 0.0;
};

/**
 * @brief WiFi MAC layer configuration.
 */
class WifiMacJson
{
  public:
    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetSsid(const std::string& ssid);
    const std::string& GetSsid() const;

    void SetBeaconInterval(const std::string& interval);
    const std::string& GetBeaconInterval() const;

    void SetActiveProbing(bool enable);
    bool GetActiveProbing() const;

  private:
    std::string m_type;
    std::string m_ssid;
    std::string m_beaconInterval;
    bool m_activeProbing = false;
};

/**
 * @brief WiFi Manager configuration (Rate Control).
 */
class WifiManagerJson
{
  public:
    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetDataMode(const std::string& mode);
    const std::string& GetDataMode() const;

    void SetControlMode(const std::string& mode);
    const std::string& GetControlMode() const;

  private:
    std::string m_type;
    std::string m_dataMode;
    std::string m_controlMode;
};

class NetDeviceJson
{
  public:
    virtual ~NetDeviceJson() = default;
    void SetNetDeviceId(NetDeviceIdJson id);
    NetDeviceIdJson GetNetDeviceId() const;

    void SetType(const std::string& type);
    const std::string& GetType() const;

  private:
    NetDeviceIdJson m_netDeviceId;
    std::string m_type;
};

class P2pNetDeviceJson : public NetDeviceJson
{
};

class CsmaNetDeviceJson : public NetDeviceJson
{
};

class WifiNetDeviceJson : public NetDeviceJson
{
  public:
    void SetWifiPhy(const std::shared_ptr<WifiPhyJson>& phy);
    std::shared_ptr<WifiPhyJson> GetWifiPhy() const;

    void SetWifiMac(const std::shared_ptr<WifiMacJson>& mac);
    std::shared_ptr<WifiMacJson> GetWifiMac() const;

  private:
    std::shared_ptr<WifiPhyJson> m_wifiPhy;
    std::shared_ptr<WifiMacJson> m_wifiMac;
};

/**
 * @brief  class for all link types.
 */
class LinkJson
{
  public:
    virtual ~LinkJson() = default;
    void SetLinkId(uint32_t id);
    uint32_t GetLinkId() const;

    void SetType(const std::string& type);
    const std::string& GetType() const;

    void SetNetDevices(const std::vector<std::shared_ptr<NetDeviceJson>>& netDevices);
    const std::vector<std::shared_ptr<NetDeviceJson>>& GetNetDevices() const;

  private:
    uint32_t m_linkId = 0;
    std::string m_type;
    std::vector<std::shared_ptr<NetDeviceJson>> m_netDevices;
};

/**
 * @brief CSMA link definition.
 */
class CsmaLinkJson : public LinkJson
{
  public:
    void SetDataRate(const std::string& rate);
    const std::string& GetDataRate() const;

    void SetDelay(const std::string& delay);
    const std::string& GetDelay() const;

    void SetMtu(uint32_t mtu);
    uint32_t GetMtu() const;

    void SetInterframeGap(const std::string& gap);
    const std::string& GetInterframeGap() const;

    void SetQueue(const std::shared_ptr<CsmaQueueJson>& queue);
    std::shared_ptr<CsmaQueueJson> GetQueue() const;

  private:
    std::string m_dataRate;
    std::string m_delay;
    uint32_t m_mtu;
    std::string m_interframeGap;
    std::shared_ptr<CsmaQueueJson> m_queue;
};

/**
 * @brief P2P link definition.
 */
class P2pLinkJson : public LinkJson
{
  public:
    void SetDataRate(const std::string& rate);
    const std::string& GetDataRate() const;

    void SetDelay(const std::string& delay);
    const std::string& GetDelay() const;

    void SetMtu(uint32_t mtu);
    uint32_t GetMtu() const;

    void SetInterframeGap(const std::string& gap);
    const std::string& GetInterframeGap() const;

    void SetQueue(const std::shared_ptr<P2pQueueJson>& queue);
    std::shared_ptr<P2pQueueJson> GetQueue() const;

  private:
    std::string m_dataRate;
    std::string m_delay;
    uint32_t m_mtu;
    std::string m_interframeGap;
    std::shared_ptr<P2pQueueJson> m_queue;
};

/**
 * @brief WiFi link definition.
 */
class WifiLinkJson : public LinkJson
{
  public:
    void SetStandard(const std::string& standard);
    void SetChannelSettings(const std::string& channelSettings);
    void SetErrorRateModel(const std::string& errorRateModel);
    void SetQosSupported(bool qosSupported);

    const std::string& GetStandard() const;
    const std::string& GetChannelSettings() const;
    const std::string& GetErrorRateModel() const;
    bool GetQosSupported() const;

    void SetWifiManager(const std::shared_ptr<WifiManagerJson>& manager);
    std::shared_ptr<WifiManagerJson> GetWifiManager() const;

    void SetWifiChannel(const std::shared_ptr<WifiChannelJson>& channel);
    std::shared_ptr<WifiChannelJson> GetWifiChannel() const;

  private:
    std::string m_standard;
    std::string m_channelSettings;
    std::string m_errorRateModel;
    bool m_qosSupported;
    std::shared_ptr<WifiManagerJson> m_wifiManager;
    std::shared_ptr<WifiChannelJson> m_wifiChannel;
};

} // namespace ns3

#endif // LINK_JSON_H
