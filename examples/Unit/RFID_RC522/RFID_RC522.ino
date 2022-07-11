/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  RFID.
* Date: 2021/8/19
*******************************************************************************
  Please connect to Port,Use the RFID Unit to read the Fudan card ID and display
the ID on the Serial. 请连接端口,使用RFID Unit 读取ID卡并在串口上显示。
*/

#include <M5Atom.h>
#include "MFRC522_I2C.h"

MFRC522 mfrc522(0x28);  // Create MFRC522 instance.  创建MFRC522实例

void setup() {
    M5.begin();  // Init M5Atom.  初始化M5Atom
    Serial.println("\n\nMFRC522 Test");
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚

    mfrc522.PCD_Init();  // Init MFRC522.  初始化 MFRC522
    Serial.println("Please put the card");
}

void loop() {
    if (!mfrc522.PICC_IsNewCardPresent() ||
        !mfrc522.PICC_ReadCardSerial()) {  //如果没有读取到新的卡片
        delay(200);
        return;
    }
    Serial.print("UID:");
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("");
}