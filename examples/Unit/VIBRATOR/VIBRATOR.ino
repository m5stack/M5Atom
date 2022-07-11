/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  Vibrator.  震动电机
* Date: 2021/8/19
*******************************************************************************
  Please connect to Port,Adjust the speed of VIBRATOR Unit through PWM.
  请连接端口,通过PWM调节Vibrator Unit的速度。
*/

#include <M5Atom.h>

#define motor_pin 26
int freq       = 10000;
int ledChannel = 0;
int resolution = 10;
void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    ledcSetup(
        ledChannel, freq,
        resolution);  // Sets the frequency and number of counts corresponding
                      // to the channel.  设置通道对应的频率和计数位数
    ledcAttachPin(
        motor_pin,
        ledChannel);  // Binds the specified channel to the specified I/O port
                      // for output.  将指定通道绑定到指定 IO 口上以实现输出
}

void loop() {
    Serial.println("Vibrator");
    ledcWrite(ledChannel, 512);  // Output PWM.  输出PWM
    delay(1000);
    ledcWrite(ledChannel, 0);
    delay(1000);
}
