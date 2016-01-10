#include "lightStructs.h"
#include <Adafruit_NeoPixel.h>
//testing
const int nLEDs = 36;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nLEDs, 9, NEO_GRB + NEO_KHZ800);
unsigned long interval = 1000;
unsigned long previousMillis=0;
//6 = pin location i.e. D6
//NEO_GRB + NEO_KHZ800 is the configuration how LED library sends information to the pixels - don't need to change this.

void setup() {
  pixels.begin();
  Serial.begin(57600);
  //begin = start up pixel
}

int offset = 0;

void loop() {
  int n;
  //Declare value and specify its type
  //n++ == n2 = n+1
  //for loop -> start condition, test, do something after each loop round.
  if ((unsigned long) (millis() - previousMillis) >= interval) {
        previousMillis = millis();
    
    for (n = 0 ; n < 24; n++) {
      
      if ((offset/4) % 24 == n)  {
        pixels.setPixelColor(n, pixels.Color(0,0,255));
      }
      else {
        pixels.setPixelColor(n, pixels.Color(0,0,0));
      }
    }  
  }
 
  for (n = 0 ; n < 12; n++) {
    int h = (int)((float)256.0 * (float(n) / 12.0));
    RGB rgb = hsvToColour(h + offset, 255, 80);
    pixels.setPixelColor(n + 24, pixels.Color(rgb.r, rgb.g, rgb.b));
    //Same as above but for 12 pixel ring. The pixels are chained so start at 24 (12ring is pixels 24-35)
  }
  offset += 2;
  //changes speed.
  offset %= 256*24;
  // efficient looping the numbers when its max. Uses modulus.
  pixels.show();
  // This allows pixels to see data (can batch process before pixels see it).
}


RGB hsvToColour(unsigned int h, unsigned int s, unsigned int v) {
  unsigned char region, remainder, p, q, t;
  h = (h + 256) % 256;
  if (s > 255) s = 255;
  if (v > 255) v = 255;
  else v = (v * v) >> 8;
  if (s == 0) return (RGB) {
    v, v, v
  };
  region = h / 43;
  remainder = (h - (region * 43)) * 6;
  p = (v * (255 - s)) >> 8;
  q = (v * (255 - ((s * remainder) >> 8))) >> 8;
  t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;
  switch (region) {
    case 0:
      return (RGB) {
        v, p, t
      };
    case 1:
      return (RGB) {
        q, p, v
      };
    case 2:
      return (RGB) {
        p, t, v
      };
    case 3:
      return (RGB) {
        p, v, q
      };
    case 4:
      return (RGB) {
        t, v, p
      };
  }
  return (RGB) {
    v, q, p
  };
}

