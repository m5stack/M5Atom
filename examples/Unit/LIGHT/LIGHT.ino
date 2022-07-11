/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  Light.  环境光传感器
* Date: 2021/8/18
*******************************************************************************
  Please connect to Port,Use the Light Unit Serial to display the current
ambient lighting value 请连接端口 ,使用Light Unit 串口显示当前环境光照值。
*/

#include <M5Atom.h>

void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    Serial.printf("\n\nUNIT_LIGHT EXAMPLE");
    pinMode(26, INPUT);  // Set pin 26 as input mode.  设置引脚26为输入模式
}

void loop() {
    static uint16_t digitalRead_value = 0, analogRead_value = 0;
    analogRead_value = analogRead(32);  // Store the analog quantity read from
                                        // pin 32.  将32号引脚读取到的模拟量存储
    digitalRead_value = digitalRead(
        26);  // Store the number read from pin 26. 将26号引脚读取到的数字量存储
    Serial.printf("Analog:%d\n", analogRead_value);
    Serial.printf("Digital:%d\n----\n", digitalRead_value);
    delay(200);
}
