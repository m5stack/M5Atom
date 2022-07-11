/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/atom_matrix
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/atom_matrix
*
* Describe: RGB LED.  点阵示例
* Date: 2021/7/21
*******************************************************************************
*/
#include "M5Atom.h"

/* After Atom-Matrix is started or reset
the program in the setUp () function will be run, and this part will only be run
once. 在 ATOM-Matrix
启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin(true, false,
             true);  // Init Atom-Matrix(Initialize serial port, LED).  初始化
                     // ATOM-Matrix(初始化串口、LED点阵)
    delay(50);                    // delay 50ms.  延迟50ms
    M5.dis.drawpix(0, 0x00ff00);  // Light the LED with the specified RGB color
                                  // 00ff00(Atom-Matrix has only one light).
                                  // 以指定RGB颜色0x00ff00点亮第0个LED
}

uint8_t FSM = 0;  // Store the number of key presses.  存储按键按下次数

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    if (M5.Btn
            .wasPressed()) {  // Check if the key is pressed. 检测按键是否被按下
        switch (FSM) {
            case 0:
                M5.dis.drawpix(0, 0xfff000);  // YELLOW 黄色
                break;
            case 1:
                M5.dis.drawpix(0, 0xff0000);  // RED  红色
                break;
            case 2:
                M5.dis.drawpix(0, 0x0000f0);  // BLUE  蓝色
                break;
            case 3:
                M5.dis.drawpix(0, 0x00ff00);  // GREEN  绿色
                break;
            default:
                break;
        }
        FSM++;
        if (FSM >= 4) {
            FSM = 0;
        }
    }

    delay(50);
    M5.update();  // Read the press state of the key.  读取按键按下状态
}