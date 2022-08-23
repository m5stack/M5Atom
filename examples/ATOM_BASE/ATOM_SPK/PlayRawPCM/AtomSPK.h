#ifndef _ATOMSPK_H_
#define _ATOMSPK_H_

#include "M5Atom.h"
#include "Arduino.h"
#include <driver/i2s.h>
#include "FS.h"

#define CONFIG_I2S_BCK_PIN     22
#define CONFIG_I2S_LRCK_PIN    21
#define CONFIG_I2S_DATA_PIN    25
#define CONFIG_I2S_DATA_IN_PIN -1

#define SPAKER_I2S_NUMBER I2S_NUM_0

typedef struct beepParameters {
    int rate;
    int freq;
    int maxval;
    size_t time;
    // beepParameters() :rate(44100),freq(2000),maxval(10000),time(500){}
    // beepParameters(int rate,int freq,int maxval,size_t time)
    // :rate(rate),freq(freq),maxval(maxval),time(time){}
} beepParameters_t;

typedef struct {
    void *pAudioData;
    int length;
    bool freeFlag;
} audioParameters_t;

enum playType {
    kTypeNull = 0,
    kTypeAudio,
    kTypeBeep,
};

typedef struct {
    int type;
    void *dataptr;
} i2sQueueMsg_t;

typedef struct audioList {
    size_t _num;
    int type;
    void *dataptr;
    audioList *nextPtr;
} audioList_t;

class ATOMSPK {
   public:
    bool begin(int __rate = 44100);
    size_t playRAW(const uint8_t *__audioPtr, size_t __size,
                   bool __modal = false, bool freeFlag = true,
                   TickType_t __ticksToWait = portMAX_DELAY);
    size_t playBeep(int __freq = 2000, int __timems = 200, int __maxval = 10000,
                    bool __modal = false);

   private:
    size_t _rate      = 44100;
    size_t listLength = 0;
};

#endif