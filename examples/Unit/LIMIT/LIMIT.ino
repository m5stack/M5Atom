/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5Stack ATOM sample source code
*                          配套  M5Stack ATOM 示例源代码
* Visit the website for more information:
* 获取更多资料请访问:
*
* Product:  Limit.
* Date: 2022/6/1
*******************************************************************************
*/

#include <M5Atom.h>

#define KEY_PIN 32  // Define Limit Pin.  定义Limit连接引脚

void setup() {
    M5.begin();  // Init M5Stack  初始化M5Stack

    pinMode(KEY_PIN, INPUT_PULLUP);  // Init Limit pin.  初始化Limit引脚.
}

void loop() {
    if (!digitalRead(KEY_PIN)) {  // If Limit was hit.  如果触碰了Limit.
        Serial.println("Hit limit!");
    }
    delay(100);
}
