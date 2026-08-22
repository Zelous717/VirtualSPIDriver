#include "SPI_Flash.h"
#include <iostream>

int main()
{
    VirtualFlash flash;
    std::vector<uint8_t> testData = {0xA5, 0x5A, 0xFF};

    // Test1 读写回环
    auto ret1 = flash.Write(0, testData);
    auto readBack = flash.Read(0, 3);
    bool pass1 = (ret1 == FlashRet::OK) && (readBack == testData);

    // Test2 扇区擦除
    auto ret2 = flash.Erase(0);
    auto erased = flash.Read(0, 1);
    bool pass2 = (ret2 == FlashRet::OK) && (erased[0] == 0xFF);

    // Test3 写保护拦截
    flash.SetWriteProtect(true);
    auto ret3 = flash.Write(0, {0x01});
    auto protectedRead = flash.Read(0, 1);
    bool pass3 = (ret3 == FlashRet::WRITE_PROTECTED) && (protectedRead[0] == 0xFF);
    flash.SetWriteProtect(false);

    // Test4 Flash硬件特性：写不能把0恢复成1
    flash.Write(0, {0x11});
    flash.Write(0, {0xFF});
    auto hwTest = flash.Read(0,1);
    bool pass4 = (hwTest[0] == 0x11);

    // Test5 越界地址
    auto ret5 = flash.Write(VirtualFlash::FLASH_SIZE, {0x00});
    bool pass5 = (ret5 == FlashRet::ADDR_OUT_RANGE);

    std::cout << "Test1 (写入读取): " << (pass1 ? "PASS ✅" : "FAIL ❌") << "\n";
    std::cout << "Test2 (扇区擦除): " << (pass2 ? "PASS ✅" : "FAIL ❌") << "\n";
    std::cout << "Test3 (写保护):   " << (pass3 ? "PASS ✅" : "FAIL ❌") << "\n";
    std::cout << "Test4 (Flash写硬件特性): "<< (pass4 ? "PASS ✅" : "FAIL ❌") << "\n";
    std::cout << "Test5 (地址越界): "<< (pass5 ? "PASS ✅" : "FAIL ❌") << "\n";

    return 0;
}