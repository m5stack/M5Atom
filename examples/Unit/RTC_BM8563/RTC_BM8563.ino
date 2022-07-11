/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product:  RTC.  实时时钟
* Date: 2021/8/18
*******************************************************************************
  Please connect to Port,The time is displayed on the Serial.
  请连接端口,串口上显示时间。
*/

#include "M5Atom.h"
#include "M5_BM8563.h"

BM8563 RTC;

rtc_time_type RTCtime;
rtc_date_type RTCdate;

char str_buffer[64];

void showlog(rtc_time_type *rtc_time, rtc_date_type *rtc_date) {
    sprintf(str_buffer, "RTC Time Now is %02d:%02d:%02d", rtc_time->Hours,
            rtc_time->Minutes, rtc_time->Seconds);
    Serial.println(str_buffer);
    sprintf(str_buffer, "RTC Date Now is %02d:%02d:%02d WeekDay:%02d",
            rtc_date->Year, rtc_date->Month, rtc_date->Date, rtc_date->WeekDay);
    Serial.println(str_buffer);
}

void setup() {
    M5.begin();          // Init M5Atom.  初始化M5Atom
    Wire.begin(26, 32);  // Initialize pin 26,32.  初始化26,32引脚
    RTC.begin();  // Example Initialize the RTC clock.  初始化RTC时钟
    RTCtime.Hours   = 14;  // Set the RTC clock time.  设置RTC时钟时间
    RTCtime.Minutes = 40;
    RTCtime.Seconds = 5;

    RTCdate.WeekDay = 4;  // Set the RTC clock date.  设置RTC时钟日期
    RTCdate.Month   = 7;
    RTCdate.Date    = 15;
    RTCdate.Year    = 2021;

    RTC.setTime(&RTCtime);  // Example Synchronize the set time to the RTC.
                            // 将设置的时间同步至RTC
    RTC.setDate(&RTCdate);  // Synchronize the set date to the RTC.
                            // 将设置的日期同步至RTC
}

void loop() {
    RTC.getTime(&RTCtime);  // To get the time.  获取时间
    RTC.getDate(&RTCdate);  // Get the date.  获取日期
    showlog(&RTCtime, &RTCdate);
    delay(1000);
}
