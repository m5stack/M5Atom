/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atomhub_switch
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atomhub_switch
*
* Product:  Switch.
* Date: 2021/9/1
*******************************************************************************
  Press the key control switch1 when breathing with pink light, and press the
key control switch 2 when breathing with blue light
  在粉色光呼吸时按键控制开关1，在蓝光呼吸时按键控制开关2
*/

#include <M5Atom.h>

#define SWITCH1 22
#define SWITCH2 19

bool Num  = 0;
bool Num2 = 0;

void setup() {
    M5.begin(true, false, true);
    pinMode(SWITCH1, OUTPUT);
    pinMode(SWITCH2, OUTPUT);
}

void breathLight() {
    for (int i = 128; i > 0; i--) {
        M5.dis.drawpix(0, 0x00aaff);
        M5.dis.setBrightness(i);
        M5.update();
        delay(20);
    }
    for (int i = 0; i < 128; i++) {
        if (Num) {
            M5.dis.drawpix(0, 0xff0000);
        } else {
            M5.dis.drawpix(0, 0x00ff00);
        }
        if (M5.Btn.wasPressed()) {
            Num = 1 - Num;
            if (Num) {
                digitalWrite(SWITCH1, HIGH);
                Serial.print("switch1 high");
            } else {
                digitalWrite(SWITCH1, LOW);
                Serial.print("switch1 low");
            }
        }
        M5.dis.setBrightness(i);
        M5.update();
        delay(20);
    }
    for (int i = 128; i > 0; i--) {
        M5.dis.drawpix(0, 0xaa00ff);
        M5.dis.setBrightness(i);
        M5.update();
        delay(20);
    }
    for (int i = 0; i < 128; i++) {
        if (Num2) {
            M5.dis.drawpix(0, 0xff0000);
        } else {
            M5.dis.drawpix(0, 0x00ff00);
        }
        if (M5.Btn.wasPressed()) {
            Num2 = 1 - Num2;
            if (Num2) {
                digitalWrite(SWITCH2, HIGH);
                Serial.print("switch2 high");
            } else {
                digitalWrite(SWITCH2, LOW);
                Serial.print("switch2 low");
            }
        }
        M5.dis.setBrightness(i);
        M5.update();
        delay(20);
    }
}

void loop() {
    breathLight();
    M5.update();
}
