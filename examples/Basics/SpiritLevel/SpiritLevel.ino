#include "M5Atom.h"

bool IMU6886Flag = false;

void setup() {
  M5.begin(true, false, true);
  if (!M5.IMU.Init()) IMU6886Flag = true;
}

#define ALPHA       0.05          // smoothing
#define BETA        (1. - ALPHA)
#define SENSITIVITY 20.
#define BRIGHTNESS  255.          // max 240.
#define FADE        0.67          // determines bubble size

void loop() {
  static float offX = 0., offY = 0.;
  static float smoX = 0., smoY = 0.;
  
  float accX = 0, accY = 0, accZ = 0;
  if (IMU6886Flag == true) {
    M5.IMU.getAccelData(&accX, &accY, &accZ);
  }

  smoX = ALPHA * accX + BETA * smoX;
  smoY = ALPHA * accY + BETA * smoY;
  
  if(M5.Btn.wasPressed()) {
    offX = smoX;
    offY = smoY;
  }


  float xc = (offX - smoX) * SENSITIVITY + 2.0;
  if(xc < 0.) xc = 0.;
  if(xc > 4.) xc = 4.;
  float yc = (offY - smoY) * SENSITIVITY + 2.0;
  if(yc < 0.) yc = 0.;
  if(yc > 4.) yc = 4.;
  
  byte wht[25];

  for(int x=0; x<5; x++) {
    for(int y=0; y<5; y++) {
      float brt = BRIGHTNESS * (1. - FADE * ((xc - (float)x)*(xc - (float)x) + (yc - (float)y)*(yc - (float)y)));
      if(brt < 0.) brt = 0.;
      wht[x+5*y] = brt; // rounds to byte
    }
  }
  
  for(int i=0; i<25; i++) M5.dis.drawpix(i, wht[i]<<16 | wht[i]<<8 | wht[i]);

  M5.update();
}
