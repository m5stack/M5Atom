/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/finger
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/finger
*
* Product:  Finger.
* Date: 2021/10/28
*******************************************************************************
Short press the button to add a finger, short press the button to verify the
finger. 短按按键添加手指,短按按键验证手指
*/

#include <M5Atom.h>
#include "M5_FPC1020A.h"

FingerPrint FP_M;

void setup() {
    M5.begin(true, true, true);  // Init M5Atom.  初始化 M5Atom
    Serial.println("Finger Unit TEST");
    FP_M.begin(&Serial2, 32, 26);
}

void loop() {
    M5.update();
    uint8_t res1;
    static long time = 0, time2 = 0;
    bool state = false;
    if (M5.Btn.isPressed()) {
        M5.dis.fillpix(0xffff00);  // Light the LED with the specified RGB color
                                   // ffff00.  以指定RGB颜色ffff00点亮LED
        time = M5.Btn.lastChange();
        while (!M5.Btn.wasReleased()) {
            M5.update();
        }
        time2 = M5.Btn.lastChange();
        state = true;
    }

    if (state == true) {
        if ((time2 - time) < 300) {
            Serial.println("Start Fingerprint Typing");
            Serial.println("Put Your Finger on the sensor");
            Serial.println("wating....");
            res1 = FP_M.fpm_addUser(22, 1);  //(user_num, userPermission)
            if (res1 == ACK_SUCCESS) {
                Serial.println("Success");
                M5.dis.fillpix(0x00ff00);
            } else {
                Serial.println("Fail");
                M5.dis.fillpix(0xff0000);
            }
        } else if ((time2 - time) > 1000) {
            Serial.println("Start Verify Fingerprint");
            res1 = FP_M.fpm_compareFinger();
            if (res1 == ACK_SUCCESS) {
                M5.dis.fillpix(0x00ff00);
                Serial.println("Success");
                Serial.print("User ID: ");
                Serial.println(FP_M.fpm_getUserId());
            } else {
                Serial.println("No Such User");
                M5.dis.fillpix(0xff0000);
            }
        }
        state = false;
    }

    delay(200);
}
