/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* describe：EzData.
* Date: 2021/10/23
*******************************************************************************
*/

#include "M5Atom.h"
#include "M5_EzData.h"

// Configure the name and password of the connected wifi and your token.
// 配置所连接wifi的名称、密码以及你的token
const char* ssid     = "Explore-F";
const char* password = "xingchentansuo123";
const char* token    = "";

void setup() {
    M5.begin();                       // Initialize M5Stack
    if (setupWifi(ssid, password)) {  // Connect to wifi.  连接到wifi
        Serial.printf("Success connecting to %s\n", ssid);
    } else {
        Serial.printf("Connecting to %s failed\n", ssid);
    }
}

void loop() {
    // Save the data 20 to the top of the testData topic queue.  保存数据20至
    // testData 队列首位
    setData(token, "testData", 20);
    delay(5000);

    // Save 3 data in sequence to the first place of testList. 依次保存3个数据至
    // testList首位
    for (int i = 0; i < 3; i++) {
        addToList(token, "testList", i);
        delay(100);
    }
    delay(5000);

    // Get a piece of data from a topic and store the value in result.  从一个
    // topic中获取一个数据,并将值存储在 result
    int result = 0;
    if (getData(token, "testData", result))
        ;
    delay(5000);

    // Get a set of data from a list and store the values in the Array array.
    // 从一个 list中获取一组数据,并将值存储在 Array数组中
    int Array[3] = {};
    if (getData(token, "testList", Array, 0, 3)) {
        Serial.print("Success get list\n");
        for (int i = 0; i < 3; i++) {
            Serial.printf("Array[%d]=%d,", i, Array[i]);
        }
        Serial.println("");
    } else {
        Serial.println("Fail to get data");
    }
    delay(5000);

    // Remove data
    removeData(token, "testData");
    removeData(token, "testList");
    delay(5000);
}