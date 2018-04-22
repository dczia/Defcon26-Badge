#include "dczia26_led.h"

Adafruit_NeoPixel* led_setup(uint8_t brightness)
{
  // IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
  // pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
  // and minimize distance between Arduino and first pixel.  Avoid connecting
  // on a live circuit...if you must, connect GND first.
  
  // Parameter 1 = number of pixels in strip
  // Parameter 2 = Arduino pin number (most are valid)
  // Parameter 3 = pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
  //   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
  //Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //Gradual Fade

  Adafruit_NeoPixel* strip = NULL;
  
  strip = new Adafruit_NeoPixel(40, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); //Rainbow Fade
  strip->begin();
  strip->setBrightness(brightness);
  strip->show(); // Initialize all pixels to 'off'
  return(strip);
}

void led_loop(Adafruit_NeoPixel* strip)
{
  // Some example procedures showing how to display to the pixels:
  //rainbow(60);
  Serial.print("starting rainbowcycle...");
  rainbowCycle(strip, 32);
  Serial.println("done!");
}

//////////////////////
// Color Functions // 
/////////////////////

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip->numPixels(); i++) {
    strip->setPixelColor(i, c);
    strip->show();
    delay(wait);
  }
}

void rainbow(Adafruit_NeoPixel* strip, uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(strip, (i+j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel* strip, uint8_t wait) {
  static uint16_t j = 0;
         uint16_t i;

  // removed looping to make rest of application more responsive.  
  // outer "j" variable changed to static so that future calls can 
  // pick up where it left off ... 
  
  //for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel

    for(i=0; i< strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(strip, ((i * 256 / strip->numPixels()) + j) & 255));
    }
    strip->show();
//    delay(wait);
//  }

  j++;
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip->show();

      delay(wait);

      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel* strip, uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, Wheel(strip,  (i+j) % 255));    //turn every third pixel on
      }
      strip->show();

      delay(wait);

      for (uint16_t i=0; i < strip->numPixels(); i=i+3) {
        strip->setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


