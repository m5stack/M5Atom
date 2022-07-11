/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: OTA Upload.  隔空传输程序
* Date: 2021/7/30
*******************************************************************************
  PC and M5Atom can only be used on the same wifi.
电脑和M5Atom需在同一wifi下才可使用 When the OTA is ready, restart the Arduino
client from Tools > Ports > Network ports to instantly transmit the program
wirelessly. OTA 准备好后重启Arduino客户端在工具->端口->网络端口,即刻无线传输程序
*/
#include <M5Atom.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

// Set the name and password of the wifi to be connected.
// 配置所连接wifi的名称和密码
const char* ssid     = "M5wifi";
const char* password = "2134123";

void setup() {
    M5.begin(true, false, true);  // Init Atom(Initialize serial port, LED).
                                  // 初始化 ATOM(初始化串口、LED)
    M5.dis.fillpix(
        0x00ff00);  // Light LED with the specified RGB color F00000(Atom-Matrix
                    // has only one light).  以指定RGB颜色00ff00点亮所有LED
    WiFi.begin(ssid, password);  // Connect wifi and return connection status.
                                 // 连接wifi并返回连接状态
    while (WiFi.status() !=
           WL_CONNECTED) {  // If the wifi connection fails.  若wifi未连接成功
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
    Serial.print("WiFi Connect To: ");
    Serial.println(WiFi.SSID());  // Output Network name.  输出网络名称
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  // Output IP Address.  输出IP地址

    ArduinoOTA.setHostname(
        "M5Atom");  // Set the network port name.  设置网络端口名称
    ArduinoOTA.setPassword("666666");  // Set the network port connection
                                       // password.  设置网络端口连接的密码
    ArduinoOTA.begin();            // Initialize the OTA.  初始化OTA
    Serial.println("OTA ready!");  // Serial port output format string.
                                   // 串口输出格式化字符串
}

void loop() {
    ArduinoOTA.handle();  // Continuously check for update requests.
                          // 持续检测是否有更新请求
    M5.update();
    if (M5.Btn.isPressed()) {  // if BtnA is Pressed.  如果按键A按下
        ArduinoOTA.end();      // Ends the ArduinoOTA service.  结束OTA服务
        Serial.println("OTA End!");
        delay(200);
    }
}