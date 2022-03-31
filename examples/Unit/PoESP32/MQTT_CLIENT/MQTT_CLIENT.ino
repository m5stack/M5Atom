/*
    Description:
    Use UNIT PoESP32 to connect to the MQTT server, and implement subscription
    and publishing messages. Check the status through Serial. 
    before compiling: 
    FastLED: https://github.com/FastLED/FastLED
    M5Atom: https://github.com/m5stack/M5Atom
    UNIT_PoESP32: https://github.com/m5stack/UNIT_PoESP32
*/

#include "M5Atom.h"
#include "UNIT_PoESP32.h"

UNIT_PoESP32 eth;

typedef enum { kConfig = 0, kStart, kConnecting, kConnected } DTUState_t;

DTUState_t State = kStart;

void TaskLED(void *pvParameters) {
    while (1) {
        switch (State) {
            case kConfig:
                M5.dis.fillpix(0x0000ff);
                break;
            case kConnecting:
                M5.dis.fillpix(0xffff00);
                break;
            case kConnected:
                M5.dis.fillpix(0x00ff00);
                break;
            case kStart:
                M5.dis.fillpix(0xff0000);
                break;
        }
        for (int i = 100; i > 0; i--) {
            M5.dis.setBrightness(i);
            FastLED.show();
            vTaskDelay(10 / portTICK_RATE_MS);
        }
        for (int i = 0; i < 100; i++) {
            M5.dis.setBrightness(i);
            FastLED.show();
            vTaskDelay(10 / portTICK_RATE_MS);
        }
    }
}

String readstr;

void setup() {
    M5.begin(true, false, true);
    eth.Init(&Serial2, 9600, 32, 26);

    xTaskCreatePinnedToCore(TaskLED, "TaskLED"  // A name just for humans
                            ,
                            4096  // This stack size can be checked & adjusted
                                  // by reading the Stack Highwater
                            ,
                            NULL,
                            1  // Priority, with 3 (configMAX_PRIORITIES - 1)
                               // being the highest, and 0 being the lowest.
                            ,
                            NULL, 0);
    delay(10);

    State = kStart;

    Serial.println("wait device connect");
    while (!eth.checkDeviceConnect()) {
        delay(10);
    }

    Serial.println("device connected");

    State = kConnecting;

    Serial.println("wait ethernet connect");
    while (!eth.checkETHConnect()) {
        delay(10);
    }
    Serial.println("ethernet connected");

    State = kConfig;

    Serial.println("wait mqtt connect");
    while (!eth.createMQTTClient("120.77.157.90", "1883", "client_id",
                                 "user_name", "password")) {
        delay(10);
    }
    Serial.println("mqtt connected");

    while (!eth.subscribeMQTTMsg("PoESP32_MQTT_D", "2")) {
        delay(10);
    }
}

void loop() {
    if (Serial.available()) {
        char ch = Serial.read();
        Serial2.write(ch);
    }
    if (Serial2.available()) {
        char ch = Serial2.read();
        Serial.write(ch);
    }
    eth.publicMQTTMsg("PoESP32_MQTT_U", "Hello From PoESP32", "2");
    delay(1000);
}
