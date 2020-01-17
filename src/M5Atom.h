// Copyright (c) M5Stack. All rights reserved.

// Licensed under the MIT license. See LICENSE file in the project root for full license information.
/**
 * \par Copyright (C), 2016-2017, M5Stack
 * \class M5Stack
 * \brief   M5Stack library.
 * @file    M5Stack.h
 * @author  M5Stack
 * @version V0.2.4
 * @date    2018/10/29
 * @brief   Header for M5Stack.cpp module
 *
 * \par Description
 * This file is a drive for M5Stack core.
 *
 * \par Method List:
 *
 *  System:
        M5.begin();
        M5.update();

    LED:

    void animation(uint8_t *buffptr, uint8_t amspeed, uint8_t ammode, int64_t amcount = -1);
    void displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0);
    void setBrightness(uint8_t brightness);
    void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color);
    void drawpix(uint8_t Number, CRGB Color);
    void clear();

    Button:
        M5.BtnA/B/C.read();
        M5.BtnA/B/C.isPressed();
        M5.BtnA/B/C.isReleased();
        M5.BtnA/B/C.wasPressed();
        M5.BtnA/B/C.wasReleased();
        M5.BtnA/B/C.wasreleasedFor()
        M5.BtnA/B/C.pressedFor(uint32_t ms);
        M5.BtnA/B/C.releasedFor(uint32_t ms);
        M5.BtnA/B/C.lastChange();
 */
// #define ESP32

#ifndef _M5ATOM_H_
#define _M5ATOM_H_

#if defined(ESP32)

#include <Arduino.h>
#include <Wire.h>
#include <FastLED.h>

#include "utility/MPU6886.h"
#include "utility/Button.h"
#include "utility/LED_Display.h"

class M5Atom
{
private:
	bool _isInited = false;
	/* data */
public:
	M5Atom(/* args */);
	~M5Atom();

	MPU6886 IMU;
	LED_Display dis;

	Button Btn = Button(39, true, 10);

	void begin(bool SerialEnable = true, bool I2CEnable = true, bool DisplayEnable = false);
	void update();
};

extern M5Atom M5;

#else
#error “This library only supports boards with ESP32 processor.”
#endif
#endif
