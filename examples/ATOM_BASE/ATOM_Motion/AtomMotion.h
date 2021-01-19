#include <M5Atom.h>

#define SERVO_ADDRESS	0X38


class AtomMotion
{
private:
    void Write1Byte(uint8_t address,uint8_t Register_address,uint8_t data);
    void Write2Byte(uint8_t address,uint8_t Register_address,uint16_t data);
    uint8_t ReadBytes(uint8_t address, uint8_t subAddress, uint8_t count,uint8_t * dest);
public:

    void Init(); //sda  25     scl  21 		

    uint8_t SetServoAngle(uint8_t Servo_CH, uint8_t angle);

    uint8_t SetServoPulse(uint8_t Servo_CH, uint16_t width);

    uint8_t SetMotorSpeed(uint8_t Motor_CH, int8_t speed);

    uint8_t ReadServoAngle(uint8_t Servo_CH);

    uint16_t ReadServoPulse(uint8_t Servo_CH);

    int8_t ReadMotorSpeed(uint8_t Motor_CH);

};

