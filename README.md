# config-json —— 基于 JSON 的 ns-3 仿真模块

`config-json` 是一个扩展自 [ns-3](https://www.nsnam.org/) 的模块，它允许你通过一组简单的 JSON 文件描述复杂的仿真场景。  
与其编写冗长的 基于C++ 的 ns-3 脚本来实例化节点、链路、协议栈、移动性和应用程序，不如使用声明式配置文件，由模块中的辅助类自动构建和运行仿真。

## 模块亮点

* **声明式配置**：在 JSON 中描述节点、链路、IP 网络、路由、移动性和应用，无需关心NS3仿真源码。
* **自动脚本生成**：`SimulatorJsonHelper` 自动构建 ns-3 拓扑、安装协议栈与应用，并运行仿真。
* **多种设备支持**：支持点对点（P2P）、CSMA 和 Wi-Fi 链路，可为每个设备配置 PHY/MAC 层参数；IPv4 与 IPv6 可同时启用。
* **灵活路由机制**：可选择全局路由或按节点定义的路由协议列表（Static / OLSR），并可通过优先级混合使用。
* **移动模型支持**：支持 ns-3 原生模型（常值位置、随机游走等）与外部 Gazebo 轨迹模型。
* **应用业务库**：内置 OnOff、PacketSink、UDP Echo（客户端/服务器）等，可绑定 IPv4/IPv6 或特定网络设备。
* **PCAP 捕获与监控**：支持链路级 PCAP 抓包。

## 目录结构

模块位于 ns-3 源码树的 `contrib` 目录中，结构如下：

| 路径        | 功能                                                         |
| ----------- | ------------------------------------------------------------ |
| `model/`    | 存放解析后数据的 C++ 模型类，如 `NodeJson`、`LinkJson`、`Ipv4NetworkJson`。这些类仅包含字段与访问器。 |
| `helper/`   | 各类辅助类，负责将 JSON 转换为模型对象并将其安装至 ns-3 仿真环境中。`SimulatorJsonHelper` 为核心入口。 |
| `examples/` | 包含示例程序（`config-json-example.cc`）及对应的 JSON 配置，如 `json-examples/adhoc-example/` 与 `json-examples/mixed-example/`。 |

模块依赖 [nlohmann/json](https://github.com/nlohmann/json) 与 Boost.Filesystem，在构建 ns-3 时会自动检测并链接。

## JSON 文件概览

顶层文件 `config.json` 引用多个子文件。每个文件负责仿真的一个独立部分，便于复用与修改。下表总结了支持的 JSON 文件：

| 文件                                                        | 功能                                                         |
| ----------------------------------------------------------- | ------------------------------------------------------------ |
| **config.json**                                             | 顶层元信息。包含 `simName`、可选 `info` 以及 `file` 对象，后者列出其他 JSON 文件路径。 |
| **nodes.json**                                              | 定义节点数组。每个节点包含 `nodeId` 与 `role`（如 `gateway`、`router`、`switch`、`terminal`、`adhoc`），角色会影响如交换机桥接等行为。 |
| **links.json**                                              | 定义每条链路（含 `linkId` 与 `type`），及其连接的网络设备。支持 `p2p`、`csma` 与 `wifi`。可配置带宽、延迟、MTU、队列等参数。Wi-Fi 还支持 PHY、MAC、信道、速率控制、误码模型与 QoS。 |
| **internet-stack.json**                                     | 配置 IPv4/IPv6 层及 TCP/UDP 参数，如 TTL、转发、校验、缓冲等。`enableGlobalRouting` 控制是否启用全局路由。 |
| **ipv4-network.json / ipv6-network.json**                   | 定义子网及 IP 地址分配，可设置掩码、基址与固定绑定。         |
| **ipv4-routing-protocol.json / ipv6-routing-protocol.json** | 定义每个节点的路由协议列表（Static / OLSR 等），支持优先级及各自参数（如静态路由表、HNA 网络等）。 |
| **mobility-*.json**                                         | 定义移动模型（ns3 / gazebo），包括 `positionAllocator` 与 `mobilityModel` 类型。 |
| **applications.json**                                       | 定义节点应用（OnOff、PacketSink、UdpEcho 等），配置端口、时间、速率、数据包大小等。 |

## 快速开始

### 1. 编译模块
在 ns-3 的 contrib/ 目录：

```bash
git clone https://github.com/Hax133/ns3-config-json-module/
```

在 ns-3 根目录执行：

```bash
./ns3 configure --enable-examples
./ns3 build
```

若缺少 `nlohmann_json`，可将单头文件放入 `third_party/nlohmann/json.hpp`。

### 2. 运行示例

在ns3根目录：

```bash
./ns3 run "config-json-example --config=contrib/config-json/examples/json-examples/adhoc-example/config.json --enable-simulator=true --enable-pcap=true"
```

参数说明：

- `--config`：指定配置文件路径  
- `--enable-dump`：打印模型数据  
- `--enable-simulator`：执行仿真  
- `--enable-pcap`：启用链路抓包  

执行后程序将：

1. 解析 JSON 配置；
2. 构建仿真拓扑；
3. 运行仿真；
4. 输出结果与 PCAP 文件。

### 3. 输出结果

仿真结束后：

- 自动打印路由表；
- 输出 `FlowMonitor` 统计；
- 生成 `.pcap` 抓包文件（可用 Wireshark 分析）。

## 数据流示意

```
config.json
 ├── nodes.json
 ├── links.json
 ├── internet-stack.json
 ├── ipv4-network.json
 ├── mobility.json
 └── applications.json
        ↓
ConfigJsonHelper → 解析配置
        ↓
ConfigJson → 参数暂存
        ↓
SimulatorJsonHelper → 构建与运行仿真
```

## 示例说明

### Adhoc 示例

- 4 个 adhoc 节点  
- 单一 Wi-Fi 链路（802.11a / 20MHz）  
- OLSR 路由  
- 固定位置  
- Node0 作为 EchoServer，其余节点为 EchoClient  

### Mixed 示例

- 组合 P2P、CSMA 与 Wi-Fi 链路  
- 路由器 + 交换机 + 终端 + Adhoc 节点混合拓扑  
- 静态与 OLSR 混合路由  
- 同时运行 OnOff、Echo、PacketSink 应用  

## 核心类

| 类名                  | 功能                               |
| --------------------- | ---------------------------------- |
| `ConfigJsonHelper`    | 模块主入口，负责解析全部配置文件。 |
| `DumpJsonHelper`      | 打印或导出模型数据。               |
| `SimulatorJsonHelper` | 控制仿真构建与运行（核心调度器）。 |

## 注意事项

- 启用 PCAP 捕获时请确保输出目录存在；
- 所有路径为相对路径；
- `nodeId` 与 `linkId` 必须唯一；
- 扩展新功能时，可在对应 Helper 中添加解析逻辑。

