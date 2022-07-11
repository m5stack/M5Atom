/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/trace
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/trace
*
* Product:  TRACE.
* Date: 2021/9/1
*******************************************************************************
  Please connect to PORT, Read the status of the four line-tracking sensors of
TRACE Unit and output them through UART. 请连接端口,读取TRACE
Unit四个线跟踪传感器的状态，并通过UART输出。
*/

#include <M5Atom.h>

// #define VALUE_SPLIT

uint8_t value;
int SensorArray[4] = {0};

void SensorStatus(void) {
    Wire.beginTransmission(
        0x5a);  // The data transfer to 0x5A begins.  开始向0x5a传输数据
    Wire.write(0x00);
    Wire.endTransmission();  // End the data transmission.结束数据传输
    Wire.requestFrom(0x5a, 1);  // Request a byte from 0x5a.  向0x5a请求一个字节
    while (Wire.available()) {  // If data is received.  如果数据被接收到
        value = Wire.read();
    }
    Serial.print(" value = ");
    Serial.println(value, HEX);
#ifdef VALUE_SPLIT
    SensorArray[3] = (value & 0x08) >> 3;
    SensorArray[2] = (value & 0x04) >> 2;
    SensorArray[1] = (value & 0x02) >> 1;
    SensorArray[0] = (value & 0x01) >> 0;
    Serial.println("     After splitting... ");
    Serial.print("     SensorArray[0] = ");
    Serial.println(SensorArray[0]);
    Serial.print("     SensorArray[1] = ");
    Serial.println(SensorArray[1]);
    Serial.print("     SensorArray[2] = ");
    Serial.println(SensorArray[2]);
    Serial.print("     SensorArray[3] = ");
    Serial.println(SensorArray[3]);
#endif
}

void setup() {
    M5.begin();

    Wire.begin();
    Serial.println("TRACE example");
}

void loop() {
    SensorStatus();
    delay(100);
}