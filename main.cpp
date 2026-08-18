#include "SPI_Flash.h"
#include <iostream>

int main() {
    VirtualFlash flash;
    std::vector<uint8_t> testData = {0xA5, 0x5A, 0xFF};

    // Test1: 写入并读回验证
    flash.Write(0, testData);
    auto readBack = flash.Read(0, 3);
    bool pass1 = (readBack == testData);

    // Test2: 擦除后验证
    flash.Erase(0);
    auto erased = flash.Read(0, 1);
    bool pass2 = (erased[0] == 0xFF);

    // Test3: 写保护后拒绝写入
    flash.SetWriteProtect(true);
    flash.Write(0, {0x01});
    auto protectedRead = flash.Read(0, 1);
    bool pass3 = (protectedRead[0] == 0xFF);

    std::cout << "Test1 (写入读取): " << (pass1 ? "PASS ✅" : "FAIL ❌") << std::endl;
    std::cout << "Test2 (扇区擦除): " << (pass2 ? "PASS ✅" : "FAIL ❌") << std::endl;
    std::cout << "Test3 (写保护):   " << (pass3 ? "PASS ✅" : "FAIL ❌") << std::endl;

    return 0;
}