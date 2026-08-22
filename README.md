# VirtualSPIDriver - 基于C++的虚拟SPI Flash驱动

## 项目简介

使用 C++11 模拟 SPI Flash 芯片的核心驱动逻辑，涵盖读写、擦除、写保护等功能。不依赖硬件，通过软件模拟验证嵌入式驱动开发流程。

## 核心功能

- 按地址写入数据
- 按地址读取数据
- 扇区擦除（256字节对齐）
- 写保护机制
- 状态查询

## 项目结构
VirtualSPIDriver/
├── SPI_Flash.h          # 类声明
├── SPI_Flash.cpp        # 类实现
├── main.cpp             # 测试入口
├── README.md            # 项目说明
└── .gitignore           # Git忽略