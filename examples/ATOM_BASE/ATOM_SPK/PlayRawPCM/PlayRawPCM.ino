/*
    Description: 
    Use ATOM SPK Compile and play PCM files
*/


#include "M5Atom.h"
#include "AtomSPK.h"

extern const unsigned char chocobo[582120];

ATOMSPK _AtomSPK;

void setup(){
    M5.begin(true,false,true);
    _AtomSPK.begin();
    M5.dis.drawpix(0, 0xf00000);
    _AtomSPK.playBeep();
    
}

void loop(){

    if(M5.Btn.isPressed()){
        while(1) _AtomSPK.playRAW(chocobo, sizeof(chocobo),true,false);
    }
    M5.update();
}
