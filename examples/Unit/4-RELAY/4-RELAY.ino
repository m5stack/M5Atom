/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: 4-Relay.  4个继电器
* Date: 2021/8/10
*******************************************************************************
  Please connect to port ,Control 4 relays and demonstrate the asynchronous
control relay LED 请连接端口，控制4继电器，并演示异步控制继电器LED
-------------------------------------------------------------------------------
  RELAY control reg           | 0x10
  -----------------------------------------------------------------------------
  Relay_ctrl_mode_reg[0]      | R/W | System control
                              | 7 | 6 | 5 | 4 | 3 | 2 | 1 |     0     |
                              | R | R | R | R | R | R | R | Sync Mode |
                              | -Sync Mode:0 LED&Relay Async
                              | -Sync Mode:1 LED&Relay Sync
  ---------------------------------------------------------------------------------
  Relay_ctrl_mode_reg[1]      | R/W | Relay & LED control
                              |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
                              | LED1| LED2| LED3| LED4| RLY1| RLY2| RLY3| RLY4|
-------------------------------------------------------------------------------*/

#include <M5Atom.h>
#include "UNIT_4RELAY.h"
UNIT_4RELAY unit_4relay;

void setup() {
    M5.begin();           // Init M5Atom.  初始化 M5Atom
    Wire.begin(26, 32);   // Initialize pin 26, 32.  初始化26,32引脚
    unit_4relay.Init(0);  // Set the lamp and relay to asynchronous mode(Async =
                          // 0,Sync = 1).  将灯和继电器设为非同步模式
    Serial.printf("Please pressed Btn. \n");
}

char count_i   = 0;
bool sync_flag = 0, all_flag = 0;

void loop() {
    M5.update();  // Check button down state.  检测按键按下状态
    if (M5.Btn.wasPressed()) {  // If button A is pressed.  如果按键A按下
        count_i++;
        if (count_i < 5) {
            Serial.printf("%d ON\n", count_i);
            unit_4relay.relayWrite(
                count_i - 1,
                1);  // Open the relay at Count_i.  打开count_i处的继电器
            unit_4relay.relayWrite(count_i - 2,
                                   0);  // Close the relay that was last opened.
                                        // 关闭上一次打开的继电器
            unit_4relay.LEDWrite(count_i - 1, 1);
            unit_4relay.LEDWrite(count_i - 2, 0);
        } else if (count_i == 5) {
            Serial.printf("ALL.ON \n");
            unit_4relay.relayALL(1);  // Open all the relays.  打开所有的继电器
            unit_4relay.LED_ALL(1);  // Turn on all leds.  打开所有的LED
        } else {
            count_i = 0;
            Serial.printf("ALL.OFF \n");
            unit_4relay.relayALL(0);
            unit_4relay.LED_ALL(0);
        }
    }
}