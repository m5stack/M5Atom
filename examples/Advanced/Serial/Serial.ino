/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* describe：Serial.  串口发送接收
* date：2021/7/27
*******************************************************************************
*/

#include <M5Atom.h>

void setup() {
  M5.begin(true, false, true); //Init Atom(Initialize serial port, LED).  初始化 ATOM(初始化串口、LED)
}

void loop() {
  M5.dis.fillpix(0xFFA500);
  if(Serial.available()) {  //If serial port is available.  如果串口可用
    int ch = Serial.read(); //Store the data read by serial port to ch.  将串口读取到到数据存储至ch中
    Serial.write(ch); //Send data from ch to serial port.  将ch中的数据发送到串口
  }
}