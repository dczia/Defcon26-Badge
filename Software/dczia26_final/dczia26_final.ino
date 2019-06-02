// dczia 2019 firmware for DCZia26 Badge
// combines all major hardware aspects (led, oled, keypad, ble, mic)

// split into functional regions
#include "Key.h" // This was referred to as dczia.h previously
#include "dczia26_keypad.h"
#include "dczia26_led.h"
#include "dczia26_oled.h"
#include "dczia26_ble.h"
#include "dczia26_sd.h"
#include "arduinoFFT.h" // Standard Arduino FFT library 

arduinoFFT FFT = arduinoFFT(); // Create FFT object

#define COLOR_GREEN HslColor(120.0 / 360.0, 1.0, 0.10)
#define COLOR_BLUE HslColor(240.0 / 360.0, 1.0, 0.05)
#define COLOR_TEAL HslColor(175.0 / 360.0, 1.0, 0.10)
#define COLOR_VIOLET HslColor(300.0 / 360.0, 1.0, 0.10)
#define COLOR_RED HslColor(360.0 / 360.0, 1.0, 0.10)
#define COLOR_YELLOW HslColor(60.0 / 360.0, 1.0, 0.10)
#define COLOR_PINK HslColor(335.0 / 360.0, 1.0, 0.10)

// Initilazie the LED decay for animating the LEDs to the mic input
int decayLED_a = 0;
int decayLED_b = 0;
int decayLED_c = 0;
int decayLED_d = 0;

// Global variables
Adafruit_SSD1306   *oled = NULL; // uses v3.xx from "esp8266 and esp32 oled driver for ssd1306 display" (https://github.com/ThingPulse/esp8266-oled-ssd1306)
Keypad             *keys = NULL; // currently customized and included within project (will update to forked lib later)
hw_timer_t         *timer = NULL;

volatile char lastKey = NO_KEY;

char getLastKey(void);
void displayUpdate(std::string message);
void runDefaultAnimations(void);

void IRAM_ATTR onTimer() {
  char tempKey = keys->getKey();
  if(tempKey != NO_KEY){
    lastKey = tempKey;
  }
}

// Set up the mic for audio capture
#define MIC1_PIN 35               // Microphone is attached to Trinket GPIO #2/Gemma D2 (A1)
#define DC_OFFSET 0               // DC offset in mic signal - if unusure, leave 0
#define NOISE 30                  // Noise/hum/interference in mic signal
#define SAMPLES 256               // Length of buffer for dynamic level adjustment
#define SAMPLING_FREQUENCY 40000  // Hz, must be 40000 or less due to ADC conversion time. Determines maximum frequency that can be analysed by the FFT Fmax=sampleF/2.
#define amplitude 100             // Depending on your audio source level, you may need to increase this value

unsigned int sampling_period_us;
unsigned long microseconds;
byte peak[] = {0,0,0,0,0,0,0};
double vReal[SAMPLES];
double vImag[SAMPLES];
unsigned long newTime, oldTime;

int pointsPerSecond=100;
int captureMinutes = 60;
int delayMS = 1000/pointsPerSecond;
int datapoints=pointsPerSecond * captureMinutes * 60;
int curIdx=0;

// Setup the board
void setup(void) {
  // init system debug output
  Serial.begin(115200);

  // Call class constructors
  Serial.println("Constructing...");
  keys = keypad_setup();
  delay(1);

  //Setup LEDS
  Serial.println("Set up LEDs...");
  strip.Begin();
  strip.Show();
  startupAnimation();
  strip.Show();

  // Setup the key scan interrupt
  Serial.println("Set up \"Key Scan\"...");
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 10000, true);
  timerAlarmEnable(timer);

  // Setup the OLED
  Serial.println("Set up OLED...");
  oled = oled_setup();

  // Setup the bluetooth
  // COMMENT THIS OUT if your board gets stuck in a bootloop, or add a 100uF capacitor to C21 (boards sold on Tindie alreay have this fix)
  Serial.println("Set up BLE...");
  ble_setup();

  // call welcome screen (once)
  Serial.println("Display welcome screen...");
  oled_welcome(oled);

  // Set a random seed
  Serial.println("Set a random seed...");
  SetRandomSeed();

  // Detect and setup a SD card
  Serial.println("Check for SD card...");
  SDSetup(oled);

  // Set up Microphone
  Serial.println("Set up Microphone (MAX4466 on J7)...");
  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  // done with init fuction
  Serial.println("Done With Setup!");

}

// in arduino world, "loop()" is called over and over and over and ...
// you get the idea... we don't need to "while(1)" ourselves...
void loop(void) {

  // Store what mode we're currently in
  static char mode = '1';
  static char oldMode = '1';

  // Determine if we've changed the mode.  Use this to initialize the animations
  static boolean newmode = true;

  // Is menu mode selected?
  if (keys->getState('D') == HOLD) {
      // User wants to select a new mode, jump to menu mode
      mode = 'D';
  }

  if(oldMode != mode){
    Serial.printf("Mode is %c (%d)\r\n", mode, mode);
    oldMode = mode;
  }

  // Run the code associated with the particular command
  switch (mode) {
    case '1': // Reserved for Light Mode
    case '8': // Reserved for Function Mode
    case '9': // Reserved for Function Mode
    case '*': // Reserved for Funciton Mode
    default:
      // Set the mode message
      if(newmode){
        displayUpdate("Hold Bottom Right\nfor Main Menu");
        newmode = false;
      }
      runDefaultAnimations();
      break;

    case 'D':
      {
        // Set the mode message
        if(newmode){
          displayUpdate("Menu");
          newmode = false;
        }
  
        // Swap modes to whatever the last key pressed was
        char key = getLastKey();
        if(key != NO_KEY){
          mode = key;
          newmode = true;
        }
  
        //Default Animation Loop
        if (animations.IsAnimating()) {
          // The normal loop just needs these two to run the active animations
          animations.UpdateAnimations();
          strip.Show();
        } else {
          // No animation runnning, start some
          FadeInFadeOutRinseRepeat(0.05f); // 0.0 = black, 0.25 is normal, 0.5 is bright
        }
      }
      break;

    //Light modes:
    //1, 2, 3, A
    //4, 5, 6, B
    case '2':
      // Set the mode message
      if(newmode){
        displayUpdate("Bright Rainbow");
        newmode = false;
      }

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

    case 'B': {
      // Set the mode message
      if(newmode){
        displayUpdate("Pixel Picker");
        newmode = false;
      }

      if (keys->getState('D') != HOLD) {
        // Turn off any animations
        animations.StopAnimation(0);
        delay(1);

        // Get a copy of the keymap
        uint16_t map = 0;
        for(uint8_t i = 0; i < 4; i++){
          map |= ((keys->bitMap[i] & 0x0F) << (i * 4));
        }

        // Determine if a pixel needs to be on or off
        for(uint8_t i = 0; i < 16; i++){
          if((map >> i) & 0x01){
            // Key is down
            strip.SetPixelColor(i, COLOR_GREEN);
          }
          else{
            strip.SetPixelColor(i, COLOR_BLUE);
          }
        }
        
        strip.Show();
      }
      break;
    }

    case 'A':
      // Set the mode message
      if (newmode){
        displayUpdate("Connection Machine");
        animations.StopAnimation(0);
        newmode = false;
      }
      //Connection Machine animation
      if (animations.IsAnimating()) {
        animations.UpdateAnimations();
        strip.Show();
      } else {
        PickRandom(.3);
      }
      break;

    case '4':
      // Set the mode message
      if (newmode){
        displayUpdate("Random Mode");
        animations.StopAnimation(0);
        newmode = false;
      }
   
      if (animations.IsAnimating()) {
        animations.UpdateAnimations();
        strip.Show();
      } else {
        Random(.2);
      }
      break;

    case '5':
      // Set the mode message
      if (newmode){
        displayUpdate("Light Walk Mode");
        animations.StopAnimation(0);
        newmode = false;
      }
        
      if (animations.IsAnimating()) {
        animations.UpdateAnimations();
        strip.Show();
      } else {
        LightIteration(.3);
      }
      break;

    case '3':
      // Set the mode message
      if (newmode){
        displayUpdate("Party Mode");
        animations.StopAnimation(0);
        newmode = false;
      }
        
      if (animations.IsAnimating()) {
        animations.UpdateAnimations();
        strip.Show();
      } else {
        PartyMode(.1);
      }
      break;

    case '6':
      // Set the mode message
      if (newmode) {
        displayUpdate("Color Waves");
        animations.StopAnimation(0);
        newmode = false;
      } else {
        ColorWaves(.1);
      }
      break;
    case '7':
      // Enter real-time audio response mode ^_^
      if(curIdx < datapoints){
        // Read from the mic until you hit the max datapoints (set above)
        oled->clearDisplay();
        for (int i = 0; i < SAMPLES; i++) {
          newTime = micros()-oldTime;
          oldTime = newTime;
          vReal[i] = analogRead(MIC1_PIN); // A conversion takes about 1uS on an ESP32
          vImag[i] = 0;
          while (micros() < (newTime + sampling_period_us)) { /* do nothing to wait */ }
        }
        FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
        FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
        
        oled->setTextSize(1);
        oled->setTextColor(WHITE);
        oled->setCursor(0,0);
        // Note, these are my best guesses for frequency to pitch assignment
        // oled->println(" A  B  C  D  E  F  G");
        oled->println("420Hz---Aask---840Hz");

        for (int i = 2; i < (SAMPLES/2); i++){ // Don't use sample 0 and only first SAMPLES/2 are usable. Each array eleement represents a frequency and its value the amplitude.
          if (vReal[i] > 2000) { // Add a crude noise filter, 10 x amplitude or more
            int dsize = vReal[i]/amplitude;
            int dsizeLED = vReal[i]/amplitude;
            
            int dmax = 52;
            if (dsize > dmax) dsize = dmax;
            if (dsizeLED > dmax) dsizeLED = dmax;
            
            double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

            // Serial.println(peak);     //Print out what frequency is the most dominant.
            // Animate the OLED
            for(double p = 1; p <= 4; p += 1.0){ // ensure adding doubles and
              if (peak >= p*420.00 && peak < p*466.16) displayBand(0,(int)dsize); // A-range - 400ish Hz, around an A
              if (peak >= p*466.16 && peak < p*508.00) displayBand(1,(int)dsize); // B
              if (peak >= p*508.00 && peak < p*570.00) displayBand(2,(int)dsize); // C
              if (peak >= p*570.00 && peak < p*640.00) displayBand(3,(int)dsize); // D
              if (peak >= p*640.00 && peak < p*680.00) displayBand(4,(int)dsize); // E
              if (peak >= p*680.00 && peak < p*760.00) displayBand(5,(int)dsize); // F
              if (peak >= p*760.00 && peak < p*840.00) displayBand(6,(int)dsize); // G
            }
            // Animate the LEDs
            // Grid looks like:
            /*____band____
               3  2  1  0 |
               7  6  5  4 | DSize
              11 10  9  8 |
              15 14 13 12 |
            */
            Serial.print("DSizeLED");
            Serial.print(dsizeLED);
            if (dsizeLED > 23) {
              for(int i = 15; i >= 12; i--){
                if(strip.GetPixelColor(i) != COLOR_GREEN) {
                  strip.SetPixelColor(i, COLOR_GREEN);
                }
              }
              decayLED_d = 0;
              decayLED_c = 0;
              decayLED_b = 0;
              decayLED_a = 2;
            }
            if(dsizeLED > 30){
              for(int i = 11; i >= 8; i--){
                if(strip.GetPixelColor(i) != COLOR_TEAL) {
                  strip.SetPixelColor(i, COLOR_TEAL);
                }
              }
              decayLED_d = 0;
              decayLED_c = 0;
              decayLED_b = 2;
              decayLED_a = 4;
            }
            if(dsizeLED > 40){
              for(int i = 7; i >= 4; i--){
                if(strip.GetPixelColor(i) != COLOR_YELLOW) {
                  strip.SetPixelColor(i, COLOR_YELLOW);
                }
              }
              decayLED_d = 0;
              decayLED_c = 2;
              decayLED_b = 4;
              decayLED_a = 6;
            }
            if(dsizeLED > 47){
              for(int i = 3; i >= 0; i--){
                if(strip.GetPixelColor(i) != COLOR_RED) {
                  strip.SetPixelColor(i, COLOR_RED);
                }
              }
              decayLED_d = 2;
              decayLED_c = 4;
              decayLED_b = 6;
              decayLED_a = 8;
            }
            
          }
          for (byte band = 0; band <= 6; band++) {
            oled->drawFastHLine(18*band,64-peak[band],14,1);
          }
        }

        // Decay the peak
        if (millis()%4 == 0) {
          for (byte band = 0; band <= 6; band++) {
            if (peak[band] > 0) peak[band] -= 1;
          }
        } 

        oled->display();
        strip.Show();

        // Pixel Picker!
        if (keys->getState('D') != HOLD) {
          // Get a copy of the keymap
          uint16_t map = 0;
          for(uint8_t i = 0; i < 4; i++){
            map |= ((keys->bitMap[i] & 0x0F) << (i * 4));
          }
          // Determine if a pixel needs to be on or off
          for(uint8_t i = 0; i < 16; i++){
            if((map >> i) & 0x01){
              // Key is down
              if(12 <= i && i <= 15) {
                strip.SetPixelColor(i, COLOR_GREEN);
                decayLED_a = 8;
              }
              if(8 <= i && i <= 11) {
                strip.SetPixelColor(i, COLOR_TEAL);
                decayLED_b = 6;
              }
              if(4 <= i && i <= 7) {
                strip.SetPixelColor(i, COLOR_PINK);
                decayLED_c = 4;
              }
              if(0 <= i && i <= 3) {
                strip.SetPixelColor(i, COLOR_VIOLET);
                decayLED_d = 2;
              }
            }
          }
        }

        curIdx++;
        delay(delayMS);
        if(curIdx >= datapoints){
          Serial.println("Done collecting audio samples!");
          mode = 'D';
        }
      
      
      if(decayLED_a == 0){
        for(int i = 15; i >= 12; i--){
          if(strip.GetPixelColor(i) != COLOR_BLUE) {
            strip.SetPixelColor(i, COLOR_BLUE);
          }
        }
      }
      if(decayLED_b == 0){
        for(int i = 11; i >= 8; i--){
          if(strip.GetPixelColor(i) != COLOR_BLUE) {
            strip.SetPixelColor(i, COLOR_BLUE);
          }
        }
      }
      if(decayLED_c == 0){
        for(int i = 7; i >= 4; i--){
          if(strip.GetPixelColor(i) != COLOR_BLUE) {
            strip.SetPixelColor(i, COLOR_BLUE);
          }
        }
      }
      if(decayLED_d == 0){
        for(int i = 3; i >= 0; i--){
          if(strip.GetPixelColor(i) != COLOR_BLUE) {
            strip.SetPixelColor(i, COLOR_BLUE);
          }
        }
      }
      if(decayLED_a > 0) decayLED_a--;
      if(decayLED_b > 0) decayLED_b--;
      if(decayLED_c > 0) decayLED_c--;
      if(decayLED_d > 0) decayLED_d--;
      }
      break;
      
    case '#':
      // BLE Scanning project

      if (newmode) {
        displayUpdate("BLE Scanning");
        newmode = false;
        
        int bleResults[3];
        
        oled->clearDisplay();
        oled->setCursor(0, 0);
        oled->setTextSize(2);
        oled->println("Scanning..");
        oled->display();
        
        ble_scan_dczia(bleResults);
        
        oled->clearDisplay();
        oled->setTextSize(1);
        oled->setCursor(0, 0);
        oled->println("- BLE Scan Results -");
        oled->print("BLE Devices: ");
        oled->print(bleResults[2]);
        oled->print("\n");
        oled->print("Defcon26 Badges: ");
        oled->print(bleResults[0]);
        oled->print("\n");
        oled->print("DCZia Badges: ");
        oled->print(bleResults[1]);
        oled->display();
      }
      runDefaultAnimations();
      break;

    case 'C':
      oled_displaytest(oled);
      // go back to menu
      mode = 'D';
      break;

    case '0':
      // Credits
      if (newmode) {
        oled_displayCredits(oled);
        //Put it back on the main menu...
        mode = 'D';
      }
      runDefaultAnimations();
      break;
  }
}

/**
 * Get the last key pressed
 */
char getLastKey(void){
  char retKey = lastKey;
  lastKey = NO_KEY;
  return retKey;
}

/**
 * Update the OLED screen
 */
void displayUpdate(std::string message){
    oled->clearDisplay();
    oled->setCursor(0, 0);
    oled->setTextSize(2);
    oled->println(" -DCZia26-");
    oled->setTextSize(1);
    oled->println(message.c_str());
    oled->display();
}

/**
 * Run the default animation - low intensity rainbow
 */
void runDefaultAnimations(void){
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

void displayBand(int band, int dsize){
  // Draw the max number of lines for OLED EQ display
  if (band == 7) {oled->drawFastHLine(18*6,0,14,1);}
  for (int s = 0; s <= dsize; s=s+2){oled->drawFastHLine(18*band,64-s,14,1);}
  if (dsize > peak[band]) {peak[band] = dsize;}
}