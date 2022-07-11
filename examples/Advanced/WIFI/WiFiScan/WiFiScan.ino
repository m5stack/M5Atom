/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: Wifi scan.  wifi扫描
* Date: 2021/7/28
*******************************************************************************
*/
#include <M5Atom.h>
#include "WiFi.h"

void setup() {
    M5.begin(true, true, true);  // Init M5Stack.  初始化M5Stack
    WiFi.mode(WIFI_STA);  // Set WiFi to station mode and disconnect from an AP
                          // if it was previously connected.
                          // 将WiFi设置为站模式，如果之前连接过AP，则断开连接
    WiFi.disconnect();  // Turn off all wifi connections.  关闭所有wifi连接
    delay(100);         // 100 ms delay.  延迟100ms
    M5.dis.drawpix(0, 0xfff000);  // Light yellow.  点亮黄色
    Serial.println("\nPlease press Btn to scan");
}

void loop() {
    M5.update();  // Check the status of the key.  检测按键的状态
    if (M5.Btn.isPressed()) {  // If button A is pressed.  如果按键A按下
        Serial.println("scan start");
        int n = WiFi.scanNetworks();  // return the number of networks found.
                                      // 返回发现的网络数
        if (n == 0) {  // If no network is found.  如果没有找到网络
            Serial.println("no networks found");
            M5.dis.fillpix(0xff0000);
        } else {  // If have network is found.  找到网络
            M5.dis.fillpix(0x00ff00);
            Serial.printf("networks found:%d\n\n", n);
            for (int i = 0; i < n;
                 ++i) {  // Print SSID and RSSI for each network found.
                         // 打印每个找到的网络的SSID和信号强度
                Serial.printf("%d:", i + 1);
                Serial.print(WiFi.SSID(i));
                Serial.printf("(%d)", WiFi.RSSI(i));
                Serial.println(
                    (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
                delay(10);
            }
        }
        delay(1000);
        Serial.println("\nPlease press Btn to rescan");
    }
}
