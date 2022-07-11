/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: NTP TIME.
* Date: 2021/8/3
*******************************************************************************/
#include <M5Atom.h>
#include <WiFi.h>
#include "time.h"

// Set the name and password of the wifi to be connected.
// 配置所连接wifi的名称和密码
const char* ssid     = "M5";
const char* password = "123456";

const char* ntpServer =
    "time1.aliyun.com";  // Set the connect NTP server.  设置连接的NTP服务器
const long gmtOffset_sec     = 0;
const int daylightOffset_sec = 3600;

void printLocalTime() {  // Output current time.  输出当前时间
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {  // Return 1 when the time is successfully
                                     // obtained.  成功获取到时间返回1
        Serial.println("Failed to obtain time");
        return;
    }
    Serial.println(&timeinfo,
                   "%A, %B %d \n%Y %H:%M:%S");  // Serial port output date and
                                                // time.  串口输出日期和时间
}

void setup() {
    M5.begin(true, false, true);  // Init Atom(Initialize serial port, LED).
                                  // 初始化 ATOM(初始化串口、LED)
    Serial.printf("\nConnecting to %s ", ssid);
    WiFi.begin(ssid, password);  // Connect wifi and return connection status.
                                 // 连接wifi并返回连接状态
    M5.dis.fillpix(0xff0000);  // Make the LED light show red.  使led灯显示红色
    while (WiFi.status() !=
           WL_CONNECTED) {  // If the wifi connection fails.  若wifi未连接成功
        delay(500);         // delay 0.5s.  延迟0.5s
        Serial.print(".");
    }
    Serial.println(" CONNECTED");
    configTime(gmtOffset_sec, daylightOffset_sec,
               ntpServer);  // init and get the time.  初始化并设置NTP
    printLocalTime();
    M5.dis.fillpix(0x00ff00);  // Make the LED light green.  使led灯显示绿色
    WiFi.disconnect(true);     // Disconnect wifi.  断开wifi连接
    WiFi.mode(WIFI_OFF);  // Set the wifi mode to off.  设置wifi模式为关闭
    delay(20);
}

void loop() {
    delay(1000);
    printLocalTime();
}