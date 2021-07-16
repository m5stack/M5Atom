/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Matrix sample source code
* Visit the website for more information：https://docs.m5stack.com/en/products
*
* describe：MPU6886 example
* date：2021/7/15
*******************************************************************************
*/
#include "M5Atom.h"

CRGB led(0, 0, 0);
double pitch, roll; // Stores attitude related variables
double r_rand = 180 / PI;

// After Atom-Matrix is started or reset
// the program in the setUp () function will be run, and this part will only be run once.
void setup(){
    M5.begin(true, true, true); //Init Atom-Matrix(Initialize serial port, I2C ,LED matrix)
    M5.IMU.Init();  //Init IMU sensor
}

//Adjust the color of Atom-Matrix LED Matrix according to posture (optional)
CRGB HSVtoRGB(uint16_t h, uint16_t s, uint16_t v){
    CRGB ReRGB(0, 0, 0);
    int i;
    float RGB_min, RGB_max;
    RGB_max = v * 2.55f;
    RGB_min = RGB_max * (100 - s) / 100.0f;

    i = h / 60;
    int difs = h % 60;
    float RGB_Adj = (RGB_max - RGB_min) * difs / 60.0f;

    switch (i){
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
    default: // case 5:
        ReRGB.r = RGB_max;
        ReRGB.g = RGB_min;
        ReRGB.b = RGB_max - RGB_Adj;
        break;
    }
    return ReRGB;
}

//After the program in setup() runs, it runs the program in loop()
//The loop() function is an infinite loop in which the program runs repeatedly
void loop(){
    delay(50);  //Delay 50ms
    M5.IMU.getAttitude(&pitch, &roll);  //Read the attitude (pitch, heading) of the IMU and store it in relevant variables
    double arc = atan2(pitch, roll) * r_rand + 180;
    double val = sqrt(pitch * pitch + roll * roll);
    Serial.printf("%.2f,%.2f,%.2f,%.2f\n", pitch, roll, arc, val);  //serial port output the formatted string

    val = (val * 6) > 100 ? 100 : val * 6;
    led = HSVtoRGB(arc, val, 100);
    M5.dis.fillpix(led);    //Fill the whole LED lattice with the color obtained according to the attitude
}
