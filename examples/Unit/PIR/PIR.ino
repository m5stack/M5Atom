/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: PIR.  人体红外
* Date: 2021/8/11
*******************************************************************************
  Please connect to Port ,Human body detection using PIR Unit.
  请连接端口,使用PIR Unit进行人体检测。
*/

#include <M5Atom.h>

void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5Atom
    Serial.println("PIR example");
    pinMode(32, INPUT);  // Set pin 36 to input mode.  设置36号引脚为输入模式
}

void loop() {
    if (digitalRead(32) ==
        1) {  // If pin 32 reads a value of 1.  如果32号引脚的读取到的值为1
        Serial.println("Status: Sensing");
        Serial.println("Value: 1\n");
    } else {
        Serial.println("Status: Not Sensed");
        Serial.println("Value: 0\n");
    }
    delay(500);
}