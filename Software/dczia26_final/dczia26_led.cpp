// NeoPixelFunFadeInOut
// This example will randomly pick a color and fade all pixels to that color, then
// it will fade them to black and restart over
//
// This example demonstrates the use of a single animation channel to animate all
// the pixels at once.
//

#include "dczia26_led.h"


// For Esp8266, the Pin is omitted and it uses GPIO3 due to DMA hardware use.
// There are other Esp8266 alternative methods that provide more pin options, but also have
// other side effects.
//NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);
//
// NeoEsp8266Uart800KbpsMethod uses GPI02 instead

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

NeoPixelAnimator animations(AnimationChannels); // NeoPixel animation management object

uint16_t effectState = 0;  // general purpose variable used to store effect state

#define colorSaturation 128

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);

auto HSLcolor = 0.0;
auto WheelPos = 0.0;
auto hue = 0;
int ColorWavePixels[] = {0, 1, 2, 3, 7, 6, 5, 4, 8, 9, 10, 11, 15, 14, 13, 12, 13, 14, 15, 11, 10, 9, 8, 4, 5, 6, 7, 3, 2, 1};



// what is stored for state is specific to the need, in this case, the colors.
// basically what ever you need inside the animation update function
struct MyAnimationState
{
  RgbColor StartingColor;
  RgbColor EndingColor;
};

// one entry per pixel to match the animation timing manager
MyAnimationState animationState[AnimationChannels];


void startupAnimation()
{
  auto luminance = 0.2f;
  strip.ClearTo(hslRed);
  /* strip.SetPixelColor(1,  HslColor(360.0f , 1.0f, luminance));
    strip.SetPixelColor(2,  HslColor(360.0f , 1.0f, luminance));
    strip.SetPixelColor(3,  HslColor(360.0f , 1.0f, luminance));
    strip.SetPixelColor(4,  HslColor(360.0f , 1.0f, luminance));

    strip.SetPixelColor(5,  HslColor(340.0f , 1.0f, luminance));
    strip.SetPixelColor(6,  HslColor(340.0f , 1.0f, luminance));
    strip.SetPixelColor(7,  HslColor(340.0f , 1.0f, luminance));
    strip.SetPixelColor(8,  HslColor(340.0f , 1.0f, luminance));
    strip.SetPixelColor(9,  HslColor(320.0f , 1.0f, luminance));
    strip.SetPixelColor(10,  HslColor(320.0f , 1.0f, luminance));
    strip.SetPixelColor(11,  HslColor(320.0f , 1.0f, luminance));
    strip.SetPixelColor(12,  HslColor(320.0f , 1.0f, luminance));
    strip.SetPixelColor(13,  HslColor(300.0f , 1.0f, luminance));
    strip.SetPixelColor(14,  HslColor(300.0f , 1.0f, luminance));
    strip.SetPixelColor(15,  HslColor(300.0f , 1.0f, luminance));
    strip.SetPixelColor(16,  HslColor(300.0f , 1.0f, luminance));
    strip.Show(); */
}

void SetRandomSeed()
{
  uint32_t seed;

  // random works best with a seed that can use 31 bits
  // analogRead on a unconnected pin tends toward less than four bits
  seed = analogRead(0);
  delay(1);

  for (int shifts = 3; shifts < 31; shifts += 3)
  {
    seed ^= analogRead(0) << shifts;
    delay(1);
  }

  randomSeed(seed);
}

// simple blend function
void BlendAnimUpdate(const AnimationParam& param)
{
  // this gets called for each animation on every time step
  // progress will start at 0.0 and end at 1.0
  // we use the blend function on the RgbColor to mix
  // color based on the progress given to us in the animation
  RgbColor updatedColor = RgbColor::LinearBlend(
                            animationState[param.index].StartingColor,
                            animationState[param.index].EndingColor,
                            param.progress);

  // apply the color to the strip
  for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
  {
    strip.SetPixelColor(pixel, updatedColor);

  }

}

void SimpleBlendAnimUpdate(const AnimationParam& param)
{
  // this gets called for each animation on every time step
  // progress will start at 0.0 and end at 1.0
  // we use the blend function on the RgbColor to mix
  // color based on the progress given to us in the animation
  RgbColor updatedColor = RgbColor::LinearBlend(
                            animationState[param.index].StartingColor,
                            animationState[param.index].EndingColor,
                            param.progress);

  // apply the color to the strip
  for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
  {
    strip.SetPixelColor(pixel, updatedColor);
    strip.SetPixelColor(pixel + 1, updatedColor);
    strip.SetPixelColor(pixel + 2, updatedColor);
    strip.SetPixelColor(pixel + 3, updatedColor);
    delay(20);
  }

}

void FadeInFadeOutRinseRepeat(float luminance)
{
  if (effectState == 0)
  {
    // Fade upto a random color
    // we use HslColor object as it allows us to easily pick a hue
    // with the same saturation and luminance so the colors picked
    // will have similiar overall brightness
    RgbColor target = HslColor(random(360) / 360.0f, 1.0f, luminance);
    uint16_t time = random(800, 2000);

    animationState[0].StartingColor = strip.GetPixelColor(0);
    animationState[0].EndingColor = target;

    animations.StartAnimation(0, time, BlendAnimUpdate);
  }
  else if (effectState == 1)
  {
    // fade to black
    uint16_t time = random(600, 700);

    animationState[0].StartingColor = strip.GetPixelColor(0);
    animationState[0].EndingColor = RgbColor(0);

    animations.StartAnimation(0, time, BlendAnimUpdate);
  }

  // toggle to the next effect state
  // effectState = (effectState + 1) % 2;
  effectState = 0;
}

void PickRandom(float luminance)
{
  // pick random count of pixels to animate
  uint16_t count = random(PixelCount);
  while (count > 0)
  {
    // pick a random pixel
    uint16_t pixel = random(PixelCount);

    // pick random time and random color
    // we use HslColor object as it allows us to easily pick a color
    // with the same saturation and luminance
    uint16_t time = random(100, 400);
    auto myrand = random(1000) / 1000.;

    strip.SetPixelColor(pixel, HslColor(0.0, 1.0f, luminance * myrand * myrand * myrand));

    //animations.StartAnimation(pixel, time, SimpleBlendAnimUpdate);


    count--;
  }
  strip.Show();
  delay(250);
}


void LightIteration(float luminance)
{
  // pick random count of pixels to animate

  RgbColor target = HslColor(random(360) / 360.0f, 1.0f, luminance);

  for (uint16_t pixel = 0; pixel < PixelCount; pixel++)
  {
    strip.SetPixelColor(pixel, target );
    strip.SetPixelColor(pixel + 1, target );
    strip.SetPixelColor(pixel + 2, target );
    strip.SetPixelColor(pixel + 3, target );
    strip.Show();
    delay(20);
  }
}


void PartyMode(float luminance)
{
  if (effectState == 0)
  {
    // Fade upto a random color
    // we use HslColor object as it allows us to easily pick a hue
    // with the same saturation and luminance so the colors picked
    // will have similiar overall brightness
    RgbColor target = HslColor(random(360) / 360.0f, 1.0f, luminance);
    uint16_t time = random(200, 300);

    animationState[0].StartingColor = strip.GetPixelColor(0);
    animationState[0].EndingColor = target;

    animations.StartAnimation(0, time, BlendAnimUpdate);
  }
  else if (effectState == 1)
  {
    // fade to black
    uint16_t time = random(200, 300);

    animationState[0].StartingColor = strip.GetPixelColor(0);
    animationState[0].EndingColor = RgbColor(0);

    animations.StartAnimation(0, time, BlendAnimUpdate);
  }

  // toggle to the next effect state
  effectState = (effectState + 1) % 2;
}


void Random(float luminance)
{
  RgbColor target = HslColor(random(360) / 360.0f, 1.0f, luminance);
  strip.SetPixelColor(random(16), target);
  strip.Show();
  delay(30);
}


void ColorWaves(float luminance)
{

  for (int i = 0; i < sizeof(ColorWavePixels) / sizeof ( int ); i++) {
    Serial.print(" CW Index = ");
    Serial.print(i);
    Serial.print(sizeof(ColorWavePixels));
    strip.SetPixelColor(ColorWavePixels[i], HslColor(hue / 360.0f, 1.0f, luminance));
    strip.Show();
    delay(70);
    hue = (hue + 11) % 360;
  }
  delay(30);

} // end waves



