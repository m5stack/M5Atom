

/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/atom/atomic_qr
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/atom/atomic_qr
*
* Product:  ATOM QR-CODE UART control.
* Date: 2021/8/30
*******************************************************************************
Press the button to scan, and the scan result will be printed out through
Serial. More Info pls refer: [QR module serial control command
list](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/atombase/AtomicQR/ATOM_QRCODE_CMD_EN.pdf)

*/

#include <M5Atom.h>

uint8_t wakeup_cmd       = 0x00;
uint8_t start_scan_cmd[] = {0x04, 0xE4, 0x04, 0x00, 0xFF, 0x14};
uint8_t stop_scan_cmd[]  = {0x04, 0xE5, 0x04, 0x00, 0xFF, 0x13};
uint8_t host_mode_cmd[]  = {0x07, 0xC6, 0x04, 0x08, 0x00,
                            0x8A, 0x08, 0xFE, 0x95};

uint8_t ack_cmd[] = {0x04, 0xD0, 0x00, 0x00, 0xFF, 0x2C};

#define TRIG 23

void setup() {
    M5.begin(true, false, true);
    Serial2.begin(
        9600, SERIAL_8N1, 22,
        19);  // Set the baud rate of serial port 2 to 115200,8 data bits, no
              // parity bits, and 1 stop bit, and set RX to 22 and TX to 19.
              // 设置串口二的波特率为115200,8位数据位,没有校验位,1位停止位,并设置RX为22,TX为19
    M5.dis.fillpix(0xfff000);  // YELLOW 黄色
    delay(1000);
    Serial2.write(wakeup_cmd);
    delay(50);
    Serial2.write(host_mode_cmd, sizeof(host_mode_cmd));
}

void loop() {
    M5.update();
    if (M5.Btn.isPressed()) {
        M5.dis.fillpix(0x0000ff);
        Serial2.write(wakeup_cmd);
        delay(50);
        Serial2.write(start_scan_cmd, sizeof(start_scan_cmd));
    }
    if (Serial.available()) {
        Serial2.write(wakeup_cmd);
        delay(50);
        while (Serial.available()) {
            Serial2.write(Serial.read());
        }
    }

    if (Serial2.available()) {
        int ch = Serial2.read();
        Serial.write(ch);
    }
}
