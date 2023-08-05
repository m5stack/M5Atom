/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: BasicHTTPClient.
* Date: 2021/8/4
******************************************************************************
*/
#include <M5Atom.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti;
HTTPClient http;

void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5Atom
    wifiMulti.addAP("YOUR-WIFINAME",
                    "YOUR_WIFIPASSWORD");  // Storage wifi configuration
                                           // information.  存储wifi配置信息
    Serial.print("\nConnecting Wifi...\n");  // Serial port format output
                                             // string.  串口格式化输出字符串
}

void loop() {
    if ((wifiMulti.run() ==
         WL_CONNECTED)) {  // wait for WiFi connection.  等待连接至wifi
        Serial.print("[HTTP] begin...\n");
        http.begin(
            "http://example.com/index.html");  // configure traged server and
                                               // url.  配置被跟踪的服务器和URL
        Serial.print("[HTTP] GET...\n");
        int httpCode = http.GET();  // start connection and send HTTP header.
                                    // 开始连接服务器并发送HTTP的标头
        if (httpCode >
            0) {  // httpCode will be negative on error.  出错时httpCode将为负值
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            if (httpCode ==
                HTTP_CODE_OK) {  // file found at server.  在服务器上找到文件
                String payload = http.getString();
                Serial.println(payload);  // 打印在服务器上读取的文件.  Print
                                          //  files read on the server
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n",
                          http.errorToString(httpCode).c_str());
        }

        http.end();
    } else {
        Serial.print("connect failed");
    }

    delay(5000);
}
