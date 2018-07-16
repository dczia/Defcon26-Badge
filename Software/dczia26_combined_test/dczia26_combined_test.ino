// dczia 2018 proto dos test firmware
// combines all major hardware aspects (led, oled, keypad, ble)

// split into functional regions
#include "dczia26_keypad.h"
#include "dczia26_led.h"
#include "dczia26_oled.h"
#include "dczia26_ble.h"
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
  // init system debug output
  Serial.begin(115200);

  // call constructors
  Serial.print("Constructing...");
  keys = keypad_setup();
  delay(1);
  leds = led_setup(1);
  delay(1);
  oled = oled_setup();
  delay(1);
  ble_setup();
  
  // call welcome screen (once)
  if (oled) oled_welcome(oled);

  // done with init fuction
  Serial.println("done!");
}

// in arduino world, "loop()" is called over and over and over and ... 
// you get the idea... we don't need to "while(1)" ourselves...
void loop(void)
{
  // main menu itself is non-blocking;
  // if no keys are pressed, function returns so that 
  // the next line(s) can operate (e.g. led color changing)
  // if key(s) are pressed, then appropriate (and 
  // potentially blocking) actions take place.
  main_menu(oled, keys, leds);
  ble_loop();
  // advance color cycling by one iteration
  delay(1);
  if (leds) led_loop_advance(leds);
}

