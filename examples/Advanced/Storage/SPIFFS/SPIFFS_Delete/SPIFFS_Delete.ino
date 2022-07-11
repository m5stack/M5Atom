/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: SPIFFS Delete
* Date: 2021/8/4
******************************************************************************
*/

#include <M5Atom.h>
#include <SPIFFS.h>

String file_name =
    "/M5Stack/notes.txt";  // Sets the location and name of the file to be
                           // operated on.  设置被操作的文件位置和名称
void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5ATOM

    if (SPIFFS.begin()) {  // Start SPIFFS, return 1 on success.
                           // 启动闪存文件系统,若成功返回1
        Serial.println("\nSPIFFS Started.");  // Serial port output format
                                              // String.  串口输出格式化字符串
    } else {
        Serial.println("SPIFFS Failed to Start.");
    }

    if (SPIFFS.remove(
            file_name)) {  // Delete file_name file from flash, return 1 on
                           // success.  从闪存中删除file_name文件,如果成功返回1
        Serial.print(file_name);
        Serial.println(" Remove sucess");
    } else {
        Serial.print(file_name);
        Serial.println(" Remove fail");
    }
}

void loop() {
}