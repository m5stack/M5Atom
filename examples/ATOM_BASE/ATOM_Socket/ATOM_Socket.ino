/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atom_socket
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atom_socket
*
* Product:  Socket.
* Date: 2021/9/1
*******************************************************************************
  Use ATOM Socket to monitor the socket power, press the middle button of ATOM
to switch the socket power on and off. Connect to the AP hotspot of the device
and access 192.168.4.1 to wirelessly control the socket power and view the power
voltage, current and power information.
  使用ATOM插座监控插座电源，按ATOM的中间按钮即可打开和关闭插座电源。
  连接到设备的AP热点，接入192.168.4.1，无线控制插座电源，查看电源电压、电流和电源信息。
*/

#include "M5Atom.h"
#include "AtomSocket.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "index.h"

const char* ssid     = "ATOM-SOCKET";
const char* password = "12345678";

int Voltage, ActivePower = 0;
float Current = 0;

WebServer server(80);

void handleRoot() {
    server.send(200, "text/html", html);
}

#define RXD   22
#define RELAY 23

ATOMSOCKET ATOM;

HardwareSerial AtomSerial(2);

bool RelayFlag = false;

String DataCreate() {
    String RelayState = (RelayFlag) ? "on" : "off";
    String Data = "vol:<mark>" + String(Voltage) + "</mark>V#current:<mark>" +
                  String(Current) + "</mark>A#power:<mark>" +
                  String(ActivePower) + "</mark>W#state:<mark>" + RelayState +
                  "</mark>";
    return Data;
}

void setup() {
    M5.begin(true, false, true);
    M5.dis.drawpix(0, 0xfff000);
    ATOM.Init(AtomSerial, RELAY, RXD);
    WiFi.softAP(ssid, password);
    Serial.print("AP SSID: ");
    Serial.println(ssid);
    Serial.print("AP PASSWORD: ");
    Serial.println(password);
    Serial.print("IP address: ");
    Serial.println(
        WiFi.softAPIP());  // IP address assigned to your ESP  获取ip地址
    server.on("/", handleRoot);

    server.on("/on", []() {
        RelayFlag = true;
        server.send(200, "text/plain", DataCreate());
    });

    server.on("/off", []() {
        RelayFlag = false;
        server.send(200, "text/plain", DataCreate());
    });

    server.on("/data", []() { server.send(200, "text/plain", DataCreate()); });

    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    ATOM.SerialReadLoop();
    if (ATOM.SerialRead == 1) {
        Voltage     = ATOM.GetVol();
        Current     = ATOM.GetCurrent();
        ActivePower = ATOM.GetActivePower();
        Serial.print("Voltage: ");
        Serial.print(Voltage);
        Serial.println(" V");
        Serial.print("Current: ");
        Serial.print(Current);
        Serial.println(" A");
        Serial.print("ActivePower: ");
        Serial.print(ActivePower);
        Serial.println(" W");
    }
    if (M5.Btn.wasPressed()) {
        RelayFlag = !RelayFlag;
    }
    if (RelayFlag) {
        M5.dis.drawpix(0, 0xff0000);
        ATOM.SetPowerOn();
    } else {
        ATOM.SetPowerOff();
        M5.dis.drawpix(0, 0xfff000);
    }
    M5.update();
    server.handleClient();
}
