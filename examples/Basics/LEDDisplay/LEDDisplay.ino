/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
*                          配套  Atom-Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/atom_matrix
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/atom_matrix
*
* Describe: LED pattern display.  LED图案显示
* Date: 2021/9/2
*******************************************************************************
*/
#include "M5Atom.h"

extern const unsigned char
    AtomImageData[375 + 2];  // External reference stores the array of images
                             // shown.  外部引用存储所示图像的数组

bool IMU6886Flag = false;  // Close IMU6886.  关闭IMU6886

/* After Atom-Matrix is started or reset
the program in the setUp () function will be run, and this part will only be run
once. 在 ATOM-Matrix
启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin(true, false,
             true);  // Init Atom-Matrix(Initialize serial port, LED matrix).
                     // 初始化 ATOM-Matrix(初始化串口、LED点阵)
    delay(50);       // Delay 50ms.  延迟50ms
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    // Moves an AtomImageData 25 steps in the direction of a kmoveLeft at the
    // specified speed of 200
    // Notice: Speed range 0~255
    //将某个图案AtomImageData以指定速度200向指定方向kMoveLeft移动25步(速度范围0~255)
    M5.dis.setWidthHeight(25, 5);  // Set the width and height of the display
                                   // pattern.  设置显示图案的宽高
    M5.dis.animation((uint8_t *)AtomImageData, 200, LED_DisPlay::kMoveLeft, 25);
    delay(5250);
}
