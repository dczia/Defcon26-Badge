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
Adafruit_SSD1306   *oled = NULL; // uses v3.xx from "esp8266 and esp32 oled driver for ssd1306 display" (https://github.com/ThingPulse/esp8266-oled-ssd1306)
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

   // animations.StopAnimation(0);

    SetRandomSeed();
    
    
    
 // delay(1);
  oled = oled_setup();
  //delay(1);
  ble_setup();
  
  // call welcome screen (once)
  oled_welcome(oled);

  // done with init fuction
   Serial.println("Done With Setup!");

    SetRandomSeed();
  
}

// in arduino world, "loop()" is called over and over and over and ... 
// you get the idea... we don't need to "while(1)" ourselves...
void loop(void) {

    // Store what mode we're currently in
    static auto mode = '1';

    // Determine if we've changed the mode.  Use this to initialize
    // the animations
    static auto newmode = true;

    // Grab the current keypress.  If there is none, it will be
    // NO_KEY.
    auto keypress = keys->getKey(); // non-blocking

    // If we have a keypress, deal with the command
    if(keypress != NO_KEY) {

      // If we're in menu mode, then the next keypress determines
      // the new mode
      if(mode == 'D') {
          mode = keypress;
          newmode = true;

      // If we're not in menu mode, but we press the menu button,
      // D, then move us into menu mode
      } else if(keypress == 'D') {
         mode = 'D';
         newmode = true;
      }
    }

    // Run the code associated with the particular command
    auto mode_name = std::string();
    auto mode_size = 2;
    switch(mode) {
    case '1':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
    case 'A':
    case 'B':
    case 'C':
    case '#':
    case '*':
        // Set the mode message
        mode_name = "Low Rainbow";
        
        //Default Animation Loop
        if (animations.IsAnimating()) {
            // The normal loop just needs these two to run the active animations
            animations.UpdateAnimations();
            strip.Show();
        } else {
            // No animation runnning, start some 
            FadeInFadeOutRinseRepeat(.1f); // 0.0 = black, 0.25 is normal, 0.5 is bright
        }
        break;
    case 'D':
        // Set the mode message
        mode_name = "Menu";
        mode_size = 4;
  
        //Default Animation Loop
        if (animations.IsAnimating()) {
            // The normal loop just needs these two to run the active animations
            animations.UpdateAnimations();
            strip.Show();
        } else {
            // No animation runnning, start some 
            FadeInFadeOutRinseRepeat(0.0f); // 0.0 = black, 0.25 is normal, 0.5 is bright
        }
    
        break;
        
    case '2':
        // Set the mode message
        mode_name = "High Rainbow";
    
        //Default Animation Loop
        if (animations.IsAnimating()) {
            // The normal loop just needs these two to run the active animations
            animations.UpdateAnimations();
            strip.Show();
        } else {
            // No animation runnning, start some 
            FadeInFadeOutRinseRepeat(.5f); // 0.0 = black, 0.25 is normal, 0.5 is bright
        }    
        break;
    }

    // Set the LED message
    if(newmode) {
        oled->clearDisplay();
        oled->setCursor(0, 0);
        oled->setTextSize(mode_size);
        oled->println(mode_name.c_str());
        oled->display();
    }

    // At this point, the mode has already run, so we're no longer in a new mode
    newmode=false;
}

