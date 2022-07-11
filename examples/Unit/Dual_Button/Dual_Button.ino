/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: Button_Two.  双按键
* Date: 2021/8/9
*******************************************************************************
  Please connect to Port,Read the button status of BUTTON Unit and display it on
the Serial

  请连接端口,读取按键的状态并在显示屏上显示
*/
#include <M5Atom.h>

int last_value1 = 0, last_value2 = 0;
int cur_value1 = 0, cur_value2 = 0;

void setup() {
    M5.begin();          // Init Atom.  初始化 Atom
    pinMode(32, INPUT);  // set pin mode to input.设置引脚模式为输入模式
    pinMode(26, INPUT);
    Serial.println("Button example: ");
}

void loop() {
    cur_value1 = digitalRead(32);  // read the value of BUTTON. 读取22号引脚的值
    cur_value2 = digitalRead(26);
    if (cur_value1 != last_value1) {
        if (cur_value1 == 0) {
            Serial.println("Button1 Status: pressed");
            Serial.println("       value:  0");
        } else {
            Serial.println("Button1 Status: released");
            Serial.println("       value:  1");
        }
        last_value1 = cur_value1;
    }
    if (cur_value2 != last_value2) {
        if (cur_value2 == 0) {
            Serial.println("Button2 Status: pressed");
            Serial.println("       value:  0");
        } else {
            Serial.println("Button2 Status: released");
            Serial.println("       value:  1");
        }
        last_value2 = cur_value2;
    }
}
