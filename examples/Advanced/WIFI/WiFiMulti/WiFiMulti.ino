/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: WIFI Multi.  多wifi择优
* Date: 2021/7/29
*******************************************************************************
*  Connect to the best AP based on a given wifi list
*  根据给定wifi的列表连接到最好的AP
*/

#include <M5Atom.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

void setup() {
    M5.begin(true, false, true);  // Init Atom(Initialize serial port, LED).
                                  // 初始化 ATOM(初始化串口、LED)
    wifiMulti.addAP(
        "cam",
        "6767");  // Storage wifi configuration information 1. 存储wifi配置信息1
    wifiMulti.addAP("wifi1", "12345566");
    wifiMulti.addAP("aaa", "sadf");
    M5.dis.fillpix(0xfff000);  // Light LED with the specified RGB color
                               // 0xfff000(Atom-Matrix has only one light).
                               // 以指定RGB颜色fff000点亮所有LED
    Serial.println("\n\nConnecting Wifi...");  // Serial port format output
                                               // string.  串口格式化输出字符串
    if (wifiMulti.run() ==
        WL_CONNECTED) {  // If the connection to wifi is established
                         // successfully.  如果与wifi成功建立连接
        Serial.print("WiFi connected\n\nSSID:");
        Serial.println(WiFi.SSID());  // Output Network name.  输出网络名称
        Serial.print("RSSI: ");
        Serial.println(WiFi.RSSI());  // Output signal strength.  输出信号强度
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());  // Output IP Address.  输出IP地址
    }
}

void loop() {
    if (wifiMulti.run() !=
        WL_CONNECTED) {  // If the connection to wifi is not established
                         // successfully.  如果没有与wifi成功建立连接
        Serial.println("WiFi not connected!");
        M5.dis.fillpix(0xff0000);
        delay(1000);
    } else {
        M5.dis.fillpix(0x00ff00);
        delay(1000);
    }
}