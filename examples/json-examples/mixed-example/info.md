本仿真场景用于验证 **多类型网络设备（P2P、CSMA、WiFi、Adhoc)在统一拓扑下的互通性能**。
拓扑中包含csma、p2p、wifi等设备类型，测试不同应用之间的互操作性与路由连通性。
Topo情况见topo.png。

| 节点ID | 角色                | 备注                                                         |
| ------ | ------------------- | ------------------------------------------------------------ |
| n0     | Gateway             | 连接多种网络类型，作为n5的AP节点，同时也是一个adhoc节点      |
| n1     | Router              | 负责P2P链路中继                                              |
| n2     | Router              | 同时连接有P2P与CSMA信道                                      |
| n3     | Switch              | 二层存储转发                                                 |
| n4     | terminal            | 运行应用 UDP Echo Server，运行应用Onoff 向 n5 的 Packe Sink发送数据 |
| n5     | terminal（STA节点） | 与AP建立无线链路，运行应用 Packe Sink                        |
| n6     | Adhoc节点           | 与其他Adhoc节点通信，运行应用 UDP Echo Client 向 n4 的 UDP Echo Server通信 |

IP地址：未分配固定IP的设备在所在IP网络的地址池里顺序选用可用的IP地址

路由：要求n4和n5的通信采用静态路由n4---n2---n1---n0---n5，adhoc网络采用olsr路由协议，其余采用ns3的全局路由GlobalRouting

移动性：n0固定位置(0,10)；n5初始位置(0,0)，随机在100x100的矩形内以1的速度随机方向移动；n6初始位置(10,0)，移动模型同n6

注：n0、n5、n6在同一个无线物理信道环境，注意各链路种类决定了两端设备类型，仿真开始时各节点应用立即启用，持续至仿真结束
