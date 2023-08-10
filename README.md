# ATOM Library

[![Arduino Compile](https://github.com/m5stack/M5Atom/actions/workflows/arduino-action-atom-compile.yml/badge.svg)](https://github.com/m5stack/M5Atom/actions/workflows/arduino-action-paper-compile.yml)
[![Arduino Lint](https://github.com/m5stack/M5Atom/actions/workflows/Arduino-Lint-Check.yml/badge.svg)](https://github.com/m5stack/M5Atom/actions/workflows/Arduino-Lint-Check.yml)
[![Clang Format](https://github.com/m5stack/M5Atom/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/m5stack/M5Atom/actions/workflows/clang-format-check.yml)

English | [中文](README_cn.md)

<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_lite_01.webp" alt="M5Atom Lite" width="350" height="350">


<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_matrix_01.webp" alt="M5Atom Matrix" width="350" height="350">

* **For the Detailed documentation of ATOM Lite, please [Click here](https://docs.m5stack.com/en/core/atom_lite)**

* **For the Detailed documentation of ATOM Matrix, please [Click here](https://docs.m5stack.com/en/core/atom_matrix)**

* **In order to buy ATOM Lite, please [Click here](https://shop.m5stack.com/collections/m5-controllers/products/atom-lite-esp32-development-kit)**

* **In order to buy ATOM Matrix, please [Click here](https://shop.m5stack.com/collections/m5-controllers/products/atom-matrix-esp32-development-kit)**

## Description

<mark>**ATOM Matrix**</mark> and <mark>**ATOM Lite**</mark> are ESP32 development board with a size of only 24 * 24mm.It provides more GPIO for user customization which is very suitable for embedded smart home devices and in making smart toys. The main control adopts the ESP32-PICO chip which comes integrated with Wi-Fi and Bluetooth technologies and has a 4MB of integrated SPI flash memory. ATOM board provides an Infra-Red LED, RGB LED, buttons, and a PH2.0 interface. In addition, it can connect to external sensors and actuators through 6 GPIOs. The on-board Type-C USB interface enables rapid program upload and execution. ATOM Matrix have 5 * 5 RGB LED matrix, built-in IMU sensor (MPU6886). 

## Applications

- Internet of things terminal controller
- IoT node
- Wearable peripherals

## Driver Installation

Connect the device to the PC, open the device manager to install [FTDI driver](https://ftdichip.com/drivers/vcp-drivers/) for the device. Take the win10 environment as an example, download the driver file that matches the operating system, unzip it, and install it through the device manager. (Note: In some system environments, the driver needs to be installed twice for the driver to take effect. The unrecognized device name is usually `M5Stack` or `USB Serial`. Windows recommends using the driver file to install directly in the device manager (custom Update), the executable file installation method may not work properly). [Click here to download FTDI driver](https://ftdichip.com/drivers/vcp-drivers/)

## Peripherals Pin Map

| Peripherals | Pin |
| ----------- | --- |
| RGB Led     | G27 |
| Btn         | G39 |
| IR          | G12 |
| SCL         | G21 |
| SDA         | G25 |

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/minicore/atom/atom_pin_map_01.webp" width="100%">

## Schematic

<img src="https://static-cdn.m5stack.com/resource/docs/static/assets/img/product_pics/core/minicore/atom/ATOM_LITE_SIMPLE_CIRCUT_20200514.webp" width="100%">

**Atom pixel tool**

[Click here to download](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/software/AtomPixTool.exe)

## More Information

**UIFlow Quick Start**: [Click Here](https://docs.m5stack.com/en/quick_start/atom/uiflow)

**MicroPython API**: [Click Here](https://docs.m5stack.com/en/quick_start/atom/mpy)

**Arduino IDE Development**: [Click Here](https://docs.m5stack.com/en/quick_start/atom/arduino)

**Atom Arduino API**: [Click Here](https://docs.m5stack.com/en/api/atom/system)
