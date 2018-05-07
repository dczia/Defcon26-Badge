// dczia 2018 proto dos test firmware
// combines all major hardware aspects (led, oled, keypad)

// split into functional regions
#include "dczia26_keypad.h"
#include "dczia26_led.h"
#include "dczia26_oled.h"
#include "dczia26_menu.h"

// Global variables
// initilized in "setup()"
// used in "loop()"
SSD1306            *oled = NULL; // uses v3.xx from "esp8266 and esp32 oled driver for ssd1306 display" (https://github.com/ThingPulse/esp8266-oled-ssd1306)
Keypad             *keys = NULL; // currently customized and included within project (will update to forked lib later)
Adafruit_NeoPixel  *leds = NULL; // uses v1.xx from "Adafruit NeoPixel" (https://github.com/adafruit/Adafruit_NeoMatrix)

// in arduino world, "setup()" is called once at power-up (or reset) ... 
void setup(void)
{
  // led_brightness
  // 1-255 = dim setting (1 = dimmest, 255 = needweldingmask)
  // any actual dimming (less than 255) will "sparkle" natively ...  it's a "feature"'d bug... we think.
  uint8_t led_brightness = 10;
   
  // init system debug output
  Serial.begin(115200);

  // call constructors
  Serial.print("Constructing...");
  oled = oled_setup();
  keys = keypad_setup();
  leds = led_setup(led_brightness);

  // call welcome screen (once)
  if (oled) oled_welcome(oled);

  // done with init fuction
  Serial.println("done!");
}

// in arduino world, "loop()" is called over and over and over and ... 
// you get the idea... we don't need to "while(1)" ourselves...
void loop(void)
{
  //Serial.println("looping main menu");

  // main menu itself is non-blocking;
  // if no keys are pressed, function returns so that 
  // the next line(s) can operate (e.g. led color changing)
  // if key(s) are pressed, then appropriate (and 
  // potentially blocking) actions take place.
  main_menu(oled, keys, leds);
  
  // advance color cycling by one iteration
  if (leds) led_loop_advance(leds);
}

