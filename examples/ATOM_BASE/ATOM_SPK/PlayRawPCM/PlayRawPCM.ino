/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite sample source code
*                          配套  Atom-Lite 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atom_spk
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atom_spk
*
* Product:  SPK.
* Date: 2021/9/1
*******************************************************************************
  Use ATOM SPK Compile and play PCM files.  使用ATOM SPK编译和播放PCM文件
*/

#include "M5Atom.h"
#include "AtomSPK.h"

extern const unsigned char chocobo[582120];

ATOMSPK _AtomSPK;

void setup() {
    M5.begin(true, false, true);
    _AtomSPK.begin();
    M5.dis.drawpix(0, 0x00ff00);
    _AtomSPK.playBeep();
}

void loop() {
    if (M5.Btn.isPressed()) {
        while (1) _AtomSPK.playRAW(chocobo, sizeof(chocobo), true, false);
    }
    M5.update();
}
