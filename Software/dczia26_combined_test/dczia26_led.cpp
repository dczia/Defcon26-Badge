#include "dczia26_led.h"

uint8_t brightness_value_current   = 255;
uint8_t brightness_value_previous  = 255;

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
  int i;
  
  strip = new Adafruit_NeoPixel(20, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); 
  strip->begin();
  led_brightness_set(strip, brightness);
  for(i=0; i<strip->numPixels(); i++) 
  {
    strip->setPixelColor(i, 0);
  }
  strip->show(); // Initialize all pixels to 'off'
  delay(1);
  return(strip);
}

void led_loop_advance(Adafruit_NeoPixel* strip)
{
  // Some example procedures showing how to display to the pixels:
  rainbowCycle(strip, 32);
}


void led_set_color(Adafruit_NeoPixel* strip, uint8_t key, uint8_t r, uint8_t g, uint8_t b, bool show_now)
{
  int color = strip->Color(r, g, b);
  strip->setPixelColor(key, color);
  if (show_now) strip->show();
}

void led_brightness_set(Adafruit_NeoPixel* strip, uint8_t newbrightness)
{
  // led_brightness
  // 1-255 = dim setting (1 = dimmest, 255 = needweldingmask)
  // any actual dimming (less than 255) will "sparkle" natively ...  it's a "feature"'d bug... we think.

  brightness_value_previous  = brightness_value_current;  // save current
  brightness_value_current   = newbrightness;             // set new
  strip->setBrightness(brightness_value_current);
}

void led_brightness_restore_last(Adafruit_NeoPixel* strip)
{
  brightness_value_current   = brightness_value_previous; // restore previous
  strip->setBrightness(brightness_value_current);
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


