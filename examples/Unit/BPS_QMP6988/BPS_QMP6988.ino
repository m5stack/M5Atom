/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: BPS_QMP6988.  压力传感器
* Date: 2021/8/10
******************************************************************************
  Please connect to Port,Read atmospheric pressure and display them on the
display Serial 请连接端口,读取大气压强并在显示屏上显示
*/
#include <M5Atom.h>
#include "Wire.h"  //The BPS uses I2C comunication.
#include "UNIT_ENV.h"

QMP6988 qmp6988;

void setup() {
    M5.begin();          // Init M5Atom.  初始化 M5Atom
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚
}

void loop() {
    while (
        !qmp6988
             .init()) {  // Init qmp6988.True if the init was successful,
                         // otherwise false. 初始化qmp6988,如果初始化成功返回1
        Serial.println(
            "\nCould not find a valid qmp6988 sensor, check wiring!");
    }
    Serial.printf("Pressure:%0.2f\n",
                  qmp6988.calcPressure());  // Serial print format string.
                                            // 串口打印格式化字符串
    delay(2000);                            // Delay 2s.  延迟2s
}