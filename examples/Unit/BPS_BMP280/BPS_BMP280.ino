/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: BPS_BMP280.  压力传感器
* Date: 2021/8/10
******************************************** ***********************************
  Please connect to Port,Read atmospheric pressure and temperature and display
them on the display Serial 请连接,读取大气压强和温度并在显示屏上显示
*/
#include <M5Atom.h>
#include <Wire.h>  //The BPS uses I2C comunication.
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme;

void setup() {
    M5.begin();          // Init M5Atom.  初始化 M5Atom
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚
    while (!bme.begin(
        0x76)) {  // Init this sensor,True if the init was successful, otherwise
                  // false.   初始化传感器,如果初始化成功返回1
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    }
}

float pressure,
    Temp;  // Store the vuale of pressure and Temperature.  存储压力和温度()

void loop() {
    pressure = bme.readPressure();
    Temp     = bme.readTemperature();
    Serial.printf("Pre:%2.0fPa\nTem:%2.0f^C\n\n", pressure, Temp);
    delay(100);
}
