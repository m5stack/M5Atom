/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/rs485
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/rs485
*
* Product:  rs485.
* Date: 2021/8/30
*******************************************************************************
  Please connect to Port,Use RS485 Unit for serial communication, continuously
send "Hello", and display the received content on the serial.
  请连接端口,在EXT.IO
采用RS485单元串行通信，连续发送“Hello”，接收到的内容显示在串口上。
*/
#include <M5Atom.h>
#define RX_PIN 32
#define TX_PIN 26

int i = 0, s = 0;

void setup() {
    M5.begin();
    Serial.println("RS485 Unit test");
    Serial.begin(115200);
    Serial2.begin(
        115200, SERIAL_8N1, RX_PIN,
        TX_PIN);  // Set the baud rate of serial port 2 to 115200,8 data bits,
                  // no parity bits, and 1 stop bit, and set RX to 16 and TX
                  // to 17.
                  // 设置串口二的波特率为115200,8位数据位,没有校验位,1位停止位,并设置RX为16,TX为17
    delay(10);
    Serial2.read();
}

void loop() {
    Serial2.write("Hello\n");

    if (Serial2.available()) {
        Serial.print(char(Serial2.read()));
    }
    delay(100);
}
