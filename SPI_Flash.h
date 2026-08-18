#pragma once
#include <vector>
#include <cstdint>

// 模拟 SPI Flash 芯片
class VirtualFlash {
public:
    VirtualFlash();  // 构造时初始化内存为 0xFF（空白状态）

    // 核心操作
    void Write(uint32_t addr, const std::vector<uint8_t>& data);
    std::vector<uint8_t> Read(uint32_t addr, size_t len);
    void Erase(uint32_t addr);
    void SetWriteProtect(bool enable);
    uint8_t GetStatus() const;

private:
    std::vector<uint8_t> memory;  // 模拟 4KB 存储空间
    bool writeProtected;          // 写保护标志
};