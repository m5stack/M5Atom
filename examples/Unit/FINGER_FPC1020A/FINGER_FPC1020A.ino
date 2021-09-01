/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/unit/finger
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/unit/finger
*
* describe: Finger.
* date：2021/8/26
*******************************************************************************
*/

#include <M5Atom.h>
#include "M5_Finger.h"

uint8_t userNum;           //User number
FingerPrint FP_M;

void CleanSerial()
{
  userNum = FP_M.fpm_getUserNum();  //Get users Numbers.  获取用户数量
  Serial.print("userNum:");
  Serial.println(userNum);
}

void setup() {
  M5.begin();
  Serial.begin(115200);
  Serial2.begin(19200, SERIAL_8N1, 32, 26);
  Serial.println("Finger example");
  userNum = FP_M.fpm_getUserNum();
  Serial.print("userNum:");
  Serial.println(userNum);
}

void loop(){
  M5.update();
  uint8_t res1;
  //ButtonA: Add user.  添加用户
  if(M5.Btn.wasPressed()){
    CleanSerial();
    Serial.println("Fingerprint Typing");

    res1 = FP_M.fpm_addUser(userNum,1);
    if(res1 == ACK_SUCCESS){
      Serial.println("Success");
    }
    else if(res1 == ACK_FAIL){
      Serial.println("Fail");
    }
    else if(res1 == ACK_FULL){
      Serial.println("Full");
    }
    else{
      Serial.println("Timeout");
    }
    userNum++;
  }
}
