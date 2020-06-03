/****************************************************************
 * 
 * This Example is used to test mpu6886
 * This Example only for M5Atom Matrix!
 * 
 * Arduino tools Setting 
 * -board : M5StickC
 * -Upload Speed: 115200 / 750000 / 1500000
 * 
****************************************************************/
#include "M5Atom.h"



CRGB led(0, 0, 0);
double pitch, roll;
double r_rand = 180 / PI;

void setup()
{
    M5.begin(true, true, true);
    M5.IMU.Init();
}

// R,G,B from 0-255, H from 0-360, S,V from 0-100

CRGB HSVtoRGB(uint16_t h, uint16_t s, uint16_t v)
{
    CRGB ReRGB(0, 0, 0);
    int i;
    float RGB_min, RGB_max;
    RGB_max = v * 2.55f;
    RGB_min = RGB_max * (100 - s) / 100.0f;

    i = h / 60;
    int difs = h % 60;
    float RGB_Adj = (RGB_max - RGB_min) * difs / 60.0f;

    switch (i)
    {
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

void loop()
{
    delay(50);
    M5.IMU.getAttitude(&pitch, &roll);
    double arc = atan2(pitch, roll) * r_rand + 180;
    double val = sqrt(pitch * pitch + roll * roll);
    Serial.printf("%.2f,%.2f,%.2f,%.2f\n", pitch, roll, arc, val);

    val = (val * 6) > 100 ? 100 : val * 6;
    led = HSVtoRGB(arc, val, 100);
    M5.dis.fillpix(led);
    M5.update();
;
}