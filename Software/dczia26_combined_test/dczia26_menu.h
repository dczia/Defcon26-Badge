#pragma once

#include "dczia26_keypad.h"
#include "dczia26_led.h"
#include "dczia26_oled.h"


void main_menu(SSD1306 *screen, Keypad *keypd, Adafruit_NeoPixel *ledgrid);
void set_led_from_keystate(Keypad *keypd, char key, Adafruit_NeoPixel *ledstrip, uint8_t led, bool shownow);


