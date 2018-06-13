#pragma once

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

// pin used to communicate with LEDs
#define NEOPIXEL_PIN 26

// LED array-to-matrix mapping
#define LED_R0C0 15
#define LED_R0C1 14
#define LED_R0C2 13
#define LED_R0C3 12
#define LED_R1C0 11
#define LED_R1C1 10
#define LED_R1C2 9
#define LED_R1C3 8
#define LED_R2C0 7
#define LED_R2C1 6
#define LED_R2C2 5
#define LED_R2C3 4
#define LED_R3C0 3
#define LED_R3C1 2
#define LED_R3C2 1
#define LED_R3C3 0



Adafruit_NeoPixel* led_setup(uint8_t brightness);

void led_loop_advance(Adafruit_NeoPixel* strip);
void led_set_color(Adafruit_NeoPixel* strip, uint8_t key, uint8_t r, uint8_t g, uint8_t b, bool show_now);
void led_brightness_set(Adafruit_NeoPixel* strip, uint8_t newbrightness);
void led_brightness_restore_last(Adafruit_NeoPixel* strip);


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

