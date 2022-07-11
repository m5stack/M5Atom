/*
*******************************************************************************
* Copyright (c) 2022 by M5Stack
*                  Equipped with M5Atom sample source code
*                          配套  M5Atom 示例源代码
* Visit the website for more
information：https://docs.m5stack.com/en/app/scales_kit
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/app/scales_kit
*
* Product:  SCALES KIT WEIGHT UNIT EXAMPLE.
* Date: 2022/02/23
*******************************************************************************
UNIT is connected to port A (G32/33), press the center button to tare when there
is no load UNIT连接至端口A（G32/33），无负重情况下按下中心按键去处皮重
Libraries:
  - [HX711](https://github.com/bogde/HX711)

*/

#include <M5Atom.h>
#include "HX711.h"

// HX711 related pin Settings.  HX711 相关引脚设置
#define LOADCELL_DOUT_PIN 32
#define LOADCELL_SCK_PIN  26

HX711 scale;

void setup() {
    M5.begin(true, false, true);
    Serial.println("Calibration sensor....");
    M5.dis.fillpix(0xff0000);
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    // The scale value is the adc value corresponding to 1g
    scale.set_scale(27.61f);  // set scale
    scale.tare();             // auto set offset
    M5.dis.fillpix(0x00ff00);
    Serial.println("Connect the Weight Unit to PortA(G26,32)");
    Serial.println("Click Btn A for Tare deduction");
    Serial.println("Click Btn B Switch to Calibration mode");
}

void loop() {
    float weight = scale.get_units(1) / 1000.0;
    if (weight >= 0) {
        Serial.printf("Weight: %.2fkg \r\n", weight);
    } else {
        Serial.println("Weight: 0.00kg");
    }
    M5.update();
    if (M5.Btn.wasPressed()) {
        M5.dis.setBrightness(100);
        M5.dis.fillpix(0x0000ff);
        scale.tare();
        delay(500);
        M5.dis.fillpix(0x00ff00);
    }
    M5.dis.setBrightness(map(int(weight), 0, 5, 0, 100));
    FastLED.show();
}
