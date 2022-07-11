/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atom_motion
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atom_motion
*
* Product:  Motion. 直流电机
* Date: 2021/9/1
*******************************************************************************
  Use ATOM Motion to control 4 channel servo and 2 channel DC motor,press btn to
change the DC motor direction 用ATOM
Motion控制4路伺服和2路直流电机，按下按键改变直流电机方向
*/

#include <M5Atom.h>
#include "AtomMotion.h"

AtomMotion Atom;
bool direction = true;

xSemaphoreHandle CtlSemaphore;

void GetStatus() {
    for (int ch = 1; ch < 5; ch++) {
        Serial.printf("Servo Channel %d: %d \n", ch, Atom.ReadServoAngle(ch));
    }
    Serial.printf("Motor Channel %d: %d \n", 1, Atom.ReadMotorSpeed(1));
    Serial.printf("Motor Channel %d: %d \n", 2, Atom.ReadMotorSpeed(2));
}

// servo angle range 0 ~ 180
// DC motor speed range -127~127

void TaskMotion(void *pvParameters) {
    while (1) {
        for (int ch = 1; ch < 5; ch++) {
            Atom.SetServoAngle(ch, 180);
        }
        GetStatus();
        vTaskDelay(1000 / portTICK_RATE_MS);
        for (int ch = 1; ch < 5; ch++) {
            Atom.SetServoAngle(ch, 0);
        }
        GetStatus();
        vTaskDelay(1000 / portTICK_RATE_MS);
        if (direction) {
            Atom.SetMotorSpeed(1, 100);
            Atom.SetMotorSpeed(2, 100);
            M5.dis.drawpix(0, 0xff0000);
        } else {
            Atom.SetMotorSpeed(1, -100);
            Atom.SetMotorSpeed(2, -100);
            M5.dis.drawpix(0, 0x0000ff);
        }
    }
}

void setup() {
    M5.begin(true, false, true);
    Atom.Init();  // sda  25     scl  21
    vSemaphoreCreateBinary(CtlSemaphore);
    xTaskCreatePinnedToCore(
        TaskMotion, "TaskMotion"  // A name just for task.  任务名称
        ,
        4096  // This stack size can be checked & adjusted by reading the Stack
              // Highwater.  可以通过阅读 Stack Highwater 来检查和调整此堆栈大小
        ,
        NULL, 2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                 // highest, and 0 being the lowest..  优先级，3
                 // (configMAX_PRIORITIES - 1) 最高，0 最低。
        ,
        NULL, 0);
}

void loop() {
    M5.update();
    if (M5.Btn.wasPressed()) {
        direction = !direction;
    }
}
