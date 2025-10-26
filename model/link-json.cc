/**
 * @file link-json.cc
 * @brief Implementation of link and channel configuration classes.
 */

#include "link-json.h"

namespace ns3
{

// ======== CsmaQueueJson ========
void CsmaQueueJson::SetType(const std::string& t) { m_type = t; }
const std::string& CsmaQueueJson::GetType() const { return m_type; }
void CsmaQueueJson::SetMode(const std::string& m) { m_mode = m; }
const std::string& CsmaQueueJson::GetMode() const { return m_mode; }
void CsmaQueueJson::SetMaxPackets(uint32_t c) { m_maxPackets = c; }
uint32_t CsmaQueueJson::GetMaxPackets() const { return m_maxPackets; }

// ======== P2pQueueJson ========
void P2pQueueJson::SetType(const std::string& t) { m_type = t; }
const std::string& P2pQueueJson::GetType() const { return m_type; }
void P2pQueueJson::SetMode(const std::string& m) { m_mode = m; }
const std::string& P2pQueueJson::GetMode() const { return m_mode; }
void P2pQueueJson::SetMaxPackets(uint32_t c) { m_maxPackets = c; }
uint32_t P2pQueueJson::GetMaxPackets() const { return m_maxPackets; }

// ======== WifiChannelJson ========

void WifiChannelJson::SetType(const std::string& t) { m_type = t; }
const std::string& WifiChannelJson::GetType() const { return m_type; }

void WifiChannelJson::SetPropagationLoss(const std::string& l) { m_propagationLoss = l; }
const std::string& WifiChannelJson::GetPropagationLoss() const { return m_propagationLoss; }

void WifiChannelJson::SetPropagationDelay(const std::string& d) { m_propagationDelay = d; }
const std::string& WifiChannelJson::GetPropagationDelay() const { return m_propagationDelay; }

// ========== WifiPhyJson ==========
void WifiPhyJson::SetTxPowerStart(double v) { m_txPowerStart = v; }
double WifiPhyJson::GetTxPowerStart() const { return m_txPowerStart; }
void WifiPhyJson::SetTxPowerEnd(double v) { m_txPowerEnd = v; }
double WifiPhyJson::GetTxPowerEnd() const { return m_txPowerEnd; }
void WifiPhyJson::SetRxSensitivity(double v) { m_rxSensitivity = v; }
double WifiPhyJson::GetRxSensitivity() const { return m_rxSensitivity; }
void WifiPhyJson::SetCcaEdThreshold(double v) { m_ccaEdThreshold = v; }
double WifiPhyJson::GetCcaEdThreshold() const { return m_ccaEdThreshold; }

// ========== WifiMacJson ==========
void WifiMacJson::SetType(const std::string& t) { m_type = t; }
const std::string& WifiMacJson::GetType() const { return m_type; }
void WifiMacJson::SetSsid(const std::string& s) { m_ssid = s; }
const std::string& WifiMacJson::GetSsid() const { return m_ssid; }
void WifiMacJson::SetBeaconInterval(const std::string& s) { m_beaconInterval = s; }
const std::string& WifiMacJson::GetBeaconInterval() const { return m_beaconInterval; }
void WifiMacJson::SetActiveProbing(bool e) { m_activeProbing = e; }
bool WifiMacJson::GetActiveProbing() const { return m_activeProbing; }

// ========== WifiManagerJson ==========
void WifiManagerJson::SetType(const std::string& t) { m_type = t; }
const std::string& WifiManagerJson::GetType() const { return m_type; }
void WifiManagerJson::SetDataMode(const std::string& m) { m_dataMode = m; }
const std::string& WifiManagerJson::GetDataMode() const { return m_dataMode; }
void WifiManagerJson::SetControlMode(const std::string& m) { m_controlMode = m; }
const std::string& WifiManagerJson::GetControlMode() const { return m_controlMode; }

// ========== NetDeviceJson ==========
void NetDeviceJson::SetType(const std::string& type) { m_type = type; }
const std::string& NetDeviceJson::GetType() const { return m_type; }
void NetDeviceJson::SetNetDeviceId(NetDeviceIdJson netDeviceId) { m_netDeviceId = netDeviceId; }
NetDeviceIdJson NetDeviceJson::GetNetDeviceId() const { return m_netDeviceId; }

// ========== WifiNetDeviceJson ==========
void WifiNetDeviceJson::SetWifiPhy(const std::shared_ptr<WifiPhyJson>& phy) { m_wifiPhy = phy; }
std::shared_ptr<WifiPhyJson> WifiNetDeviceJson::GetWifiPhy() const { return m_wifiPhy; }
void WifiNetDeviceJson::SetWifiMac(const std::shared_ptr<WifiMacJson>& mac) { m_wifiMac = mac; }
std::shared_ptr<WifiMacJson> WifiNetDeviceJson::GetWifiMac() const { return m_wifiMac; }


// ======== LinkJson ========
void LinkJson::SetLinkId(uint32_t id) { m_linkId = id; }
uint32_t LinkJson::GetLinkId() const { return m_linkId; }
void LinkJson::SetType(const std::string& type) { m_type = type; }
const std::string& LinkJson::GetType() const { return m_type; }
void LinkJson::SetNetDevices(const std::vector<std::shared_ptr<NetDeviceJson>>& netDevices) { m_netDevices = netDevices; }
const std::vector<std::shared_ptr<NetDeviceJson>>& LinkJson::GetNetDevices() const { return m_netDevices; }


// ======== CsmaLinkJson ========
void CsmaLinkJson::SetDataRate(const std::string& r) { m_dataRate = r; }
const std::string& CsmaLinkJson::GetDataRate() const { return m_dataRate; }
void CsmaLinkJson::SetDelay(const std::string& d) { m_delay = d; }
const std::string& CsmaLinkJson::GetDelay() const { return m_delay; }
void CsmaLinkJson::SetMtu(uint32_t m) { m_mtu = m; }
uint32_t CsmaLinkJson::GetMtu() const { return m_mtu; }
void CsmaLinkJson::SetInterframeGap(const std::string& g) { m_interframeGap = g; }
const std::string& CsmaLinkJson::GetInterframeGap() const { return m_interframeGap; }
void CsmaLinkJson::SetQueue(const std::shared_ptr<CsmaQueueJson>& q) { m_queue = q; }
std::shared_ptr<CsmaQueueJson> CsmaLinkJson::GetQueue() const { return m_queue; }

// ======== P2pLinkJson ========
void P2pLinkJson::SetDataRate(const std::string& r) { m_dataRate = r; }
const std::string& P2pLinkJson::GetDataRate() const { return m_dataRate; }
void P2pLinkJson::SetDelay(const std::string& d) { m_delay = d; }
const std::string& P2pLinkJson::GetDelay() const { return m_delay; }
void P2pLinkJson::SetMtu(uint32_t m) { m_mtu = m; }
uint32_t P2pLinkJson::GetMtu() const { return m_mtu; }
void P2pLinkJson::SetInterframeGap(const std::string& g) { m_interframeGap = g; }
const std::string& P2pLinkJson::GetInterframeGap() const { return m_interframeGap; }
void P2pLinkJson::SetQueue(const std::shared_ptr<P2pQueueJson>& q) { m_queue = q; }
std::shared_ptr<P2pQueueJson> P2pLinkJson::GetQueue() const { return m_queue; }

// ======== WifiLinkJson ========
void WifiLinkJson::SetStandard(const std::string& standard) { m_standard = standard; }
void WifiLinkJson::SetChannelSettings(const std::string& channelSettings) { m_channelSettings = channelSettings; }
void WifiLinkJson::SetErrorRateModel(const std::string& errorRateModel) { m_errorRateModel = errorRateModel; }
void WifiLinkJson::SetQosSupported(bool qosSupported) { m_qosSupported = qosSupported; }
const std::string& WifiLinkJson::GetStandard() const { return m_standard; }
const std::string& WifiLinkJson::GetChannelSettings() const { return m_channelSettings; }
const std::string& WifiLinkJson::GetErrorRateModel() const { return m_errorRateModel; }
bool WifiLinkJson::GetQosSupported() const { return m_qosSupported; }
void WifiLinkJson::SetWifiManager(const std::shared_ptr<WifiManagerJson>& channel) { m_wifiManager = channel; }
std::shared_ptr<WifiManagerJson> WifiLinkJson::GetWifiManager() const { return m_wifiManager; }
void WifiLinkJson::SetWifiChannel(const std::shared_ptr<WifiChannelJson>& channel) { m_wifiChannel = channel; }
std::shared_ptr<WifiChannelJson> WifiLinkJson::GetWifiChannel() const { return m_wifiChannel; }

} // namespace ns3
