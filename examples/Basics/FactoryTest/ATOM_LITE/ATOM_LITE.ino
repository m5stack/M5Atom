#include <M5Atom.h>
#include <Adafruit_NeoPixel.h>

#define PIN       27  //定义NeoPixel的控制引脚
#define NUMPIXELS 1   //定义NeoPixel控制灯灯数量

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    NUMPIXELS, PIN,
    NEO_GRB + NEO_KHZ800);  // set number of LEDs, pin number, LED type.
                            // 设置灯的数量,控制引脚编号,灯灯类型
                         
void setup() {
    M5.begin();      // Init M5Atom.  初始化 M5Atom
    pixels.begin();  // Init the NeoPixel library.  初始化NeoPixel库

}

void loop() {
    rainbow(20);
}


void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
      while(M5.Btn.read()== 1);
    }
    pixels.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
