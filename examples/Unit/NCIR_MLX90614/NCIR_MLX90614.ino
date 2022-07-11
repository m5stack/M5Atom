/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/ncir
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/ncir
*
* Product:  ncir.  单点红外测温传感器
* Date: 2021/8/27
*******************************************************************************
  Please connect to Port,Use NCIR Unit to measure the temperature without
contact and display the value on the Serial.
  请连接端口,使用NCIR单元无接触测量温度，并在串口上显示。
*/
#include <M5Atom.h>

void setup() {
    M5.begin();
    Wire.begin(26, 32);
    Serial.print("NCIR");
}

void loop() {
    static uint16_t result;
    static float temperature;
    Wire.beginTransmission(0x5A);  // Send Initial Signal and I2C Bus Address
                                   // 发送初始信号和I2C总线地址
    Wire.write(0x07);  // Send data only once and add one address automatically.
                       // 只发送一次数据，并自动添加一个地址。
    Wire.endTransmission(false);  // Stop signal  停止信号
    Wire.requestFrom(
        0x5A, 2);  // Get 2 consecutive data from 0x5A, and the data is stored
                   // only.  从0x5A中获取2个连续的数据，并且只存储这些数据。
    result = Wire.read();        // Receive DATA  接收数据
    result |= Wire.read() << 8;  // Receive DATA  接收数据

    temperature = result * 0.02 - 273.15;
    Serial.printf("Temp:%.3f\n", temperature);
    delay(500);
}