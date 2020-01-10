#include "M5Atom.h"

float accX = 0, accY = 0, accZ = 0;
float gyroX = 0, gyroY = 0, gyroZ = 0;
float temp = 0;
bool IMU6886Flag = false;

void setup()
{
    M5.begin(true, false, true);

    if (M5.IMU.Init() != 0)
        IMU6886Flag = false;
    else
        IMU6886Flag = true;
}

void loop()
{

    if (IMU6886Flag == true)
    {
        M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
        M5.IMU.getAccelData(&accX, &accY, &accZ);
        M5.IMU.getTempData(&temp);

        Serial.printf("%.2f,%.2f,%.2f o/s \r\n", gyroX, gyroY, gyroZ);
        Serial.printf("%.2f,%.2f,%.2f mg\r\n", accX * 1000, accY * 1000, accZ * 1000);
        Serial.printf("Temperature : %.2f C \r\n", temp);
    }
    delay(500);
    M5.update();
}