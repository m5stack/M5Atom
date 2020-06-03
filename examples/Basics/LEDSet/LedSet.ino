/****************************************************************
 * 
 * This Example is used to test leds
 * 
 * Arduino tools Setting 
 * -board : M5StickC
 * -Upload Speed: 115200 / 750000 / 1500000
 * 
****************************************************************/
#include "M5Atom.h"

void setup()
{
    M5.begin(true, false, true);
    delay(50);
    M5.dis.drawpix(0, 0xf00000);
}

uint8_t FSM = 0;

void loop()
{
    if (M5.Btn.wasPressed())
    {

        switch (FSM)
        {
        case 0:
            M5.dis.drawpix(0, 0xf00000);
            break;
        case 1:
            M5.dis.drawpix(0, 0x00f000);
            break;
        case 2:
            M5.dis.drawpix(0, 0x0000f0);
            break;
        case 3:
            M5.dis.drawpix(0, 0x707070);
            break;
        default:
            break;
        }
        FSM++;
        if (FSM >= 4)
        {
            FSM = 0;
        }
    }

    delay(50);
    M5.update();
}