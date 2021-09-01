/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* describe: Ameter_ADS1115.  电流计
* date：2021/8/19
*******************************************************************************
  Please connect to Port ,Measure current and display.
  请连接端口,测量电流并显示到串口上
  Pay attention: EEPROM (0x51) has built-in calibration parameters when leaving the factory.
  Please do not write to the EEPROM, otherwise the calibration data will be overwritten and the measurement results will be inaccurate.
  注意: EEPROM (0x51)在出厂时具有内置的校准参数。请不要写入EEPROM，否则校准数据会被覆盖，测量结果会不准确。
*/

#include <M5Atom.h>
#include "M5_ADS1115.h"

Ammeter ammeter;

float page512_volt = 2000.0F;

int16_t volt_raw_list[10];
uint8_t raw_now_ptr = 0;
int16_t adc_raw = 0;

int16_t hope = 0.0;

ammeterGain_t now_gain = PAG_512;

void setup(void) {
  M5.begin(); //Init M5Atom.  初始化M5Atom
  Wire.begin();

  ammeter.setMode(SINGLESHOT);
  ammeter.setRate(RATE_8);
  ammeter.setGain(PAG_512);
  hope = page512_volt / ammeter.resolution;
  // | PAG      | Max Input Voltage(V) |
  // | PAG_6144 |        128           |
  // | PAG_4096 |        64            |
  // | PAG_2048 |        32            |
  // | PAG_512  |        16            |
  // | PAG_256  |        8             |

  Serial.printf("2A");

}

void loop(void) {
  M5.update();  //Check the status of the key.  检测按键的状态
  if (M5.Btn.wasPressed()) {
    ammeter.setMode(SINGLESHOT);  //Set the mode.  设置模式
    ammeter.setRate(RATE_8);  //Set the rate.  设置速率
    ammeter.setGain(PAG_512);
    now_gain = PAG_512;
    hope = page512_volt / ammeter.resolution;

    for (uint8_t i = 0; i < 10; i++) {
      volt_raw_list[i] = 0;
    }
  }

  float current = ammeter.getCurrent();

  volt_raw_list[raw_now_ptr] = ammeter.adc_raw;
  raw_now_ptr = (raw_now_ptr == 9) ? 0 : (raw_now_ptr + 1);

  int count = 0;
  int total = 0;

  for (uint8_t i = 0; i < 10; i++) {
    if (volt_raw_list[i] == 0) {
      continue ;
    }
    total += volt_raw_list[i];
    count += 1;
  }

  if (count == 0) {
    adc_raw = 0;
  } else {
    adc_raw = total / count;
  }

  Serial.printf("Hope volt:%.2f mAn\n",page512_volt);

  Serial.printf("Cal volt:%.2f mA\n",current);

  Serial.printf("Cal ADC:%.0f\n",adc_raw * ammeter.calibration_factor);

  Serial.printf("RAW ADC:%d\n\n", adc_raw);
}