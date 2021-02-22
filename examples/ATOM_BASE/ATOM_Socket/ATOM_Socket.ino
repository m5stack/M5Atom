/*
    Description: 
    Use ATOM Socket to monitor the socket power, press the middle button of ATOM to switch the socket power on and off.
    Connect to the AP hotspot of the device and access 192.168.4.1 to wirelessly control the socket power and view the power voltage, current and power information.
*/

#include "M5Atom.h"
#include "AtomSocket.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include "index.h"

const char* ssid = "ATOM-SOCKET";
const char* password = "12345678";

int Voltage, ActivePower = 0;
float Current = 0;

WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", html);
}

#define RXD 22
#define RELAY 23

ATOMSOCKET ATOM;

HardwareSerial AtomSerial(2);

bool RelayFlag = false;

String DataCreate() {
    String RelayState = (RelayFlag)?"on":"off";
    String Data = "vol:<mark>"+String(Voltage)+"</mark>V#current:<mark>"+String(Current)+"</mark>A#power:<mark>"+String(ActivePower)+"</mark>W#state:<mark>"+RelayState+"</mark>";
    return Data;
}

void setup(){
    M5.begin(true, false, true);
    M5.dis.drawpix(0, 0xe0ffff);
    ATOM.Init(AtomSerial, RELAY, RXD);
    WiFi.softAP(ssid, password);
    Serial.print("AP SSID: ");
    Serial.println(ssid);
    Serial.print("AP PASSWORD: ");
    Serial.println(password);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());  //IP address assigned to your ESP
    server.on("/", handleRoot);

    server.on("/on", []() {
        RelayFlag = true;
        server.send(200, "text/plain", DataCreate());
    });

    server.on("/off", []() {
        RelayFlag = false;
        server.send(200, "text/plain", DataCreate());
    });

    server.on("/data", []() {
        server.send(200, "text/plain", DataCreate());
    });

    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    ATOM.SerialReadLoop();
	if(ATOM.SerialRead == 1)   
	{
        Voltage = ATOM.GetVol();
        Current = ATOM.GetCurrent();
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
    if(M5.Btn.wasPressed()){
        RelayFlag = !RelayFlag;
    }
    if(RelayFlag) {
        M5.dis.drawpix(0, 0xff0000);
        ATOM.SetPowerOn();
    }else{
        ATOM.SetPowerOff();
        M5.dis.drawpix(0, 0xe0ffff);
    }
    M5.update();
    server.handleClient();
}
