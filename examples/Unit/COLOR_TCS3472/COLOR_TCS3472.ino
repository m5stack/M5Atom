/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: COLOR_TCS3472.  颜色识别
* Date: 2021/8/11
*******************************************************************************
  Please connect to Port ,Use COLOR Unit to read C, R, G, B values
  请连接端口,使用COLOR Unit读取C, R, G, B值
*/

#include <M5Atom.h>
#include "Adafruit_TCS34725.h"

#define commonAnode \
    true  // set to false if using a common cathode LED.
          // //如果使用普通阴极LED，则设置为false

byte gammatable[256];  // our RGB -> eye-recognized gamma color

static uint16_t color16(uint16_t r, uint16_t g, uint16_t b) {
    uint16_t _color;
    _color = (uint16_t)(r & 0xF8) << 8;
    _color |= (uint16_t)(g & 0xFC) << 3;
    _color |= (uint16_t)(b & 0xF8) >> 3;
    return _color;
}

Adafruit_TCS34725 tcs =
    Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
    M5.begin();          // Init M5Atom.  初始化 M5Atom
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚
    Serial.println("Color View Test!");
    while (!tcs.begin()) {  //如果color unit未能初始化
        Serial.println("No TCS34725 found ... check your connections");
        delay(1000);
    }
    tcs.setIntegrationTime(
        TCS34725_INTEGRATIONTIME_154MS);  // Sets the integration time for the
                                          // TC34725.  设置TC34725的集成时间
    tcs.setGain(TCS34725_GAIN_4X);  // Adjusts the gain on the TCS34725.
                                    // 调整TCS34725上的增益
}

void loop() {
    uint16_t clear, red, green, blue;
    tcs.getRawData(&red, &green, &blue,
                   &clear);  // Reads the raw red, green, blue and clear channel
                             // values.  读取原始的红、绿、蓝和清晰的通道值

    // Figure out some basic hex code for visualization.  生成对应的十六进制代码
    uint32_t sum = clear;
    float r, g, b;
    r = red;
    r /= sum;
    g = green;
    g /= sum;
    b = blue;
    b /= sum;
    r *= 256;
    g *= 256;
    b *= 256;
    uint16_t _color = color16((int)r, (int)g, (int)b);

    Serial.print("C:");
    Serial.println(clear);
    Serial.print("R:");
    Serial.println(red);
    Serial.print("G:");
    Serial.println(green);
    Serial.print("B:");
    Serial.println(blue);
    Serial.print("0x");
    Serial.print((int)r, HEX);
    Serial.print((int)g, HEX);
    Serial.println((int)b, HEX);
    Serial.println("");
    delay(1000);
}
