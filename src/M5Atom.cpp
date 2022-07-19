// Copyright (c) M5Stack. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "M5Atom.h"

M5Atom::M5Atom() {
}

M5Atom::~M5Atom() {
}

void M5Atom::begin(bool SerialEnable, bool I2CEnable, bool DisplayEnable) {
    if (_isInited) return;

    _isInited = true;

    if (I2CEnable) {
        Wire.begin(25, 21, 100000UL);
    }
    if (SerialEnable) {
        Serial.begin(115200);
        Serial.flush();
        delay(50);
        Serial.println("M5Atom initializing...OK");
    }

    if (DisplayEnable) {
        dis.begin();
        dis.setTaskName("LEDs");
        dis.setTaskPriority(2);
        M5.dis.setCore(1);
        dis.start();
    }
}

void M5Atom::update() {
    M5.Btn.read();
}

M5Atom M5;
