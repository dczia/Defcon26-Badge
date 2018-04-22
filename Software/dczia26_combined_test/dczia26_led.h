#pragma once

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIXEL_PIN 26

Adafruit_NeoPixel* led_setup();

void led_loop(Adafruit_NeoPixel* strip);

//////////////////////
// Color Functions // 
/////////////////////

// Fill the dots one after the other with a color
void colorWipe(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait);

void rainbow(Adafruit_NeoPixel* strip, uint8_t wait);

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel* strip, uint8_t wait);

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel* strip, uint32_t c, uint8_t wait);

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel* strip, uint8_t wait);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel* strip, byte WheelPos);

