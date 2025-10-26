#include "application-json-helper.h"

#include <fstream>
#include <iostream>

namespace ns3
{

using json = nlohmann::json;

/**
 * @brief Build a nested SocketJson object.
 */
std::shared_ptr<SocketJson>
ApplicationJsonHelper::BuildSocket(const json& j)
{
    auto socket = std::make_shared<SocketJson>();
    socket->SetType(j.value("type", ""));
    socket->SetPort(j.value("port", 0));
    socket->SetAddressId(j.value("addressId", 0));
    bool any = true;
    if (j.contains("netDeviceId"))
    {
        any = false;
        auto d = j.value("netDeviceId", json::object());
        socket->SetNetDeviceId(
            NetDeviceIdJson{d.value<uint32_t>("nodeId", 0), d.value<uint32_t>("linkId", 0)});
    }
    socket->SetAny(any);
    return socket;
}

/**
 * @brief Build OnOffJson.
 */
std::shared_ptr<OnOffJson>
ApplicationJsonHelper::BuildOnOff(const json& entry)
{
    auto app = std::make_shared<OnOffJson>();
    app->SetApplicationId(entry.value<uint32_t>("applicationId", 0));
    app->SetType(entry.value("type", ""));
    app->SetSocket(BuildSocket(entry.value("socket", json::object())));
    app->SetStartTime(entry.value("startTime", ""));
    app->SetStopTime(entry.value("stopTime", ""));
    app->SetPacketSize(entry.value("packetSize", 0));
    app->SetProtocol(entry.value("protocol", ""));
    app->SetDataRate(entry.value("dataRate", ""));

    return app;
}

/**
 * @brief Build UDP Echo Server.
 */
std::shared_ptr<UdpEchoServerJson>
ApplicationJsonHelper::BuildUdpEchoServer(const json& entry)
{
    auto app = std::make_shared<UdpEchoServerJson>();
    app->SetApplicationId(entry.value<uint32_t>("applicationId", 0));
    app->SetType(entry.value("type", ""));
    app->SetSocket(BuildSocket(entry.value("socket", json::object())));
    app->SetStartTime(entry.value("startTime", ""));
    app->SetStopTime(entry.value("stopTime", ""));
    return app;
}

/**
 * @brief Build UDP Echo Client.
 */
std::shared_ptr<UdpEchoClientJson>
ApplicationJsonHelper::BuildUdpEchoClient(const json& entry)
{
    auto app = std::make_shared<UdpEchoClientJson>();
    app->SetApplicationId(entry.value<uint32_t>("applicationId", 0));
    app->SetType(entry.value("type", ""));
    app->SetSocket(BuildSocket(entry.value("socket", json::object())));
    app->SetStartTime(entry.value("startTime", ""));
    app->SetStopTime(entry.value("stopTime", ""));
    app->SetPacketSize(entry.value("packetSize", 0));
    app->SetMaxPackets(entry.value("maxPackets", 0));
    app->SetInterval(entry.value("interval", ""));
    return app;
}

/**
 * @brief Build PacketSinkJson.
 */
std::shared_ptr<PacketSinkJson>
ApplicationJsonHelper::BuildPacketSink(const json& entry)
{
    auto app = std::make_shared<PacketSinkJson>();
    app->SetApplicationId(entry.value<uint32_t>("applicationId", 0));
    app->SetType(entry.value("type", ""));
    app->SetSocket(BuildSocket(entry.value("socket", json::object())));
    app->SetStartTime(entry.value("startTime", ""));
    app->SetStopTime(entry.value("stopTime", ""));
    app->SetProtocol(entry.value("protocol", ""));
    return app;
}

/**
 * @brief Build a single application by nodeId and appId.
 */
std::shared_ptr<ApplicationJson>
ApplicationJsonHelper::Build(const json& data)
{
    std::string type = data.value("type", "");
    if (type == "onOff")
        return BuildOnOff(data);
    else if (type == "udpEchoServer")
        return BuildUdpEchoServer(data);
    else if (type == "udpEchoClient")
        return BuildUdpEchoClient(data);
    else if (type == "packetSink")
        return BuildPacketSink(data);
    return nullptr;
}

} // namespace ns3
