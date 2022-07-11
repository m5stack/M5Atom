/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: WIFI TCP.
* Date: 2021/7/29
*******************************************************************************
  M5Atom will sends a message to a TCP server
  M5Atom 将向TCP服务器发送一条数据
*/

#include <M5Atom.h>
#include <WiFi.h>
#include <WiFiMulti.h>

// Set the name and password of the wifi to be connected.
// 配置所连接wifi的名称和密码
const char *ssid     = "cam";
const char *password = "12345678";
WiFiMulti WiFiMulti;

void setup() {
    M5.begin(true, false, true);  // Init Atom(Initialize serial port, LED).
                                  // 初始化 ATOM(初始化串口、LED)
    WiFiMulti.addAP(
        ssid,
        password);  // Add wifi configuration information.  添加wifi配置信息
    Serial.print(
        "\nWaiting connect to WiFi...");  // Serial port output format string.
                                          // 串口输出格式化字符串
    M5.dis.fillpix(0xff0000);  // Make the LED light show red.  使led灯显示红色
    while (WiFiMulti.run() !=
           WL_CONNECTED) {  // If the connection to wifi is not established
                            // successfully.  如果没有与wifi成功建立连接
        Serial.print(".");
        delay(300);
    }
    M5.dis.fillpix(0x00ff00);  // Make the LED light green.  使led灯显示绿色
    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  // The serial port outputs the IP address
                                     // of the M5Atom.  串口输出M5Atom的IP地址
    delay(500);
}

void loop() {
    const char *host = "www.baidu.com";  // Set the IP address or DNS of the TCP
                                         // server.  设置TCP服务器的ip或dns
    const uint16_t port =
        80;  // The port of the TCP server is specified.  设置TCP服务器的端口
    Serial.print("Connecting to: ");
    Serial.println(host);

    WiFiClient client;
    if (!client.connect(
            host,
            port)) {  // Connect to the server. 0 is returned if the
                      // connection fails. 连接服务器,若连接失败返回0
        Serial.println("Connection failed.");
        Serial.println("Waiting 5 seconds before retrying...");
        delay(5000);
        return;
    }

    // send an arbitrary string to the server.  发送一个字符串到上边连接的服务器
    client.print("Send this data to the server");
    // send a basic document request to the server.
    // 向服务器发送一个基本的文档请求.
    client.print("GET /index.html HTTP/1.1\n\n");
    int maxloops = 0;

    // wait for the server's reply to become available
    //等待服务器的回复
    while (!client.available() && maxloops < 1000) {
        maxloops++;
        delay(1);  // delay 1 msec
    }
    if (client.available() >
        0) {  // Detects whether data is received.  检测是否接收到数据
        String line = client.readStringUntil(
            '\r');  // Read information from data received by the device until
                    // \r is read.  从设备接收到的数据中读取信息,直至读取到\r时
        Serial.println(line);  // String received by serial port output.
                               // 串口输出接收到的字符串
    } else {
        Serial.println("client.available() timed out ");
    }
    Serial.println("Closing connection.");
    client.stop();
    Serial.println("Waiting 5 seconds before restarting...");
    delay(5000);
}
