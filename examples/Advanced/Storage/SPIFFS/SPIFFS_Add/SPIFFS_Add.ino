/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit for more information: https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* Describe: SPIFFS Add(Write is to clean up the contents of the file and write
*it again.). 向SPIFFS中添加信息(write是将文件内容完全清除重新写) Date: 2021/8/4
******************************************************************************
*/

#include <M5Atom.h>
#include <SPIFFS.h>

String file_name =
    "/M5Stack/notes.txt";  // Sets the location and name of the file to be
                           // operated on.  设置被操作的文件位置和名称
bool SPIFFS_FORMAT =
    true;  // Whether to initialize the SPIFFS.  是否初始化SPIFFS
// You don't need to format the flash file system every time you use it.
//无需每次使用闪存都进行格式化

void setup() {
    M5.begin();  // Init M5Atom.  初始化 M5ATOM
    if (SPIFFS_FORMAT) {
        Serial.println(
            "\nSPIFFS format start...");  // Serial port output format String.
                                          // 串口输出格式化字符串
        SPIFFS.format();                  // Formatting SPIFFS.  格式化SPIFFS
        Serial.println("SPIFFS format finish");
    }
    if (SPIFFS.begin()) {  // Start SPIFFS, return 1 on success.
                           // 启动闪存文件系统,若成功返回1
        Serial.println("\nSPIFFS Started.");
    } else {
        Serial.println("SPIFFS Failed to Start.");
    }

    if (SPIFFS.exists(
            file_name)) {  // Check whether the file_name file exists in the
                           // flash memory.  确认闪存中是否有file_name文件
        Serial.println("FOUND.");
        Serial.println(file_name);

        File dataFile = SPIFFS.open(
            file_name,
            "a");  // Create a File object dafaFile to add information to
                   // file_name in the SPIFFS.
                   // 建立File对象dafaFile用于向SPIFFS中的file_name添加信息
        dataFile.println(
            "This is Appended Info.");  // Adds string information to dataFile.
                                        // 向dataFile添加字符串信息
        dataFile.close();  // Close the file when writing is complete.
                           // 完成写入后关闭文件
        Serial.println("Finished Appending data to SPIFFS");
    } else {
        Serial.println("NOT FOUND.");
        Serial.print(file_name);
        Serial.println("is creating.");
        File dataFile = SPIFFS.open(
            file_name,
            "w");  // Create aFile object dafaFile to write information to
                   // file_name in the SPIFFS.
                   // 建立File对象dafaFile用于向SPIFFS中的file_name写入信息
        dataFile.close();  // Close the file when writing is complete.
                           // 完成写入后关闭文件
        Serial.println("Please disable format and Reupload");
    }
}

void loop() {
}