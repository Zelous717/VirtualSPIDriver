#include "SPI_Flash.h"

VirtualFlash::VirtualFlash()
    : memory(FLASH_SIZE, 0xFF), writeProtected(false), busy(false)
{}

FlashRet VirtualFlash::Write(uint32_t addr, const std::vector<uint8_t>& data)
{
    if (writeProtected) {
        return FlashRet::WRITE_PROTECTED;
    }
    if (addr >= FLASH_SIZE) {
        return FlashRet::ADDR_OUT_RANGE;
    }

    busy = true;
    for (size_t i = 0; i < data.size(); ++i) {
        uint32_t pos = addr + static_cast<uint32_t>(i);
        if (pos >= FLASH_SIZE) {
            break;
        }
        memory[pos] &= data[i];
    }
    busy = false;
    return FlashRet::OK;
}

std::vector<uint8_t> VirtualFlash::Read(uint32_t addr, size_t len)
{
    std::vector<uint8_t> result;
    if (addr >= FLASH_SIZE) {
        return result;
    }
    for (size_t i = 0; i < len; ++i) {
        uint32_t pos = addr + static_cast<uint32_t>(i);
        if (pos >= FLASH_SIZE) {
            break;
        }
        result.push_back(memory[pos]);
    }
    return result;
}

FlashRet VirtualFlash::Erase(uint32_t addr)
{
    if (writeProtected) {
        return FlashRet::WRITE_PROTECTED;
    }
    if (addr >= FLASH_SIZE) {
        return FlashRet::ADDR_OUT_RANGE;
    }

    busy = true;
    uint32_t start = (addr / SECTOR_SIZE) * SECTOR_SIZE;
    for (size_t i = 0; i < SECTOR_SIZE; ++i) {
        uint32_t pos = start + static_cast<uint32_t>(i);
        if (pos >= FLASH_SIZE) {
            break;
        }
        memory[pos] = 0xFF;
    }
    busy = false;
    return FlashRet::OK;
}

void VirtualFlash::SetWriteProtect(bool enable)
{
    writeProtected = enable;
}

uint8_t VirtualFlash::GetStatus() const
{
    uint8_t status = 0x00;
    if (busy) {
        status |= (1U << 0); // WIP忙位
    }
    if (writeProtected) {
        status |= (1U << 1); // 写保护位
    }
    return status;
}