/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* describe：ENVIII_SHT30_QMP6988.  环境传感器
* date：2021/8/17
*******************************************************************************
  Please connect to Port A,Read temperature, humidity and atmospheric pressure and display them on the display screen
  请连接端口A,读取温度、湿度和大气压强并在显示屏上显示
*/
#include <M5Atom.h>
#include "Adafruit_Sensor.h"
#include <Adafruit_BMP280.h>
#include "UNIT_ENV.h"

SHT3X sht30;
QMP6988 qmp6988;

float tmp = 0.0;
float hum = 0.0;
float pressure = 0.0;

void setup() {
  M5.begin(); //Init M5Atom.  初始化M5Atom
  Wire.begin(26,32);  //Initialize pin 26,32.  初始化26,32引脚
  qmp6988.init();
  Serial.println(F("ENV Unit III test"));
}

void loop() {
  pressure = qmp6988.calcPressure();
  if(sht30.get()==0){ //Obtain the data of shT30.  获取sht30的数据
    tmp = sht30.cTemp;  //Store the temperature obtained from shT30.  将sht30获取到的温度存储
    hum = sht30.humidity; //Store the humidity obtained from the SHT30.  将sht30获取到的湿度存储
  }else{
    tmp=0,hum=0;
  }
  Serial.printf("Temp: %2.1f  \r\nHumi: %2.0f%%  \r\nPressure:%2.0fPa\r\n---\n", tmp, hum, pressure);
  delay(2000);
}
