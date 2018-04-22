
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
  // init system debug output
  Serial.begin(115200);

  // call constructors
  Serial.print("Constructing...");
  oled = oled_setup();
  keys = keypad_setup();
  leds = led_setup();
  Serial.println("done!");
}

void loop(void)
{
  Serial.println("looping main menu");
  main_menu(oled, keys, leds);
}




