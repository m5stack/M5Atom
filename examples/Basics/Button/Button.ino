/****************************************************************
 * 
 * This Example is used to test button
 * 
 * Arduino tools Setting 
 * -board : M5StickC
 * -Upload Speed: 115200 / 750000 / 1500000
 * 
****************************************************************/

#include "M5Atom.h"

uint8_t DisBuff[2 + 5 * 5 * 3];

void setBuff(uint8_t Rdata, uint8_t Gdata, uint8_t Bdata)
{
    DisBuff[0] = 0x05;
    DisBuff[1] = 0x05;
    for (int i = 0; i < 25; i++)
    {
        DisBuff[2 + i * 3 + 0] = Rdata;
        DisBuff[2 + i * 3 + 1] = Gdata;
        DisBuff[2 + i * 3 + 2] = Bdata;
    }
}

void setup()
{
    M5.begin(true, false, true);
    delay(10);
    setBuff(0xff, 0x00, 0x00);
    M5.dis.displaybuff(DisBuff);
}

uint8_t FSM = 0;

void loop()
{
    if (M5.Btn.wasPressed())
    {

        switch (FSM)
        {
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
        M5.dis.displaybuff(DisBuff);

        FSM++;
        if (FSM >= 4)
        {
            FSM = 0;
        }
    }

    delay(50);
    M5.update();
}