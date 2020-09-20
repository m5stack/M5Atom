# ATOM Library

English | [中文](README_cn.md)

<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_lite_01.webp" alt="M5Atom Lite" width="350" height="350">


<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/image/m5-docs_homepage/core/atom_matrix_01.webp" alt="M5Atom Matrix" width="350" height="350">


## Description

<mark>**ATOM Matrix**</mark> and <mark>**ATOM Lite**</mark> are ESP32 development board with a size of only 24 * 24mm.It provides more GPIO for user customization which is very suitable for embedded smart home devices and in making smart toys. The main control adopts the ESP32-PICO chip which comes integrated with Wi-Fi and Bluetooth technologies and has a 4MB of integrated SPI flash memory. ATOM board provides an Infra-Red LED, RGB LED, buttons, and a PH2.0 interface. In addition, it can connect to external sensors and actuators through 6 GPIOs. The on-board Type-C USB interface enables rapid program upload and execution. ATOM Matrix have 5 * 5 RGB LED matrix, built-in IMU sensor (MPU6886). 

## PinMap

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

# Display API Document

## Public Types
<table>
<tr><td>enum</td><td><font color=#27b300>Am_mode</font>{kMoveRight,kMoveLeft,kMoveTop,kMoveButtom} </td></tr>
</table>

## Public Functions

<table>
<tr><td> void </td><td> <font color=#27b300>animation</font>(uint8_t *buffptr, uint8_t amspeed, uint8_t ammode, int64_t amcount = -1)</td></tr>
<tr><td> void </td><td> <font color=#27b300>displaybuff</font>(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0)</td></tr>
<tr><td> void </td><td> <font color=#27b300>MoveDisPlayBuff</font>(int8_t offsetx = 0, int8_t offsety = 0)</td></tr>
<tr><td> void </td><td> <font color=#27b300>setBrightness</font>(uint8_t brightness)</td></tr>
<tr><td> void </td><td> <font color=#27b300>drawpix</font>(uint8_t xpos, uint8_t ypos, CRGB Color)</td></tr>
<tr><td> void </td><td> <font color=#27b300>drawpix</font>(uint8_t Number, CRGB Color)</td></tr>
<tr><td> void </td><td> <font color=#27b300>fillpix</font>(CRGB Color)</td></tr>
<tr><td> void </td><td> <font color=#27b300>clear</font>()</td></tr>
</table>


## enum  Am_mode

<table>
<tr><td>Constant</td><td>Value</td><td>Description</td></tr>
<tr><td>LED_Display::kMoveRight</td><td>0x01</td><td>Move the image to the right</td></tr>
<tr><td>LED_Display::kMoveLeft</td><td>0x02</td><td>Move the image to the left</td></tr>
<tr><td>LED_Display::kMoveTop</td><td>0x04</td><td>Move the image to the top</td></tr>
<tr><td>LED_Display::kMoveButtom</td><td>0x08</td><td>Move the image to the buttom</td></tr>
</table>

## Member Function Documentation

---

        void animation(uint8_t *buffptr, uint8_t amspeed, uint8_t ammode, int64_t amcount = -1)

Start moving animation of an image

**parameter list**
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>buffptr</td><td>uint8_t*</td><td>-</td><td>-</td><td>Image pointer</td></tr>
<tr><td>amspeed</td><td>uint8_t</td><td>0 ~ MAXSIZE of uint8_t </td><td>-</td><td>Time interval of image movement</td></tr>
<tr><td>ammode</td><td>uint8_t</td><td>See also Am_mode</td><td>-</td><td>Animation mode of image movement</td></tr>
<tr><td>amcount</td><td>int64_t</td><td>-1 ~ MAXSIZE of int64_t</td><td>-1</td><td>The distance the image moves (pixels)</td></tr>
</table>

**return value**  
null

---

        void displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0)

Display an image 

**parameter list**
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>buffptr</td><td>uint8_t*</td><td>-</td><td>-</td><td>Image pointer</td></tr>
<tr><td>offsetx</td><td>uint8_t</td><td>-127 ~ 127 </td><td>0</td><td>Horizontal image offset</td></tr>
<tr><td>offsety</td><td>uint8_t</td><td>-127 ~ 127 </td><td>0</td><td>Vertical image offset</td></tr>
</table>

**return value**  
null

---

        void MoveDisPlayBuff(int8_t offsetx = 0, int8_t offsety = 0)

Move the image data in the display buff

**parameter list**
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>offsetx</td><td>int8_t</td><td>-127 ~ 127 </td><td>0</td><td>Horizontal image offset</td></tr>
<tr><td>offsety</td><td>int8_t</td><td>-127 ~ 127 </td><td>0</td><td>Vertical image offset</td></tr>
</table>

**return value**  
null

---

        void setBrightness(uint8_t brightness)

Set the Leds Brightness   
<font color=#ffbf00>Warning: It is not recommended to set the LED brightness to 100. Setting the LED brightness to 100 may cause overheating</font>

**parameter list**  
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>brightness</td><td>uint8_t</td><td> 0 ~ 100 </td><td>-</td><td>Brightness of Leds </td></tr>
</table>

**return value**  
null

---

        void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color)

Set the color of a LED in coordinate mode

**parameter list**
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>xpos</td><td>uint8_t</td><td>0 ~ 255 </td><td>0</td><td>coordinate x</td></tr>
<tr><td>ypos</td><td>uint8_t</td><td>0 ~ 255 </td><td>0</td><td>coordinate y</td></tr>
<tr><td>Color</td><td>CRGB</td><td>-</td><td>-</td><td>Color of Led </td></tr>
</table>

**return value**  
null

---

        void drawpix(uint8_t Number, CRGB Color)

Set the color of a LED

**parameter list**
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>Number</td><td>uint8_t</td><td>0 ~ 255 </td><td>0</td><td>number of Led</td></tr>
<tr><td>Color</td><td>CRGB</td><td>-</td><td>-</td><td>Color of Led </td></tr>
</table>

**return value**  
null

---

        void fillpix(CRGB Color)

Set the color of all LEDs

**parameter list**
<table>
<tr><td>name</td><td>type</td><td>range</td><td>default</td><td>description</td></tr>
<tr><td>Color</td><td>CRGB</td><td>-</td><td>-</td><td>Color of Leds </td></tr>
</table>

**return value**  
null

---

        void clear()

 Close all of LEDs

**parameter list**  
null

**return value**  
null
