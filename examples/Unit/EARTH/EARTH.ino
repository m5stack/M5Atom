/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: EARTH.  土壤湿度
* Date: 2021/8/11
*******************************************************************************
  Please connect to Port ,Read the analog quantity and digital quantity returned
by the EARTH unit, and convert the analog quantity into 12-bit data and display
it on the Serial. 请连接端口,读取EARTH Unit
返回的模拟量和数字量，并将模拟量转换为12位数据显示在串口上。
*/

#include <M5Atom.h>

void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5Atom
    Serial.printf("UNIT_EARTH EXAMPLE\n");
    pinMode(26, INPUT);  // Set pin 26 to input mode.  将引脚26设置为输入模式
}

void loop() {
    Serial.printf("AnalogRead:%d\n", analogRead(32));
    Serial.printf("DigitalRead:%d\n", digitalRead(26));
    delay(1000);
}
