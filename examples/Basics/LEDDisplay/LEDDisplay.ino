#include "M5Atom.h"

/* this Example only for M5Atom Matrix */

extern const unsigned char AtomImageData[375 + 2];

bool IMU6886Flag = false;

void setup()
{
    M5.begin(true, false, true);
    delay(50);
    M5.dis.animation((uint8_t *)AtomImageData, 200, LED_Display::kMoveLeft, 18);
}

void loop()
{
    delay(500);
    M5.update();
}