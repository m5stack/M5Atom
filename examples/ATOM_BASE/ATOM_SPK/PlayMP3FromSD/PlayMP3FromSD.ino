/*
    Description: 
    Use ATOM SPK play mp3 files from TF Card
    Before runing put the music file to the TF card
    MP3 file link: http://gitfile.oss-cn-beijing.aliyuncs.com/11-fanfare.mp3
    Please install library before compiling:  
    ESP8266Audio: https://github.com/earlephilhower/ESP8266Audio
*/

#include "M5Atom.h"
#include <WiFi.h>

#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourceID3.h"

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

#define SCK 23
#define MISO 33
#define MOSI 19

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void StatusCallback(void *cbData, int code, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}

void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
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

void setup(){
    M5.begin(true,false,true);
    SPI.begin(SCK, MISO, MOSI, -1);
    if(!SD.begin(-1, SPI, 40000000)){
        Serial.println("Card Mount Failed");
        return;
    }
    M5.dis.drawpix(0, 0xf00000);
    audioLogger = &Serial;
    file = new AudioFileSourceSD("/11-fanfare.mp3");
    id3 = new AudioFileSourceID3(file);
    id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
    out = new AudioOutputI2S();
    out->SetPinout(22, 21, 25);
    mp3 = new AudioGeneratorMP3();
    mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
    mp3->begin(id3, out);
}

void loop(){

  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}

