/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: Angle.  角度计
* Date: 2021/8/9
*******************************************************************************
  Description: Read the Angle of the angometer and convert it to digital display
  读取角度计的角度，并转换为数字量显示
*/

#include <M5Atom.h>
int sensorPin =
    32;  // set the input pin for the potentiometer.  设置角度计的输入引脚

int last_sensorValue =
    100;  // Stores the value last read by the sensor.  存储传感器上次读取到的值
int cur_sensorValue = 0;  // Stores the value currently read by the sensor.
                          // 存储传感器当前读取到的值

void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5Atom
    pinMode(
        sensorPin,
        INPUT);  // Sets the specified pin to input mode. 设置指定引脚为输入模式
    dacWrite(25, 0);
}

void loop() {
    cur_sensorValue = analogRead(
        sensorPin);  // read the value from the sensor.  读取当前传感器的值
    if (abs(cur_sensorValue - last_sensorValue) >
        10) {  // If the difference is more than 10.  如果差值超过10
        Serial.print("the value of ANGLE: ");
        Serial.println(cur_sensorValue);
        last_sensorValue = cur_sensorValue;
    }
    delay(200);
}
