/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
* Visit the website for more information：https://docs.m5stack.com/en/products
*
* describe：Button example
* date：2021/7/15
*******************************************************************************
*/
#include "M5Atom.h"

uint8_t DisBuff[2 + 5 * 5 * 3];  //Used to store RBG color values

void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata){  //Set the colors of LED
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++){
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }
}

// After Atom-Matrix is started or reset
// the program in the setup () function will be run, and this part will only be run once.
void setup(){
    M5.begin(true, false, true);    //Init Atom-Matrix(Initialize serial port, LED matrix)
    delay(10);  //Delay 10ms
    setBuff(0xff, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);    //Display the DisBuff color on the LED
}

uint8_t FSM = 0;    //Store the number of key presses

//After the program in setup() runs, it runs the program in loop()
//The loop() function is an infinite loop in which the program runs repeatedly
void loop(){
    M5.update();    //Read the press state of the key
    if (M5.Btn.wasPressed()){   //Check if the key is pressed
        switch (FSM){
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
        M5.dis.displaybuff(DisBuff);    //Display the DisBuff color on the LED

        FSM++;
        if (FSM >= 4){
            FSM = 0;
        }
    }
    delay(50);
}
