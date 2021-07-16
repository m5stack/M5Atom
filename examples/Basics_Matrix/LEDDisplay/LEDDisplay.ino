/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
* Visit the website for more information：https://docs.m5stack.com/en/products
*
* describe：LED pattern movement Example
* date：2021/7/15
*******************************************************************************
*/

#include "M5Atom.h"

extern const unsigned char AtomImageData[375 + 2];  //External reference stores the array of images shown

bool IMU6886Flag = false;   //Close IMU6886

// After Atom-Matrix is started or reset
// the program in the setUp () function will be run, and this part will only be run once.
void setup(){
    M5.begin(true, false, true);    //Init Atom-Matrix(Initialize serial port, LED matrix)
    delay(50);  //Delay 50ms
}

// After M5Core is started or reset
// the program in the setUp () function will be run, and this part will only be run once.
void loop(){
    // Moves an AtomImageData 25 steps in the direction of a kmoveLeft at the specified speed of 200
    //Notice: Speed range 0~255
    M5.dis.animation((uint8_t *)AtomImageData, 200, LED_DisPlay::kMoveLeft, 25);
    delay(5250);
}
