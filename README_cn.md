# ATOM Library

[![Arduino Compile](https://github.com/m5stack/M5Atom/actions/workflows/arduino-action-atom-compile.yml/badge.svg)](https://github.com/m5stack/M5Atom/actions/workflows/arduino-action-paper-compile.yml)
[![Arduino Lint](https://github.com/m5stack/M5Atom/actions/workflows/Arduino-Lint-Check.yml/badge.svg)](https://github.com/m5stack/M5Atom/actions/workflows/Arduino-Lint-Check.yml)
[![Clang Format](https://github.com/m5stack/M5Atom/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/m5stack/M5Atom/actions/workflows/clang-format-check.yml)

中文 | [English](README_cn.md)

<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_lite_01.webp" alt="M5Atom Lite" width="350" height="350">


<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_matrix_01.webp" alt="M5Atom Matrix" width="350" height="350">

* **如果查看 ATOM Lite 的详细介绍文档，[点击这里](https://docs.m5stack.com/zh_CN/core/atom_lite)**

* **如果查看 ATOM Matrix 的详细介绍文档，[点击这里](https://docs.m5stack.com/zh_CN/core/atom_matrix)**

* **如果想要购买 ATOM Lite 的话，[点击这里](https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-22404213529.13.6b94492dPkGMA4&id=611064238273)**

* **如果想要购买 ATOM Matrix 的话，[点击这里](https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-22404213529.11.6b94492dPkGMA4&id=610821977232)**

## 描述

<mark>**ATOM Matrix**</mark> 与 <mark>**ATOM Lite**</mark> 是M5Stack开发套件系列中一款非常小巧的开发板,其大小`只有24 * 24mm`,提供更多GPIO供用户自定义,非常适合做嵌入式的智能硬件。主控采用`ESP32-PICO-D4`方案,集成`Wi-Fi`和`蓝牙`模块,拥有`4MB`的SPI闪存,ATOM系列开发板包含IR，RGB LED, 按键和PH2.0接口，提供6个GPIO引脚。相比 ATOM Lite，ATOM Matrix拥有5 * 5 RGB LED矩阵和MPU6886.

## 应用

- 物联网节点
- 微型控制器
- 可穿戴设备

## 驱动安装

将设备连接至PC，打开设备管理器为设备安装[FTDI驱动](https://ftdichip.com/drivers/vcp-drivers/)。以win10环境为例,下载匹配操作系统的驱动文件, 并解压,通过设备管理器进行安装。（注：某些系统环境下,需要安装两次,驱动才会生效,未识别的设备名通常为`M5Stack`或`USB Serial`, Windows推荐使用驱动文件在设备管理器直接进行安装(自定义更新), 可执行文件安装方式可能无法正常工作）。[点击此处，前往下载FTDI驱动](https://ftdichip.com/drivers/vcp-drivers/)

## 管脚映射

| 外设    | 引脚 |
| ------- | ---- |
| RGB Led | G27  |
| Btn     | G39  |
| IR      | G12  |
| SCL     | G21  |
| SDA     | G25  |

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/minicore/atom/atom_pin_map_01.webp" width="100%">


## 原理图

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/minicore/atom/ATOM_LITE_SIMPLE_CIRCUT_20200514.webp" width="100%">'

**Atom pixel tool**

[点此下载](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/software/AtomPixTool.exe)

## 更多信息

**UIFlow 快速上手**: [点击这里](https://docs.m5stack.com/zh_CN/quick_start/atom/uiflow)

**MicroPython API**: [点击这里](https://docs.m5stack.com/zh_CN/quick_start/atom/mpy)

**Arduino IDE 环境搭建**: [点击这里](https://docs.m5stack.com/zh_CN/quick_start/atom/arduino)

**Atom Arduino API**: [点击这里](https://docs.m5stack.com/zh_CN/api/atom/system)
