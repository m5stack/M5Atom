/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: WIFI Smart Config.  WIFI智能配网
* Date: 2021/7/30
*******************************************************************************
*  Fill in WIFI configuration information through mobile APP to connect M5Atom
*to relevant WIFI 通过手机APP填写WIFI配置信息使 M5Atom连接至相关WIFI APP
*Download Address:
*https://www.espressif.com/en/products/software/esp-touch/resources APP下载地址:
*https://www.espressif.com/zh-hans/products/software/esp-touch/resources
*/
#include <M5Atom.h>
#include "WiFi.h"

void setup() {
    M5.begin(true, false, true);  // Init Atom(Initialize serial port, LED).
                                  // 初始化 ATOM(初始化串口、LED)
    WiFi.mode(WIFI_AP_STA);   // Set the wifi mode to the mode compatible with
                              // the AP and Station, and start intelligent
                              // network configuration
    WiFi.beginSmartConfig();  // 设置wifi模式为AP 与 Station
                              // 兼容模式,并开始智能配网
    M5.dis.fillpix(
        0xfff000);  // Light LED with the specified RGB color F00000(Atom-Matrix
                    // has only one light).  以指定RGB颜色fff000点亮所有LED
    // Wait for the M5Atom to receive network information from the phone
    //等待M5Atom接收到来自手机的配网信息
    Serial.print(
        "\nWaiting for Phone SmartConfig.");  // Serial port format output
                                              // string.  串口格式化输出字符串
    while (!WiFi.smartConfigDone()) {  // If the smart network is not completed.
                                       // 若智能配网没有完成
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nSmartConfig received.");

    Serial.println("Waiting for WiFi\n");
    while (
        WiFi.status() !=
        WL_CONNECTED) {  // M5Atom will connect automatically upon receipt of
                         // the configuration information, and return true if
                         // the connection is successful.
                         // 收到配网信息后M5Atom将自动连接，若连接成功将返回true
        delay(500);
        Serial.print(".");
    }
    M5.dis.fillpix(0x00ff00);
    Serial.print("WiFi Connect To: ");
    Serial.println(WiFi.SSID());  // Output Network name.  输出网络名称
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  // Output IP Address.  输出IP地址
    Serial.print("RSSI: ");
    Serial.println(WiFi.RSSI());  // Output signal strength.  输出信号强度
}

void loop() {
}