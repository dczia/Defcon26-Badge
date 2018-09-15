#pragma once

#include <NeoPixelBus.h>
#include <NeoPixelAnimator.h>



const uint16_t PixelCount = 16; // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 27;  // make sure to set this to the correct pin, ignored for Esp8266
const uint8_t AnimationChannels = 1; // we only need one as all the pixels are animated at once


// extern NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0800KbpsMethod> strip; //(PixelCount, PixelPin);

extern NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip; //(PixelCount, PixelPin);

extern NeoPixelAnimator animations; //(AnimationChannels); // NeoPixel animation maagement object

void SetRandomSeed();
void startupAnimation();
void FadeInFadeOutRinseRepeat(float luminance);
void PickRandom(float luminance);
void LightIteration(float luminance);
void PartyMode(float luminance);
void Random(float luminance);
void ColorWaves(float luminance);

HslColor Wheel(byte WheelPos);

// LED array-to-matrix mapping
#define LED_R0C0 0
#define LED_R0C1 1
#define LED_R0C2 2
#define LED_R0C3 3
#define LED_R1C0 4
#define LED_R1C1 5
#define LED_R1C2 6
#define LED_R1C3 7
#define LED_R2C0 8
#define LED_R2C1 9
#define LED_R2C2 10
#define LED_R2C3 11
#define LED_R3C0 12
#define LED_R3C1 13
#define LED_R3C2 14
#define LED_R3C3 15

#define colorSaturation 128

const RgbColor red(colorSaturation, 0, 0);
const RgbColor green(0, colorSaturation, 0);
const RgbColor blue(0, 0, colorSaturation);
const RgbColor teal(0, colorSaturation, colorSaturation);
const RgbColor white(colorSaturation);
const RgbColor yellow(colorSaturation, colorSaturation-32, 0);
const RgbColor orange(colorSaturation, colorSaturation-96, 0);
const RgbColor purple(colorSaturation, 0, colorSaturation);
const RgbColor black(0);

const HslColor hslRed(red);
const HslColor hslGreen(green);
const HslColor hslTeal(teal);
const HslColor hslBlue(blue);
const HslColor hslWhite(white);
const HslColor hslYellow(yellow);
const HslColor hslOrange(orange);
const HslColor hslPurple(purple);
const HslColor hslBlack(black);

