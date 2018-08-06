// dczia 2018 FINAL package
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
Adafruit_SSD1306   *oled = NULL; 
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

  oled = oled_setup();
  ble_setup();

  // call welcome screen (once)
  oled_welcome(oled);

  // done with init fuction
  Serial.println("Done With Setup!");

  SetRandomSeed();
}

// in arduino world, "loop()" is called over and over and over and ...
// you get the idea... we don't need to "while(1)" ourselves...
<<<<<<< HEAD
void loop(void) {

    // Store what mode we're currently in
    static auto mode = '1';

    // Grab the current keypress.  If there is none, it will be
    // NO_KEY.
    auto keypress = keys->getKey(); // non-blocking

    // If we have a keypress, deal with the command
    if(keypress != NO_KEY) {

      // If we're in menu mode, then the next keypress determines
      // the new mode
      if(mode == 'D') {
          mode = keypress;

      // If we're not in menu mode, but we press the menu button,
      // D, then move us into menu mode
      } else if(keypress == 'D') {
         mode = 'D';
      }
    }

    // Run the code associated with the particular command
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
    case 'D':
    case '#':
    case '*':           
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
    case '2':
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
=======
void loop(void)
{
  auto keypress = keys->getKey(); // non-blocking
  
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
>>>>>>> 5529edaea220b871a8c0fd711d32cbef043337c7
}

