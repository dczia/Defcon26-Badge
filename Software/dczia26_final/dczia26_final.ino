
// dczia 2018 proto dos test firmware
// combines all major hardware aspects (led, oled, keypad, ble)

// split into functional regions
#include "dczia26_keypad.h"
#include "dczia26_led.h"
#include "dczia26_oled.h"
#include "dczia26_ble.h"
#include "dczia26_menu.h"
#include "dczia26_sd.h"

// Global variables
// initilized in "setup()"
// used in "loop()"
Adafruit_SSD1306   *oled = NULL; // uses v3.xx from "esp8266 and esp32 oled driver for ssd1306 display" (https://github.com/ThingPulse/esp8266-oled-ssd1306)
Keypad             *keys = NULL; // currently customized and included within project (will update to forked lib later)

// in arduino world, "setup()" is called once at power-up (or reset) ...
void setup(void) {
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


  // Setup the OLED
  oled = oled_setup();

  // Setup the bluetooth
  ble_setup();

  // call welcome screen (once)
  oled_welcome(oled);

  // Set a random seed
  SetRandomSeed();

  SDSetup(oled);

  // done with init fuction
  Serial.println("Done With Setup!");
}

// Maps a pixel location to a pixel value
uint ijtop(uint const & i, uint const & j) {
  return (j - 1) + (i - 1) * 4;
}

// in arduino world, "loop()" is called over and over and over and ...
// you get the idea... we don't need to "while(1)" ourselves...
void loop(void) {

  // Store what mode we're currently in
  static auto mode = '1';

  // Determine if we've changed the mode.  Use this to initialize
  // the animations
  static auto newmode = true;

  // Determine if we have a new keypress
  static auto newpress = true;

  // Last key pressed
  static auto key = '1';
  static auto key_i = uint(1);
  static auto key_j = uint(1);

  // Grab the current keypress.  If there is none, it will be
  // NO_KEY.
  auto keypress = keys->getKey(); // non-blocking

  // If we have a keypress, deal with the command
  if (keypress != NO_KEY) {
    // Denote that a new key was pressed
    newpress = true;

    // If we're in menu mode, then the next keypress determines
    // the new mode
    if (mode == 'D') {
      mode = keypress;
      newmode = true;

      // If we're not in menu mode, but we press the menu button,
      // D, then move us into menu mode
    } else if (keypress == 'D') {
      mode = 'D';
      newmode = true;
    }

    // Convert the keypress into a coordinate (key_i,key_j) where
    // key_i denotes the row and key_j denotes the column.  The
    // upper left corner has coordinate (1,1).
    key = keypress;
    if (keypress == '1') {
      key_i = 1; key_j = 1;
    } else if (keypress == '2') {
      key_i = 1; key_j = 2;
    } else if (keypress == '3') {
      key_i = 1; key_j = 3;
    } else if (keypress == '4') {
      key_i = 2; key_j = 1;
    } else if (keypress == '5') {
      key_i = 2; key_j = 2;
    } else if (keypress == '6') {
      key_i = 2; key_j = 3;
    } else if (keypress == '7') {
      key_i = 3; key_j = 1;
    } else if (keypress == '8') {
      key_i = 3; key_j = 2;
    } else if (keypress == '9') {
      key_i = 3; key_j = 3;
    } else if (keypress == '0') {
      key_i = 4; key_j = 2;
    } else if (keypress == '*') {
      key_i = 4; key_j = 1;
    } else if (keypress == '#') {
      key_i = 4; key_j = 3;
    } else if (keypress == 'A') {
      key_i = 1; key_j = 4;
    } else if (keypress == 'B') {
      key_i = 2; key_j = 4;
    } else if (keypress == 'C') {
      key_i = 3; key_j = 4;
    } else if (keypress == 'D') {
      key_i = 4; key_j = 4;
    }
  }

  // Run the code associated with the particular command
  auto mode_name = std::string();
  auto mode_size = 2;
  switch (mode) {
    case '1': // Reserved for Light Mode
    case '4': // Reserved for Light Mode
    case '5': // Reserved for Light Mode
    case '6': // Reserved for Light Mode
    case '9': // Reserved for Function Mode
    case 'B': // Reserved for Light Mode
    case '#': // Reserved for Function Mode
    case '*': // Reserved for Funciton Mode
      // Set the mode message
      mode_name = "Low Rainbow";

      //Default Animation Loop  
      if (animations.IsAnimating()) { 
        // The normal loop just needs these two to run the active animations  
        animations.UpdateAnimations();  
        strip.Show(); 
      } else {  
        // No animation runnning, start some  
        FadeInFadeOutRinseRepeat(.05f); // 0.0 = black, 0.25 is normal, 0.5 is bright 
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
        FadeInFadeOutRinseRepeat(0.05f); // 0.0 = black, 0.25 is normal, 0.5 is bright
      }

      break;

    //Light modes:
    //1, 2, 3, A
    //4, 5, 6, B
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

    case '3': {
        // Set the mode message
        mode_name = "Pixel Picker";

        if (newpress) {
          // Turn off any animations
          animations.StopAnimation(0);
          delay(1);

          // Set what it means to be an on and off pixel
          auto on = HslColor(120.0 / 360.0, 1.0, 0.5);
          auto off = HslColor(240.0 / 360.0, 1.0, 0.05);

          // Loop over the pixels
          for (auto i = uint(1); i <= 4; i++) {
            for (auto j = uint(1); j <= 4; j++) {
              auto color = (key_i == i && key_j == j) ? on : off;
              strip.SetPixelColor(ijtop(i, j), color);
            }
          }
          delay(1);
          strip.Show();
        }
        break;
      }

    case 'A':
      // Set the mode message
      mode_name = "Connection Machine";
      if (newmode)
        animations.StopAnimation(0);
      //Connection Machine animation
      if (animations.IsAnimating()) {
        animations.UpdateAnimations();
        strip.Show();
      } else {
        PickRandom(.2); 
      }
      break;

    // Function Modes:
    // 7, 8, 9, C
    // *, #
    case '7':
      // Reserving for BLE Scanning project
      // Set the mode message
      mode_name = "BLE Scanning";
      if (newmode) {
        oled->clearDisplay();
        oled->setCursor(0, 0);
        oled->println("Scanning for DEFCON");
        oled->println("badges...");
        oled->display();
        int bleResults[2];
        ble_scan_dczia(bleResults);
        oled->clearDisplay();
        oled->setCursor(0, 0);
        oled->print("Defcon26 Badges: ");
        oled->print(bleResults[0]);
        oled->print("\n");
        oled->print("DCZia Badges: ");
        oled->print(bleResults[1]);
        oled->display();
        delay(5000);
        newmode=false;
      }
      runDefaultAnimations();
      break;
    case '8':
      // Reserving for BLE Scanning project (all named things)
      // Set the mode message
      oled->clearDisplay();
      delay(1);
      ble_scan_all(oled);
      newmode=false;
      mode_name = "BLE Scanning and Record";
      runDefaultAnimations();
      mode='D';
      mode_name = "Menu";
      keypress='D';
      break;
      
    case 'C':
      oled_displaytest(oled);
      // go back to menu
      mode='D';
      mode_name = "Menu";
      keypress='D';
      break;

    case '0':
      // Credits
      if (newmode == true) {
        oled_displayCredits(oled);
        //Put it back on the main menu...
        mode = 'D';
      }
      runDefaultAnimations();
      break;

  }

  // Set the LED message
  if (newmode) {
    oled->clearDisplay();
    oled->setCursor(0, 0);
    oled->setTextSize(2);
    oled->println(" -DCZia26-");
    oled->setTextSize(1);
    oled->println(mode_name.c_str());
    oled->display();
  }

  // At this point, the mode has already run, so we're no longer in a new mode
  newmode = false;
  newpress = false;
}

//Low Rainbow default mode
void runDefaultAnimations(void) {
  //Default Animation Loop
  if (animations.IsAnimating()) {
    // The normal loop just needs these two to run the active animations
    animations.UpdateAnimations();
    strip.Show();
  } else {
    // No animation runnning, start some
    FadeInFadeOutRinseRepeat(.05f); // 0.0 = black, 0.25 is normal, 0.5 is bright
  }
}


