/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atom_can
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atom_can
*
* Product:  Can.
* Date: 2021/9/1
*******************************************************************************
  Use ATOM CAN to send and receive information, delete the macro definition
`CAN_SENDER` to compile the receiving part of the program, and enable the macro
definition `CAN_SENDER` to compile the sending part of the program. You need to
use two ATOM CANs for testing 使用ATOM
CAN发送和接收信息，删除宏定义`Can_SENDER`编译程序的接收部分，启用宏定义`Can_SENDER`编译程序的发送部分。
  你需要使用两个Atom Can进行测试。
*/

#include "M5Atom.h"
#include "ESP32CAN.h"
#include "CAN_config.h"

#define CAN_UNIT
#define CAN_SENDER

#define CAN_MSG_ID 0x001

CAN_device_t CAN_cfg;              // CAN Config.  CAN配置。
unsigned long previousMillis = 0;  // will store last time a CAN Message was
                                   // send.  将存储上次发送CAN消息的时间。
const int interval = 80;  // interval at which send CAN Messages (milliseconds).
                          // 发送CAN消息的间隔(毫秒)。
const int rx_queue_size = 10;  // Receive Queue size.  接收队列大小
int LedNumberCount      = 0;
int waitCANData         = 0;

uint8_t msgcnt = 0;

void setup() {
    M5.begin(true, true, true);
    Serial.println("Atom Install OK....");
    M5.dis.fillpix(CRGB(0, 100, 0));

    CAN_cfg.speed = CAN_SPEED_500KBPS;

    // CAN_cfg.tx_pin_id = GPIO_NUM_26;
    // CAN_cfg.rx_pin_id = GPIO_NUM_32;

    CAN_cfg.tx_pin_id = GPIO_NUM_22;
    CAN_cfg.rx_pin_id = GPIO_NUM_19;
    CAN_cfg.rx_queue  = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));

    ESP32Can.CANInit();
    Serial.println("CAN Install");
    M5.dis.fillpix(CRGB(100, 0, 0));
}

void loop() {
    unsigned long currentMillis = millis();

#ifndef CAN_SENDER
    // Send CAN Message
    CAN_frame_t rx_frame;

    if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) ==
        pdTRUE) {
        if (rx_frame.FIR.B.FF == CAN_frame_std) {
            Serial.printf("New standard frame");
        } else {
            Serial.printf("New extended frame");
        }

        if (rx_frame.FIR.B.RTR == CAN_RTR) {
            Serial.printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,
                          rx_frame.FIR.B.DLC);
        } else {
            Serial.printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,
                          rx_frame.FIR.B.DLC);
            for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
                Serial.printf("0x%02X ", rx_frame.data.u8[i]);
            }
            Serial.printf("\n");
            if (rx_frame.data.u8[0] == 0x01) {
                CAN_frame_t tx_frame;
                tx_frame.FIR.B.FF   = CAN_frame_std;
                tx_frame.MsgID      = CAN_MSG_ID;
                tx_frame.FIR.B.DLC  = 8;
                tx_frame.data.u8[0] = 0x02;
                tx_frame.data.u8[1] = rx_frame.data.u8[1];
                tx_frame.data.u8[2] = 0x00;
                tx_frame.data.u8[3] = 0x00;
                tx_frame.data.u8[4] = 0x00;
                tx_frame.data.u8[5] = 0x00;
                tx_frame.data.u8[6] = 0x00;
                tx_frame.data.u8[7] = 0x00;
                ESP32Can.CANWriteFrame(&tx_frame);
            }
        }
    }
#else

    if (currentMillis - previousMillis >= interval) {
        // ESP32Can.CANInit();
        previousMillis = currentMillis;
        CAN_frame_t tx_frame;
        tx_frame.FIR.B.FF   = CAN_frame_std;
        tx_frame.MsgID      = CAN_MSG_ID;
        tx_frame.FIR.B.DLC  = 8;
        tx_frame.data.u8[0] = 0x01;
        tx_frame.data.u8[1] = msgcnt;
        tx_frame.data.u8[2] = 0x00;
        tx_frame.data.u8[3] = 0x00;
        tx_frame.data.u8[4] = 0x00;
        tx_frame.data.u8[5] = 0x00;
        tx_frame.data.u8[6] = 0x00;
        tx_frame.data.u8[7] = 0x00;

        ESP32Can.CANWriteFrame(&tx_frame);
        // ESP32Can.CANStop();
        msgcnt++;
        if (msgcnt > 29) {
            msgcnt = 0;
        }
    }

    CAN_frame_t rx_frame;

    if (xQueueReceive(CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) ==
        pdTRUE) {
        if (rx_frame.FIR.B.FF == CAN_frame_std) {
            Serial.printf("New standard frame");
        } else {
            Serial.printf("New extended frame");
        }

        if (rx_frame.FIR.B.RTR == CAN_RTR) {
            Serial.printf(" RTR from 0x%08X, DLC %d\r\n", rx_frame.MsgID,
                          rx_frame.FIR.B.DLC);
        } else {
            Serial.printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,
                          rx_frame.FIR.B.DLC);
            for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
                Serial.printf("0x%02X ", rx_frame.data.u8[i]);
            }
            Serial.printf("\n");

            if (rx_frame.data.u8[0] == 0x02) {
                if (rx_frame.data.u8[1] < 25) {
                    M5.dis.drawpix(rx_frame.data.u8[1], CRGB(100, 0, 0));
                } else if (rx_frame.data.u8[1] > 27) {
                    M5.dis.fillpix(CRGB(0, 0, 20));
                }
                waitCANData = 0;
            }
        }
    }

#endif
    // waitCANData
    M5.update();
    if (M5.Btn.isPressed()) {
        M5.dis.clear();
        esp_restart();
    }
    delay(10);
}
