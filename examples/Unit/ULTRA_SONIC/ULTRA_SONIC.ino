/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  Ultrasonic.  超声波测距传感器
* Date: 2021/8/19
*******************************************************************************
  Please connect to Port,Display the distance measured by ultrasonic
  请连接端口,显示超声波测量的距离
*/

#include <M5Atom.h>

void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    Wire.begin(26, 32);
    Serial.print("Ultrasonic");
}

float readEUS() {
    uint32_t data;
    Wire.beginTransmission(0x57);  // Transfer data to 0x57.  将数据传输到0x57
    Wire.write(0x01);
    Wire.endTransmission();  // Stop data transmission with the Ultrasonic Unit.
                             // 停止与Ultrasonic Unit的数据传输
    delay(120);
    Wire.requestFrom(0x57, 3);  // Request 3 bytes from Ultrasonic Unit.
                                // 向Ultrasonic Unit请求3个字节。
    data = Wire.read();
    data <<= 8;
    data |= Wire.read();
    data <<= 8;
    data |= Wire.read();
    return float(data) / 1000;
}

void loop() {
    static float newvalue = 0;
    newvalue              = readEUS();
    if ((newvalue < 1500) && (newvalue > 20)) {
        Serial.printf("Distance:%.2fmm\n", newvalue);
    }
    delay(100);
}