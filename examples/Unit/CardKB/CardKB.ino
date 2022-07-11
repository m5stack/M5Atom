/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: CardKB.  键盘
* Date: 2021/8/11
*******************************************************************************
  Please connect to Port,Read the characters entered by CardKB Unit and display
them on the Serial. 请连接端口,读取CardKB Unit输入的字符并显示在串口上。
*/

#include <M5Atom.h>
#define CARDKB_ADDR \
    0x5F  // Define the I2C address of CardKB.  定义CardKB的I2C地址

void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5Atom
    Serial.printf("IIC Address: 0x5F\n");
    Serial.printf(">>");
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚
}

void loop() {
    Wire.requestFrom(
        CARDKB_ADDR,
        1);  // Request 1 byte from the slave device.  向从设备请求1字节
    while (
        Wire.available())  // If received data is detected.  如果检测到收到数据
    {
        char c = Wire.read();  // Store the received data.  将接收到的数据存储
        if (c != 0) {
            Serial.printf("%c", c);
        }
    }
}
