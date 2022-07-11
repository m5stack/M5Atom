/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: Button.  按键
* Date: 2021/8/9
*******************************************************************************
  Please connect to Port,Read the button status of BUTTON Unit and display it on
the Serial

  请连接端口,读取按键的状态并在显示屏上显示
*/
#include <M5Atom.h>

int last_value;
int cur_value;

void setup() {
    M5.begin();          // Init Atom.  初始化Atom
    pinMode(32, INPUT);  // set pin mode to input.设置引脚模式为输入模式
    Serial.println("Button example: ");
}

void loop() {
    cur_value = digitalRead(32);  // read the value of BUTTON.  读取22号引脚的值
    if (cur_value != last_value) {
        if (cur_value == 0) {
            Serial.println("Button1 Status: pressed");
            Serial.println("       value:  0");
        } else {
            Serial.println("Button1 Status: released");
            Serial.println("       value:  1");
        }
        last_value = cur_value;
    }
}
