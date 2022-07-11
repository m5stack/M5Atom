/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: Heart Rate.  心率
* Date: 2021/8/16
*******************************************************************************
  Please connect to Port , HEART Unit obtains the original value of the heart
rate detection and displays it on the Serial. The user can also use the Arduino
IDE Serial Plotter to view the line graph output. 请连接端口,HEART
Unit获取心率检测的原始值并显示在串口上。用户还可以使用Arduino IDE Serial
Plotter查看线图输出。
*/

#include <M5Atom.h>
#include "MAX30100.h"

#define SAMPLING_RATE   MAX30100_SAMPRATE_100HZ
#define IR_LED_CURRENT  MAX30100_LED_CURR_24MA
#define RED_LED_CURRENT MAX30100_LED_CURR_27_1MA
#define PULSE_WIDTH     MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE    true

MAX30100
sensor;  // Instantiate a MAX30100 sensor class.  实例化一个MAX30100传感器类

void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    Wire.begin(26, 32);
    Serial.print("Initializing MAX30100..");

    while (!sensor.begin()) {  // Initialize the sensor.  初始化传感器
        Serial.println("Sensor not found");
        delay(1000);
    }
    // Set up the wanted parameters.  设置所需的参数
    sensor.setMode(MAX30100_MODE_SPO2_HR);
    sensor.setLedsCurrent(IR_LED_CURRENT, RED_LED_CURRENT);
    sensor.setLedsPulseWidth(PULSE_WIDTH);
    sensor.setSamplingRate(SAMPLING_RATE);
    sensor.setHighresModeEnabled(HIGHRES_MODE);
}

void loop() {
    uint16_t ir, red;
    sensor.update();  //更新传感器读取到的数据
    while (sensor.getRawValues(&ir, &red)) {  //如果获取到数据
        Serial.printf("IR: %d\n", ir);
        Serial.printf("RED: %d\n", red);
    }
    delay(500);
}
