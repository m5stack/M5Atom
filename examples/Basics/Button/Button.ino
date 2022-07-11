/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more
*information：https://docs.m5stack.com/en/core/atom_matrix
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/atom_matrix
*
* Product: Button example.  按键示例
* Date: 2021/7/21
*******************************************************************************
*/
#include "M5Atom.h"

uint8_t
    DisBuff[2 + 5 * 5 * 3];  // Used to store RGB color values.  用来存储RBG色值

void setBuff(uint8_t Rdata, uint8_t Gdata,
             uint8_t Bdata) {  // Set the colors of LED, and save the relevant
                               // data to DisBuff[].  设置RGB灯的颜色
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++) {
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }
}
/* After Atom-Matrix is started or reset
the program in the setUp () function will be run, and this part will only be run
once. 在 ATOM-Matrix
启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin(true, false,
             true);  // Init Atom-Matrix(Initialize serial port, LED).  初始化
                     // ATOM-Matrix(初始化串口、LED点阵)
    delay(10);  // delay10ms.  延迟10ms
    setBuff(0xff, 0x00, 0x00);
    M5.dis.displaybuff(
        DisBuff);  // Display the DisBuff color on the LED.  同步所设置的颜色
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
                setBuff(0x40, 0x00, 0x00);
                break;
            case 1:
                setBuff(0x00, 0x40, 0x00);
                break;
            case 2:
                setBuff(0x00, 0x00, 0x40);
                break;
            case 3:
                setBuff(0x20, 0x20, 0x20);
                break;
            default:
                break;
        }
        M5.dis.displaybuff(DisBuff);

        FSM++;
        if (FSM >= 4) {
            FSM = 0;
        }
    }
    delay(50);
    M5.update();  // Read the press state of the key.  读取按键按下状态
}
