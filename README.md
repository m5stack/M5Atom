# ATOM Library

English | [中文](README_cn.md)

<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_lite_01.webp" alt="M5Atom Lite" width="350" height="350">


<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_matrix_01.webp" alt="M5Atom Matrix" width="350" height="350">


## Description

<mark>**ATOM Matrix**</mark> and <mark>**ATOM Lite**</mark> are ESP32 development board with a size of only 24 * 24mm.It provides more GPIO for user customization which is very suitable for embedded smart home devices and in making smart toys. The main control adopts the ESP32-PICO chip which comes integrated with Wi-Fi and Bluetooth technologies and has a 4MB of integrated SPI flash memory. ATOM board provides an Infra-Red LED, RGB LED, buttons, and a PH2.0 interface. In addition, it can connect to external sensors and actuators through 6 GPIOs. The on-board Type-C USB interface enables rapid program upload and execution. ATOM Matrix have 5 * 5 RGB LED matrix, built-in IMU sensor (MPU6886). 

## PinMap

**ATOM Lite**

<img src="https://docs.m5stack.com/assets/img/product_pics/core/minicore/atom/atom_lite.jpg" alt="M5Atom Lite" height="350" style="margin-left:20px">

**ATOM Matrix**

<img src="https://docs.m5stack.com/assets/img/product_pics/core/minicore/atom/atom_matrix.jpg" alt="M5Atom Matrix" height="350" style="margin-left:20px">


<table>
 <tr><td>Neo</td><td>GPIO27</td></tr>
 <tr><td>Btn</td><td>GPIO39</td></tr>
 <tr><td>CLK(MPU6886)</td><td>GPIO21</td></tr>
 <tr><td>SDA(MPU6886)</td><td>GPIO25</td></tr>
 <tr><td>IR</td><td>GPIO12</td></tr>
 <tr><td>Btn</td><td>GPIO39</td></tr>
</table>

**GROVE interface**

<table>
 <tr><td>ESP32 chip</td><td>GPIO32</td><td>GPIO26</td><td>5V</td><td>GND</td></tr>
 <tr><td>PH2.0 interface</td><td>SCL</td><td>SDA</td><td>5V</td><td>GND</td></tr>
</table>

**Atom pixel tool**

<img src="https://github.com/m5stack/M5Atom/blob/master/tools/AtomPixelTool.jpg" alt="AtomPixelTool" height="100" style="margin-left:20px">

[Click here to download](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/software/AtomPixTool.exe)