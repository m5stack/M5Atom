/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
* Visit the website for more information：https://docs.m5stack.com/en/products
*
* describe：RBG LED lattice example
* date：2021/7/15
*******************************************************************************
*/
#include "M5Atom.h"

// After Atom-Matrix is started or reset
// the program in the setUp () function will be run, and this part will only be run once.
void setup(){
    M5.begin(true, false, true);    //Init Atom-Matrix(Initialize serial port, LED matrix)
    delay(50);   //Delay 50ms
    M5.dis.drawpix(0, 0xf00000);    // Light the 0th LED with the specified RGB color f00000
}

uint8_t FSM = 0;    //Store the number of key presses

//After the program in setup() runs, it runs the program in loop()
//The loop() function is an infinite loop in which the program runs repeatedly
void loop(){
    if (M5.Btn.wasPressed()){   //Check if the key is pressed
        switch (FSM){
        case 0:
            M5.dis.drawpix(1, 0xfff000);
            break;
        case 1:
            M5.dis.drawpix(2, 0x00f000);    // Light the 2th LED with the specified RGB color 00f000 (LED Number : 0~24)
            break;
        case 2:
            M5.dis.drawpix(3, 0x0000f0);
            break;
        case 3:
            M5.dis.drawpix(4, 0x707070);
            break;
        default:
            break;
        }
        FSM++;
        if (FSM >= 4){
            FSM = 0;
        }
    }

    delay(50);
    M5.update();    //Read the press state of the key
}
