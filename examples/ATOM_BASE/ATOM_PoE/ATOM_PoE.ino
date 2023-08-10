/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atom_poe
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atom_poe
*
* Product:  PoE.
* Date: 2023/3/2
*******************************************************************************
  Before compile this example, you have to change line 28 of the ESP32 core's
  Server.h from: "virtual void begin(uint16_t port=0) =0;" To: "virtual void
  begin() =0;" But that will break anything that uses the ESP32 WiFi library's
  WebServer class.
  Reference link:
  https://community.m5stack.com/topic/3068/lan-module-w5500-with-poe-compilation-error
  Use ATOM PoE to connect to the LAN and start the webserver,users can
  使用ATOM PoE连接到局域网并启动Web服务器，用户可以
  connect to the IP address, and control the LEDs through the web page.
  连接到IP地址，并通过网页控制LED。
*/

#include <SPI.h>
#include <M5_Ethernet.h>
#include <FastLED.h>
#include "index.h"

#define SCK  22
#define MISO 23
#define MOSI 33
#define CS   19

#define NUM_LEDS  100
#define DATA_PIN1 27
#define DATA_PIN2 26
CRGB leds[NUM_LEDS];

// Enter a MAC address and IP address for your controller below.
// 在下方输入控制器的 MAC 地址和 IP 地址。 The IP address will be dependent on
// your local network:  IP 地址将取决于您的本地网络：
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library  初始化以太网服务器库
// with the IP address and port you want to use  使用您要使用的 IP 地址和端口
// (port 80 is default for HTTP):  （HTTP 的默认端口为 80）：
EthernetServer server(80);

void setup() {
    FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds,
                                         NUM_LEDS);  // RGB ordering is assumed
    FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds,
                                         NUM_LEDS);  // RGB ordering is assumed

    SPI.begin(SCK, MISO, MOSI, -1);
    Ethernet.init(CS);

    // Open serial communications and wait for port to open:.
    // 打开串口通信，等待端口打开：
    Serial.begin(115200);
    while (!Serial) {
        ;  // wait for serial port to connect. Needed for native USB port only.
           // 等待串口连接。 仅本地 USB 端口需要
    }
    Serial.println("Ethernet WebServer Example");

    // start the Ethernet connection and the server:.  启动以太网连接和服务器：
    Ethernet.begin(mac, ip);
    // start the server.  启动服务器
    server.begin();
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
}

void loop() {
    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
        Serial.println("new client");
        // an http request ends with a blank line
        while (client.connected()) {
            if (client.available()) {
                String c = client.readString();
                Serial.println(c);
                // if you've gotten to the end of the line (received a newline
                // 如果你已经到了行尾（收到换行符 character) and the line is
                // blank, the http request has ended,  字符）且该行为空，则 http
                // 请求已结束， so you can send a reply  所以你可以发送回复
                if (c.indexOf("color?=") != -1) {
                    c = c.substring(c.indexOf("color?=") + 7,
                                    c.indexOf(" HTTP/1.1"));
                    Serial.println(c);
                    client.println("HTTP/1.1 200 OK");
                    fill_solid(leds, NUM_LEDS, CRGB(c.toInt()));
                    FastLED.show();
                } else {
                    // send a standard http response header  发送标准的 http
                    // 响应头
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: text/html");
                    client.println(
                        "Connection: close");  // the connection will be closed
                                               // after completion of the
                                               // response. 响应完成后连接将关闭
                    client.println();
                    client.println(MAIN_page);
                }
                break;
            }
        }
        // give the web browser time to receive the data.
        // 给网络浏览器时间来接收数据
        delay(1);
        // close the connection:.  关闭连接：
        client.stop();
        Serial.println("client disconnected");
    }
}
