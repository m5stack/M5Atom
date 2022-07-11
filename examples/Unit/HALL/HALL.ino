/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  Hall.  霍尔传感器
* Date: 2021/8/18
*******************************************************************************
  Please connect to Port ,Displays a string on the Serial.
  请连接端口,在串口上显示字符串。
  Low-level signal can be generated when the magnet S pole is close to the front
of the sensor 当磁体S极靠近传感器前端时，会产生低电平信号 OR the N pole is close
to the back, and the internal LED indicator will light up, the Serial wiil
display 0. 或N极靠近背面，内部LED指示灯亮起，串口显示0。
*/

#include <M5Atom.h>

#define HALL 32

void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    Serial.print("\n\nHALL Sensor");
    pinMode(HALL,
            INPUT);  // Set the pins to which the Hall sensor is connected to
                     // the input mode.  将霍尔传感器所连接的引脚设置为输入模式
}

void loop() {
    bool status = digitalRead(HALL);
    Serial.printf("Hall status : %d\n", status);
    delay(200);
}
