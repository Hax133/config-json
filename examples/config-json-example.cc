#include "ns3/config-json-module.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

int
main(int argc, char* argv[])
{
    CommandLine cmd;
    std::string configPath = "contrib/config-json/examples/json-examples/adhoc-example/config.json";
    bool enableDump = false;
    bool enableSimulator = true;
    bool enablePcap = true;
    cmd.AddValue("config", "Path to config.json", configPath);
    cmd.AddValue("enable-dump", "enable or not dump model built by json", enableDump);
    cmd.AddValue("enable-simulator", "enable or not run the simulation", enableSimulator);
    cmd.AddValue("enable-pcap", "enable or not packet caputure on some links", enablePcap);
    cmd.Parse(argc, argv);

    // 构建 ConfigJson
    ConfigJsonHelper configHelper;
    const auto& config = configHelper.Build(configPath);
    // 使用 JsonDumpHelper 打印完整结构
    if (enableDump)
    {
        DumpJsonHelper dumper(config);
        dumper.PrintAll();
    }
    // 构建仿真脚本
    if (enableSimulator)
    {
        SimulatorJsonHelper sim;
        sim.Install(config);
        // 配置channel抓包 文件前缀+关心的linkId容器
        // 文件前缀 若要添加子文件夹保存，一定要先创建文件夹，否则出现路径不可达断言
        // 例如pcap/test，要手动在ns3根目录先添加pcap文件夹
        if (enablePcap)
        {
            std::vector<uint32_t> linkIdsToTrace = {0};
            std::string prefix = "test";
            sim.EnablePcapAuto(prefix, linkIdsToTrace);
        }

        // 配置打印路由表事件
        Ipv4RoutingHelper::PrintRoutingTableAllAt(Seconds(20 - 0.1),
                                                  Create<OutputStreamWrapper>(&std::cout));

        // flow监控配置
        FlowMonitorHelper flow;
        Ptr<FlowMonitor> monitor = flow.InstallAll();

        Simulator::Stop(Seconds(20.0));
        Simulator::Run();
        Simulator::Destroy();
        // 打印业务流统计
        monitor->CheckForLostPackets();
        Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flow.GetClassifier());
        if (classifier)
        {
            FlowMonitor::FlowStatsContainer stats = monitor->GetFlowStats();
            std::cout << "检测到的流量数量: " << stats.size() << std::endl;

            for (auto i = stats.begin(); i != stats.end(); ++i)
            {
                Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow(i->first);
                std::cout << "Flow " << i->first << ": " << t.sourceAddress << ":" << t.sourcePort
                          << " -> " << t.destinationAddress << ":" << t.destinationPort
                          << " Tx: " << i->second.txPackets << " Rx: " << i->second.rxPackets
                          << std::endl;
            }
        }
    }

    return 0;
}
