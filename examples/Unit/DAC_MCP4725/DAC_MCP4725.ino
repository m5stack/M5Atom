/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Product: DAC_MCP4725.  数模转换
* Date: 2021/8/16
*******************************************************************************
  Please connect to Port ,Use DAC Unit to output 0 ~ 3.3V voltage with an
accuracy of 12 bits. 请连接端口,使用DAC Unit 输出12位精度的0 ~ 3.3V电压。
*/

#include <M5Atom.h>
#include <Adafruit_MCP4725.h>

#define DAC_ADDR \
    0x60  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR
          // pin tied to VCC) For MCP4725A0 the address is 0x60 or 0x61 For
          // MCP4725A2 the address is 0x64 or 0x65

Adafruit_MCP4725 dac;

void setup(void) {
    M5.begin(true, false, true);  // Init M5Atom(Init serial and display).
                                  // 初始化 M5Atom(初始化串口和串口)
    Serial.print("\nDAC MCP4725 demo.");

    dac.begin(0x60);  // Setups the hardware address and checks the DAC was
                      // found.  设置硬件地址并检查是否找到DAC
    dac.setVoltage(2048, false);
    M5.dis.fillpix(0x00FFFF);
}

void loop(void) {
    Serial.println("Voltage:1.2V");
    dac.setVoltage(1024,
                   false);  // Set the voltage to 1.2V and retain the current
                            // voltage output after power off or reset.
                            // 设置电压为1.2v,关闭断电或复位后保留当前电压输出
    delay(1000);
    Serial.println("Voltage:2.4V");
    dac.setVoltage(2048, false);  // 2.4v
    delay(1000);
}