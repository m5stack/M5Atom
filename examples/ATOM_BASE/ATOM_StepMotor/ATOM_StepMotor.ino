/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atomic_step_motor
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atomic_step_motor
*
* Product:  ATOM STEPMOTOR.
* Date: 2021/8/31
*******************************************************************************
  Please connect to Port ,Press button the stepmotor will turn 5000 steps
clockwise then turn 5000 steps anti-clockwise
  请连接端口,按下按钮步进电机顺时针旋转5000步，然后逆时针旋转5000步
*/

#include <M5Atom.h>
#include "StepperDriver.h"

int motor_steps     = 200;
int step_divisition = 32;
int en_pin          = 22;
int dir_pin         = 23;
int step_pin        = 19;

int step  = 0;
int speed = 0;

StepperDriver ss(motor_steps, step_divisition, en_pin, dir_pin, step_pin);

void setup() {
    M5.begin(true, false, true);
    ss.setSpeed(0);  // Sets the speed in revs per minute.  设置转速(转/分)
    ss.powerEnable(true);
    M5.dis.fillpix(0x00ff00);  // GREEN  绿色
    delay(1600);
}

void loop() {
    if (M5.Btn.wasPressed()) {
        ss.setSpeed(300);
        ss.step(5000);  // Set the motor steps_to_move steps. 设置电机移动步长。
        ss.step(-5000);  // If the number is negative, the motor moves in the
                         // reverse direction.如果数字是负数，电机反方向运动。
    }
    M5.update();
}
