#ifndef DUMP_JSON_HELPER_H
#define DUMP_JSON_HELPER_H

#include <memory>
#include <iostream>
#include <vector>
#include <string>

#include "../model/config-json.h"
namespace ns3
{


/**
 * @brief Helper class to dump ConfigJson into a structured JSON string
 *
 * 该类负责以 JSON 格式打印整个仿真配置结构（ConfigJson），
 * 包括 nodes、links、IPv4/IPv6 网络、Internet Stack、WiFi 信道等。
 */
class DumpJsonHelper
{
  public:
    /**
     * @brief 构造函数
     * @param config 指向 ConfigJson 对象的共享指针
     */
    explicit DumpJsonHelper(std::shared_ptr<ConfigJson> config);

    /**
     * @brief 打印完整的 ConfigJson 内容
     */
    void PrintAll() const;

  private:
    std::shared_ptr<ConfigJson> m_config; //!< 配置对象

    // === 各子结构的导出函数 ===
    void DumpNodes(std::ostream& os, int level) const;
    void DumpLinks(std::ostream& os, int level) const;
    void DumpIpv4Networks(std::ostream& os, int level) const;
    void DumpIpv6Networks(std::ostream& os, int level) const;
    void DumpInternetStack(std::ostream& os, int level) const;
};

} // namespace ns3

#endif // JSON_DUMP_HELPER_H
