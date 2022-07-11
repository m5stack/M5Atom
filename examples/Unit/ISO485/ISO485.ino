/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/iso485
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/iso485
*
* Product:  iso485.
* Date: 2021/8/30
*******************************************************************************
  Please connect to Port ,Pressed ButtonA :send "hello world"
  请连接端口 ,Pressed ButtonA :send "hello world"
*/

#include <M5Atom.h>

String str = "";

void setup() {
    M5.begin();
    Serial.println("ISO485");
    Serial2.begin(115200, SERIAL_8N1, 26, 32);
}

void loop() {
    if (M5.Btn.wasPressed()) {
        Serial2.write("HELLO World\r\n");
    }

    if (Serial2.available()) {
        char ch = Serial2.read();
        str += ch;
        if (str.endsWith("\r\n")) {
            Serial.print(str);
            str = "";
        }
    }
    M5.update();
}
