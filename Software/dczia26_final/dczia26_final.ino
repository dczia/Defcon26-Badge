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

// in arduino world, "setup()" is called once at power-up (or reset) ... 
void setup(void)
{
  // init system debug output
  Serial.begin(115200);

  // call constructors
  Serial.print("Constructing...");
  keys = keypad_setup();
  delay(1);

    //Setup LEDS
    strip.Begin();
    strip.Show();

    startupAnimation();
    strip.Show();

    animations.StopAnimation(0);

    SetRandomSeed();
    
    
    
  delay(1);
  oled = oled_setup();
  delay(1);
  ble_setup();
  
  // call welcome screen (once)
  if (oled) oled_welcome(oled);

  // done with init fuction
  Serial.println("done!");

    SetRandomSeed();
  
}

// in arduino world, "loop()" is called over and over and over and ... 
// you get the idea... we don't need to "while(1)" ourselves...
void loop(void)
{

   auto keypress = keys->getKey(); // non-blocking
  
  // main menu itself is non-blocking;
  // if no keys are pressed, function returns so that 
  // the next line(s) can operate (e.g. led color changing)
  // if key(s) are pressed, then appropriate (and 
  // potentially blocking) actions take place.
 // main_menu(oled, keys, leds);
 
   ble_loop();
  // advance color cycling by one iteration
 // delay(1);


    
    FadeInFadeOutRinseRepeat(.1f);

    animations.UpdateAnimations();
    strip.Show();


/*
//Default Animation Loop
 if (animations.IsAnimating())
    {
        // the normal loop just needs these two to run the active animations
        
        animations.UpdateAnimations();
        strip.Show();
    }
    else
    {
        // no animation runnning, start some 
        FadeInFadeOutRinseRepeat(.1f); // 0.0 = black, 0.25 is normal, 0.5 is bright
    }
  
  */

}

