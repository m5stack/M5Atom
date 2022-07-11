/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  Hdiver.
* Date: 2021/9/1
*******************************************************************************
*/
#include "M5Atom.h"
#include <Arduino.h>

const int IN1_PIN = 19;
const int IN2_PIN = 23;
int freq          = 10000;
int ledChannel1   = 0;
int ledChannel2   = 1;
int resolution    = 10;
bool direction    = true;
int VIN_PIN       = 33;
int FAULT_PIN     = 22;

void setup() {
    M5.begin(true, false, true);
    ledcSetup(ledChannel1, freq, resolution);
    ledcSetup(ledChannel2, freq, resolution);
    ledcAttachPin(IN1_PIN, ledChannel1);
    ledcAttachPin(IN2_PIN, ledChannel2);
    pinMode(VIN_PIN, INPUT);
    pinMode(FAULT_PIN, INPUT);
}

void loop() {
    if (M5.Btn.pressedFor(2000)) {
        M5.dis.drawpix(0, 0x000000);
        ledcWrite(ledChannel1, 0);
        ledcWrite(ledChannel2, 0);
    }

    if (M5.Btn.wasPressed()) {
        if (direction) {
            M5.dis.drawpix(0, 0x0000f0);
            ledcWrite(ledChannel1, 1000);
            ledcWrite(ledChannel2, 0);
        } else {
            M5.dis.drawpix(0, 0xff00f0);
            ledcWrite(ledChannel1, 0);
            ledcWrite(ledChannel2, 1000);
        }
        direction = !direction;
    }

    M5.update();
    Serial.println("VIN IN: " +
                   String((analogRead(VIN_PIN) * 10.0 / 4095.0) * 3.6));
    if (digitalRead(FAULT_PIN) == 0) {
        Serial.println("FAULT!");
    }
    delay(100);
}
