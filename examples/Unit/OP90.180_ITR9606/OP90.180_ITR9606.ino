/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: OP 180/90.  非接触式光电限位开关
* Date: 2021/8/16
*******************************************************************************
  Please connect to Port ,Detect the current OP 90/180 Unit Photoelectric switch
status. 请连接端口,检测当前OP 90/180单元光电开关状态。
*/

#include <M5Atom.h>

void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    Serial.println("90/180 OPTICAL");
    pinMode(32, INPUT_PULLUP);  // Set pin 32 to input pull-up mode.
                                // 设置32号引脚为输入上拉模式
}

void loop() {
    Serial.printf(
        "IR Receive: %d\n",
        digitalRead(32));  // Output the value of pin 32.  输出32号引脚的值
}
