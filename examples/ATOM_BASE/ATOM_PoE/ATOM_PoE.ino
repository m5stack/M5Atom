/*
    Description: 
    Use ATOM PoE to connect to the LAN and start the webserver, 
    users can connect to the IP address, and control the LEDs through the web page.
    Please install library before compiling:  
    FastLED: https://github.com/FastLED/FastLED
    Ethernet2: https://github.com/adafruit/Ethernet2
*/

#include <SPI.h>
#include <Ethernet2.h>
#include <FastLED.h>
#include "index.h"

#define SCK 22
#define MISO 23
#define MOSI 33
#define CS 19

#define NUM_LEDS 100
#define DATA_PIN1 27
#define DATA_PIN2 26
CRGB leds[NUM_LEDS];

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN1>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.addLeds<NEOPIXEL, DATA_PIN2>(leds, NUM_LEDS);  // GRB ordering is assumed

  SPI.begin(SCK, MISO, MOSI, -1);
  Ethernet.init(CS);

  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void handler() {

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
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if(c.indexOf("color?=") != -1) {
          c = c.substring(c.indexOf("color?=")+7,c.indexOf(" HTTP/1.1"));
          Serial.println(c);
          client.println("HTTP/1.1 200 OK");
          fill_solid(leds, NUM_LEDS, CRGB(c.toInt()));
          FastLED.show();
        }else{
                      // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println(MAIN_page);
        }
        break; 
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

