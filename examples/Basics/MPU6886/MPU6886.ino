/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
*                          配套  Atom-Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/atom_matrix
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/core/atom_matrix
*
* Describe: MPU6886.  姿态传感器示例
* Date: 2021/7/21
*******************************************************************************
*/
#include "M5Atom.h"

CRGB led(0, 0, 0);
double pitch, roll;  // Stores attitude related variables.  存储姿态相关变量
double r_rand = 180 / PI;

/* After Atom-Matrix is started or reset
the program in the setUp () function will be run, and this part will only be run
once. 在 ATOM-Matrix
启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin(true, true,
             true);  // Init Atom-Matrix(Initialize serial port, LED matrix).
                     // 初始化 ATOM-Matrix(初始化串口、LED点阵)
    M5.IMU.Init();   // Init IMU sensor.  初始化姿态传感器
}

CRGB HSVtoRGB(
    uint16_t h, uint16_t s,
    uint16_t
        v) {  // Adjust the color of Atom-Matrix LED Matrix according to posture
              // (optional).  根据姿态调整ATOM-Matrix点阵LED颜色（可选择性添加）
    CRGB ReRGB(0, 0, 0);
    int i;
    float RGB_min, RGB_max;
    RGB_max = v * 2.55f;
    RGB_min = RGB_max * (100 - s) / 100.0f;

    i             = h / 60;
    int difs      = h % 60;
    float RGB_Adj = (RGB_max - RGB_min) * difs / 60.0f;

    switch (i) {
        case 0:
            ReRGB.r = RGB_max;
            ReRGB.g = RGB_min + RGB_Adj;
            ReRGB.b = RGB_min;
            break;
        case 1:
            ReRGB.r = RGB_max - RGB_Adj;
            ReRGB.g = RGB_max;
            ReRGB.b = RGB_min;
            break;
        case 2:
            ReRGB.r = RGB_min;
            ReRGB.g = RGB_max;
            ReRGB.b = RGB_min + RGB_Adj;
            break;
        case 3:
            ReRGB.r = RGB_min;
            ReRGB.g = RGB_max - RGB_Adj;
            ReRGB.b = RGB_max;
            break;
        case 4:
            ReRGB.r = RGB_min + RGB_Adj;
            ReRGB.g = RGB_min;
            ReRGB.b = RGB_max;
            break;
        default:  // case 5:
            ReRGB.r = RGB_max;
            ReRGB.g = RGB_min;
            ReRGB.b = RGB_max - RGB_Adj;
            break;
    }
    return ReRGB;
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    delay(50);  // Delay 50ms 延迟50ms
    M5.IMU.getAttitude(&pitch,
                       &roll);  // Read the attitude (pitch, heading) of the IMU
                                // and store it in relevant variables.
                                // 读取IMU的姿态（俯仰、航向）并存储至相关变量
    double arc = atan2(pitch, roll) * r_rand + 180;
    double val = sqrt(pitch * pitch + roll * roll);
    Serial.printf("%.2f,%.2f,%.2f,%.2f\n", pitch, roll, arc,
                  val);  // serial port output the formatted string.  串口输出

    val = (val * 6) > 100 ? 100 : val * 6;
    led = HSVtoRGB(arc, val, 100);
    M5.dis.fillpix(
        led);  // Fill the whole LED lattice with the color obtained according
               // to the attitude.  将根据姿态获取的颜色填充至整个LED点阵
}
