#include "LED_DisPlay.h"

LED_DisPlay::LED_DisPlay() {
}

LED_DisPlay::~LED_DisPlay() {
}

void LED_DisPlay::begin(uint8_t LEDNumber) {
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(_ledbuff, LEDNumber);
    _xSemaphore = xSemaphoreCreateMutex();
    _numberled  = LEDNumber;
}

void LED_DisPlay::run(void *data) {
    for (int num = 0; num < NUM_LEDS; num++) {
        _ledbuff[num] = 0x000000;
    }
    FastLED.show();
    FastLED.setBrightness(20);

    while (1) {
        xSemaphoreTake(_xSemaphore, portMAX_DELAY);
        if (_mode == kAnimation_run) {
            _displaybuff(_am_buffptr, _count_x, _count_y);
            FastLED.show();
            if ((_am_mode & kMoveRight) || (_am_mode & kMoveLeft)) {
                if (_am_mode & kMoveRight) {
                    _count_x++;
                } else {
                    _count_x--;
                }
            }
            if ((_am_mode & kMoveTop) || (_am_mode & kMoveBottom)) {
                if (_am_mode & kMoveTop) {
                    _count_y--;
                } else {
                    _count_y++;
                }
            }
            if ((_am_count != -1) && (_am_count != 0)) {
                _am_count--;
                if (_am_count == 0) {
                    _mode = kAnimation_stop;
                }
            }
            delay(_am_speed);
        } else if (_mode == kAnimation_frush) {
            _mode = kAnimation_stop;
            FastLED.show();
            FastLED.setBrightness(20);
        }
        xSemaphoreGive(_xSemaphore);
        delay(10);
    }
}

void LED_DisPlay::_displaybuff(uint8_t *buffptr, int32_t offsetx,
                               int32_t offsety) {
    uint16_t xsize = 0, ysize = 0;
    xsize = _xColumns;
    ysize = _yRows;

    offsetx = offsetx % xsize;
    offsety = offsety % ysize;

    int16_t setdatax = (offsetx < 0) ? (-offsetx) : (xsize - offsetx);
    int16_t setdatay = (offsety < 0) ? (-offsety) : (ysize - offsety);
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            _ledbuff[x + y * 5].raw[1] =
                buffptr[2 +
                        ((setdatax + x) % xsize +
                         ((setdatay + y) % ysize) * xsize) *
                            3 +
                        0];
            _ledbuff[x + y * 5].raw[0] =
                buffptr[2 +
                        ((setdatax + x) % xsize +
                         ((setdatay + y) % ysize) * xsize) *
                            3 +
                        1];
            _ledbuff[x + y * 5].raw[2] =
                buffptr[2 +
                        ((setdatax + x) % xsize +
                         ((setdatay + y) % ysize) * xsize) *
                            3 +
                        2];
        }
    }
    FastLED.setBrightness(Brightness);
}

void LED_DisPlay::animation(uint8_t *buffptr, uint8_t amspeed, uint8_t ammode,
                            int64_t amcount) {
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);
    if (_mode == kAnimation_run) {
        _mode = kAnimation_stop;
    }
    _am_buffptr = buffptr;
    _am_speed   = amspeed;
    _am_mode    = ammode;
    _am_count   = amcount;
    _count_x = _count_y = 0;
    _mode               = kAnimation_run;
    xSemaphoreGive(_xSemaphore);
}

void LED_DisPlay::displaybuff(uint8_t *buffptr, int32_t offsetx,
                              int32_t offsety) {
    uint16_t xsize = 0, ysize = 0;
    xsize = _xColumns;
    ysize = _yRows;

    offsetx = offsetx % xsize;
    offsety = offsety % ysize;

    int16_t setdatax = (offsetx < 0) ? (-offsetx) : (xsize - offsetx);
    int16_t setdatay = (offsety < 0) ? (-offsety) : (ysize - offsety);
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);

    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            _ledbuff[x + y * 5].raw[1] =
                buffptr[2 +
                        ((setdatax + x) % xsize +
                         ((setdatay + y) % ysize) * xsize) *
                            3 +
                        0];
            _ledbuff[x + y * 5].raw[0] =
                buffptr[2 +
                        ((setdatax + x) % xsize +
                         ((setdatay + y) % ysize) * xsize) *
                            3 +
                        1];
            _ledbuff[x + y * 5].raw[2] =
                buffptr[2 +
                        ((setdatax + x) % xsize +
                         ((setdatay + y) % ysize) * xsize) *
                            3 +
                        2];
        }
    }

    _mode = kAnimation_frush;

    xSemaphoreGive(_xSemaphore);
    FastLED.setBrightness(Brightness);
}

void LED_DisPlay::setBrightness(uint8_t brightness) {
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);
    brightness = (brightness > 100) ? 100 : brightness;
    brightness = (40 * brightness / 100);
    Brightness = brightness;
    FastLED.setBrightness(Brightness);
    xSemaphoreGive(_xSemaphore);
}

void LED_DisPlay::drawpix(uint8_t xpos, uint8_t ypos, CRGB Color) {
    if ((xpos >= 5) || (ypos >= 5)) {
        return;
    }
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);
    _ledbuff[xpos + ypos * 5] = Color;
    _mode                     = kAnimation_frush;
    xSemaphoreGive(_xSemaphore);
}

void LED_DisPlay::drawpix(uint8_t Number, CRGB Color) {
    if (Number >= NUM_LEDS) {
        return;
    }
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);
    _ledbuff[Number] = Color;
    _mode            = kAnimation_frush;
    xSemaphoreGive(_xSemaphore);
}

void LED_DisPlay::fillpix(CRGB Color) {
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);
    for (int i = 0; i < NUM_LEDS; i++) {
        _ledbuff[i] = Color;
    }
    _mode = kAnimation_frush;
    xSemaphoreGive(_xSemaphore);
}

void LED_DisPlay::clear() {
    xSemaphoreTake(_xSemaphore, portMAX_DELAY);
    for (int8_t i = 0; i < NUM_LEDS; i++) {
        _ledbuff[i] = 0;
    }
    _mode = kAnimation_frush;
    xSemaphoreGive(_xSemaphore);
}

boolean LED_DisPlay::animationrunning() {
    if (_mode == kAnimation_run) {
        return true;
    } else if (_mode == kAnimation_stop) {
        return false;
    }
    return 0;
}

void LED_DisPlay::setWidthHeight(uint16_t xColumns, uint16_t yRows) {
    _xColumns = xColumns;
    _yRows    = yRows;
}
