/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: ENVII_DH12_BMP280.  环境传感器
* Date: 2021/8/17
*******************************************************************************
  Please connect to Port A,Read temperature, humidity and atmospheric pressure
and display them on the display Serial
  请连接端口A,读取温度、湿度和大气压强并在显示屏上显示
*/

#include <M5Atom.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "UNIT_ENV.h"

DHT12 dht12;
Adafruit_BMP280 bme;

void setup() {
    M5.begin();          // Init M5Atom.  初始化M5Atom
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚
    Serial.println(F("ENV Unit(DHT12 and BMP280) test"));
}

void loop() {
    while (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    }
    float tmp = dht12.readTemperature();  // Store the temperature obtained from
                                          // dht12.  将dht12获取到的温度存储
    float hum = dht12.readHumidity();  // Store the humidity obtained from the
                                       // dht12.  将dht12获取到的湿度存储
    float pressure = bme.readPressure();  // Stores the pressure gained by BMP.
                                          // 存储bmp获取到的压强
    Serial.printf(
        "Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n------\n", tmp,
        hum, pressure);

    delay(2000);
}
