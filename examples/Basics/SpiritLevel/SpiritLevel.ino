/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
*                          配套  Atom-Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/atom_matrix
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/atom_matrix
*
* Describe: SpiritLevel
* Date: 2023/8/5
*******************************************************************************
  Shake the M5Atom and the matrix light will change with the position, you can
  set a new reference point by pressing the button.
  晃动M5Atom,矩阵灯将会随着位置的变化而变化,你可以通过按下按键来设定新的基准点位
*/
#include "M5Atom.h"

#define ALPHA       0.05  // smoothing
#define BETA        (1. - ALPHA)
#define SENSITIVITY 20.
#define BRIGHTNESS  255.
#define FADE        0.67  // determine the size of the lit area.  决定点亮区域的大小

bool IMU6886Flag =
    false;  // Stores the IMU initialization state.  存储IMU初始化状态

/* After Atom-Matrix is started or reset
the program in the setUp () function will be run, and this part will only be run
once. 在 ATOM-Matrix
启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin(true, false,
             true);  // Init Atom-Matrix(Initialize serial port, LED matrix).
                     // 初始化 ATOM-Matrix(初始化串口、LED点阵)
    if (!M5.IMU.Init())
        IMU6886Flag = true;  // The value returned from successful IMU
                             // initialization is 0.  IMU初始化成功返回值为0
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    M5.update();
    static float offX = 0., offY = 0.;
    static float smoX = 0., smoY = 0.;

    float accX = 0, accY = 0, accZ = 0;
    if (IMU6886Flag == true) {
        M5.IMU.getAccelData(&accX, &accY,
                            &accZ);  // Get the acceleration data of the three
                                     // axes.  获取三轴加速度数据
    }

    smoX = ALPHA * accX + BETA * smoX;
    smoY = ALPHA * accY + BETA * smoY;

    if (M5.Btn.wasPressed()) {  // Check if the key is pressed. 判断按键是否按下
        offX = smoX;  // Set the current position as the reference point.
        offY = smoY;  // 设定当前位置为基准点位
    }

    float xc = (offX - smoX) * SENSITIVITY + 2.0;
    if (xc < 0.) xc = 0.;
    if (xc > 4.) xc = 4.;
    float yc = (offY - smoY) * SENSITIVITY + 2.0;
    if (yc < 0.) yc = 0.;
    if (yc > 4.) yc = 4.;

    byte wht[25];

    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            float brt =
                BRIGHTNESS * (1. - FADE * ((xc - (float)x) * (xc - (float)x) +
                                           (yc - (float)y) * (yc - (float)y)));
            if (brt < 0.) brt = 0.;
            wht[x + 5 * y] = brt;
        }
    }

    for (int i = 0; i < 25; i++) {
        M5.dis.drawpix(
            i, wht[i] << 16 | wht[i] << 8 |
                   wht[i]);  // Continuously lights some LEDs with the specified
                             // RGB color.  以指定RGB颜色不断点亮某些LED
    }
}
