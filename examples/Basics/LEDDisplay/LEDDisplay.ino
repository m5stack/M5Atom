/****************************************************************
 * 
 * This Example is used to test leds
 * This Example only for M5Atom Matrix!
 * 
 * Arduino tools Setting 
 * -board : M5StickC
 * -Upload Speed: 115200 / 750000 / 1500000
 * 
****************************************************************/
#include "M5Atom.h"

/* this Example only for M5Atom Matrix */

extern const unsigned char AtomImageData[375 + 2];

bool IMU6886Flag = false;

void setup()
{
    M5.begin(true, false, true);
    delay(50);
    M5.dis.animation((uint8_t *)AtomImageData, 200, LED_DisPlay::kMoveLeft, 18);
}

void loop()
{
    delay(500);
    M5.update();
}