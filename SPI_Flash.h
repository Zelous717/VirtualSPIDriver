#pragma once
#include <vector>
#include <cstdint>

enum class FlashRet {
    OK,
    WRITE_PROTECTED,
    ADDR_OUT_RANGE
};

class VirtualFlash {
public:
    static constexpr uint32_t FLASH_SIZE = 4096U;
    static constexpr uint32_t SECTOR_SIZE = 256U;

    VirtualFlash();

    FlashRet Write(uint32_t addr, const std::vector<uint8_t>& data);
    std::vector<uint8_t> Read(uint32_t addr, size_t len);
    FlashRet Erase(uint32_t addr);

    void SetWriteProtect(bool enable);
    uint8_t GetStatus() const;

private:
    std::vector<uint8_t> memory;
    bool writeProtected;
    bool busy;
};