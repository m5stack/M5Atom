/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* For more information, visit: https://docs.m5stack.com/en/atom/atomic485
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/atom/atomic485
*
* Describe: RS485
* Date: 2022/5/21
*******************************************************************************
  When the serial port sends or receives messages, the LED lights up,Press
  button to send character
  当串口发送或接收信息时，LED灯亮起，按下按钮发送字符
*/

#include <M5Atom.h>

void setup() {
    M5.begin(true, false, true);
    // Serial2.begin(unsigned long baud, uint32_t config, int8_t rxPin, int8_t
    // txPin, bool invert)
    Serial2.begin(115200, SERIAL_8N1, 22, 19);
}

void loop() {
    if (M5.Btn.wasPressed()) {        // Press the button to send a
                                      // message.按下按键发送信息
        M5.dis.drawpix(0, 0xff00ff);  // Set the light to purple. 设置灯为紫色
        M5.update();
        Serial2.write('a');
        delay(50);
    } else {
        M5.dis.drawpix(0, 0x000000);
    }
    if (Serial2.available()) {    // If the serial port receives a
                                  // message. 如果串口收到信息
        int ch = Serial2.read();  // Read the message. 读取信息
        Serial.write(ch);
        M5.dis.drawpix(0, 0x00ffff);
        M5.update();
        delay(50);
    } else {
        M5.dis.drawpix(0, 0x000000);
    }
    M5.update();
}