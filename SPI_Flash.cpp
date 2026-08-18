#include "SPI_Flash.h"
#include <algorithm>

VirtualFlash::VirtualFlash() : memory(4096, 0xFF), writeProtected(false) {}

void VirtualFlash::Write(uint32_t addr, const std::vector<uint8_t>& data) {
    if (writeProtected) return;  // 写保护则忽略
    for (size_t i = 0; i < data.size() && (addr + i) < memory.size(); ++i) {
        memory[addr + i] = data[i];
    }
}

std::vector<uint8_t> VirtualFlash::Read(uint32_t addr, size_t len) {
    std::vector<uint8_t> result;
    for (size_t i = 0; i < len && (addr + i) < memory.size(); ++i) {
        result.push_back(memory[addr + i]);
    }
    return result;
}

void VirtualFlash::Erase(uint32_t addr) {
    if (writeProtected) return;
    // 模拟扇区擦除（256字节对齐）
    uint32_t start = (addr / 256) * 256;
    for (size_t i = 0; i < 256 && (start + i) < memory.size(); ++i) {
        memory[start + i] = 0xFF;
    }
}

void VirtualFlash::SetWriteProtect(bool enable) {
    writeProtected = enable;
}

uint8_t VirtualFlash::GetStatus() const {
    return writeProtected ? 0x01 : 0x00;  // 第0位表示写保护状态
}