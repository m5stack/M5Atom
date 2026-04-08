/*
 * SPDX-FileCopyrightText: 2026 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "M5Atom.h"
#include "AtomSPK.h"

extern const unsigned char chocobo[582120];

ATOMSPK AtomSPK;

void setup() {
    M5.begin(true, false, true);
    AtomSPK.begin();
    M5.dis.drawpix(0, 0x00ff00);
    AtomSPK.playBeep();
}

void loop() {
    if (M5.Btn.isPressed()) {
        while (1) AtomSPK.playRAW(chocobo, sizeof(chocobo), true, false);
    }
    M5.update();
}
