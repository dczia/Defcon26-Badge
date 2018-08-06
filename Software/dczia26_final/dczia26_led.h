#pragma once

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>



const uint16_t PixelCount = 16; // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 27;  // make sure to set this to the correct pin, ignored for Esp8266
const uint8_t AnimationChannels = 1; // we only need one as all the pixels are animated at once


// extern NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0800KbpsMethod> strip; //(PixelCount, PixelPin);

extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip; //(PixelCount, PixelPin);

extern NeoPixelAnimator animations; //(AnimationChannels); // NeoPixel animation management object

void SetRandomSeed();
void startupAnimation();
void FadeInFadeOutRinseRepeat(float luminance);

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




