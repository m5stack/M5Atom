/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atomic_qr
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atomic_qr
*
* Product:  ATOM QR-CODE.
* Date: 2021/8/30
*******************************************************************************
  Please connect to Port ,Press button to scan, serial monitor will print
information 请连接端口,按下按钮扫描，串行显示器将打印信息
*/

#include <M5Atom.h>

#define TRIG 23
#define DLED 33

void setup() {
    M5.begin(true, false, true);
    Serial2.begin(
        9600, SERIAL_8N1, 22,
        19);  // Set the baud rate of serial port 2 to 9600,8 data bits, no
              // parity bits, and 1 stop bit, and set RX to 22 and TX to 19.
              // 设置串口二的波特率为9600,8位数据位,没有校验位,1位停止位,并设置RX为22,TX为19
    M5.dis.fillpix(0xfff000);  // YELLOW 黄色
    pinMode(TRIG, OUTPUT);
    pinMode(DLED, INPUT);
    digitalWrite(TRIG, HIGH);
}

void loop() {
    M5.update();
    if (M5.Btn.isPressed()) {
        digitalWrite(TRIG, LOW);
    } else {
        digitalWrite(TRIG, HIGH);
    }
    if (digitalRead(DLED) == HIGH) {  // If read the QR code.  如果读取到二维码
        M5.dis.fillpix(0x00ff00);  // GREEN  绿色
        while (Serial2.available() > 0) {
            char ch = Serial2.read();
            Serial.print(ch);
        }
    } else {
        M5.dis.fillpix(0xfff000);
    }
}
