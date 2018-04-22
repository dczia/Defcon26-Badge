
#include "dczia26_keypad.h"
#include "dczia26_led.h"
#include "dczia26_oled.h"
#include "dczia26_menu.h"


// Global variables
SSD1306            *oled = NULL;
Keypad             *keys = NULL;
Adafruit_NeoPixel  *leds = NULL;


void setup(void)
{
  uint8_t led_brightness = 1; 
  
  // init system debug output
  Serial.begin(115200);

  // call constructors
  Serial.print("Constructing...");
  oled = oled_setup();
  keys = keypad_setup();
  leds = led_setup(led_brightness);
  Serial.println("done!");
}

void loop(void)
{
  Serial.println("looping main menu");
//  main_menu(oled, keys, leds);

  char keypress = NO_KEY;
  if (keys) 
  {
    String outstr;
    
    if (oled)
    {
      oled->clear();
      oled->setTextAlignment(TEXT_ALIGN_LEFT);
      oled->setFont(ArialMT_Plain_16);
    }

    keys->getKeys();

    // Row 0
    outstr  = keys->getState(KEY_R0C0);
    outstr += keys->getState(KEY_R0C1);
    outstr += keys->getState(KEY_R0C2);
    outstr += keys->getState(KEY_R0C3);
    Serial.println(outstr);
    if (oled) oled->drawString(0, 0, outstr);

    // Row 1
    outstr  = keys->getState(KEY_R1C0);
    outstr += keys->getState(KEY_R1C1);
    outstr += keys->getState(KEY_R1C2);
    outstr += keys->getState(KEY_R1C3);
    Serial.println(outstr);
    if (oled) oled->drawString(0, 16, outstr);

    // Row 2
    outstr  = keys->getState(KEY_R2C0);
    outstr += keys->getState(KEY_R2C1);
    outstr += keys->getState(KEY_R2C2);
    outstr += keys->getState(KEY_R2C3);
    Serial.println(outstr);
    if (oled) oled->drawString(0, 32, outstr);

    // Row 3
    outstr  = keys->getState(KEY_R3C0);
    outstr += keys->getState(KEY_R3C1);
    outstr += keys->getState(KEY_R3C2);
    outstr += keys->getState(KEY_R3C3);
    Serial.println(outstr);
    if (oled) oled->drawString(0, 48, outstr);

    if (oled) oled->display();
  }

  if (leds) led_loop(leds);
}




