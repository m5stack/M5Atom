#ifndef _LED_DISPLAY_H_
#define _LED_DISPLAY_H_

#include <FastLED.h>
#include "utility/Task.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define NUM_LEDS 25
#define DATA_PIN 27

class LED_DisPlay : public Task
{
private:
    CRGB _ledbuff[NUM_LEDS];
    uint8_t _numberled;

    uint8_t _mode;
    uint16_t _am_speed;
    uint8_t _am_mode;
    int32_t _count_x, _count_y;
    int32_t _am_count = -1;
    uint8_t *_am_buffptr;

    SemaphoreHandle_t _xSemaphore = NULL;

public:
    enum
    {
        kStatic = 0,
        kAnmiation_run,
        kAnmiation_stop,
        kAnmiation_frush,
    } Dismode;
    enum
    {
        kMoveRight = 0x01,
        kMoveLeft = 0x02,
        kMoveTop = 0x04,
        kMoveButtom = 0x08,
    } Am_mode;

    uint8_t Brightness = 40;

    /* data */
public:
    LED_DisPlay();
    ~LED_DisPlay();

    void begin(uint8_t LEDNumbre = NUM_LEDS);
    void run(void *data);

    void animation(uint8_t *buffptr, uint8_t amspeed, uint8_t ammode, int64_t amcount = -1);
    void displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0);
    void MoveDisPlayBuff(int8_t offsetx = 0, int8_t offsety = 0);

    void setBrightness(uint8_t brightness);
    void drawpix(uint8_t xpos, uint8_t ypos, CRGB Color);
    void drawpix(uint8_t Number, CRGB Color);
    void fillpix(CRGB Color);
    void clear();

private:
    void _displaybuff(uint8_t *buffptr, int8_t offsetx = 0, int8_t offsety = 0);
};

#endif
