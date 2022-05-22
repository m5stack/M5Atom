/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite sample source code
* Visit the website for more information：https://docs.m5stack.com/en/atom/atom_spk
*
* describe: SPK.
* date：2021/9/1
* modified：2022/05/22 by @riraosan_0901
*******************************************************************************
  Use ATOM SPK play mp3 files from TF Card
  Before running put the BGM file and Animation GIF file to the TF card
  MP3 file : non.mp3
  GIF file : non_small.gif
*/

#include <Arduino.h>
#include <WiFi.h>
#include "M5Atom.h"
#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourceID3.h"
#include "Video.h"
#include <Ticker.h>

AudioGeneratorMP3  *mp3;
AudioFileSourceSD  *file;
AudioOutputI2S     *out;
AudioFileSourceID3 *id3;

Video *cvbs;

Ticker audioStart;

#define SCK  23
#define MISO 33
#define MOSI 19

void startAudio(void) {
  mp3->begin(id3, out);//flagを用いてもよいかも。
  M5.dis.drawpix(0, 0x00FF00);
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup).
void StatusCallback(void *cbData, int code, const char *string) {
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf.
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1) - 1] = 0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}

void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string) {
  (void)cbData;
  Serial.printf("ID3 callback for: %s = '", type);

  if (isUnicode) {
    string += 2;
  }

  while (*string) {
    char a = *(string++);
    if (isUnicode) {
      string++;
    }
    Serial.printf("%c", a);
  }
  Serial.printf("'\n");
  Serial.flush();
}

void audioTask(void *) {
  for (;;) {
    if (mp3->isRunning()) {
      if (!mp3->loop()) {
        mp3->stop();
        M5.dis.drawpix(0, 0x000000);
      }
    }
    delay(1);//これを書かないとaudioTastが常に処理を専有してしまう。
  }
}

void setup() {
  log_d("Free Heap : %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));

  M5.begin(true, false, true);
  SPI.begin(SCK, MISO, MOSI, -1);
  if (!SD.begin(-1, SPI, 40000000)) {
    Serial.println("Card Mount Failed");
    return;
  }

  M5.dis.drawpix(0, 0x000000);
  audioLogger = &Serial;

  file = new AudioFileSourceSD("/non.mp3");
  id3  = new AudioFileSourceID3(file);
  id3->RegisterMetadataCB(MDCallback, (void *)"ID3TAG");
  out = new AudioOutputI2S(I2S_NUM_1);  // CVBSがI2S0を使っているのでAUDIOはI2S1を設定
  out->SetPinout(22, 21, 25);
  out->SetGain(0.05);//1.0だと音が大きすぎる。0.1ぐらいが適当。後は外部アンプで増幅するのが適切。
  mp3 = new AudioGeneratorMP3();
  mp3->RegisterStatusCB(StatusCallback, (void *)"mp3");
  // mp3->begin(id3, out);

  cvbs = new Video();
  if (cvbs != nullptr) {
    cvbs->begin();
    cvbs->setSd(&SD);
    cvbs->setFilename("/non_small.gif");
    cvbs->openGif();
  } else {
    log_e("Can not allocate CVBS.");
  }

  xTaskCreatePinnedToCore(audioTask, "audioTask", 2048, nullptr, 2, nullptr, PRO_CPU_NUM);

  // タイマーを使ってAnimationとBGMの再生タイミングを合わせる
  audioStart.once_ms(1450, startAudio);
  log_d("Free Heap : %d", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
}

void loop() {
  cvbs->update();
}
