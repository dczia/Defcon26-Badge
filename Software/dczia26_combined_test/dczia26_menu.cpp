#include "dczia26_menu.h"
#include "dczia26_keypad.h"

void main_menu(SSD1306 *screen, Keypad *keypd, Adafruit_NeoPixel *ledgrid)
{
  Serial.println("main_menu(): entering");
  if (screen)
  {
    // clear screen
    screen->clear();
    // Print to the screen
    screen->println("Main Menu");
    screen->println("2) screen test");
    screen->println("3) led test");

    /* ***********
    screen->println("add your menu choice here");
    *********** */

    // Draw it to the internal screen buffer
    screen->drawLogBuffer(0, 0);
    // Display it on the screen
    screen->display();
  }

  
  // wait for keypress
  Serial.println("main_menu(): wait for keypress");
  char keypress = NO_KEY;
  if (keypd) 
  {
    keypress = keypd->waitForKey();
    if (keypress == NO_KEY) return;
  }
  
  Serial.println("main_menu(): switch(keypress)");
  switch (keypress)
  {
/*
    case KEY_R0C1:
    {
      Serial.println("main_menu(): case KEY_R0C1");
      if (ledgrid) led_loop(ledgrid);
      break;
    }
          
    case KEY_R0C2:
    {
      Serial.println("main_menu(): case KEY_R0C2");
      if (screen)
      {
        int display_delay=1000;
        screen->clear();
        oled_drawLines(screen);
        delay(display_delay);
        
        screen->clear();
        oled_drawRect(screen);
        delay(display_delay);
        
        screen->clear();
        oled_fillRect(screen);
        delay(display_delay);
        
        screen->clear();
        oled_drawCircle(screen);
        delay(display_delay);
        
        screen->clear();
        oled_drawZia(screen);
        delay(display_delay);
        
        screen->clear();
        oled_printBuffer(screen);
        delay(display_delay);
      }
      break;
    }

    case {** YOUR_KEY **}:
    {
      Serial.println("main_menu(): case **YOUR_KEY**");
      do_your_stuff();
      break;
    }

*/
    default:
    {
      Serial.print("main_menu(): case default: "); Serial.println(keypress);
      if (screen)
      {
        screen->println(keypress);    // Print to the screen
        screen->drawLogBuffer(0, 0);  // Draw it to the internal screen buffer
        screen->display();            // Display it on the screen
      }
      break;
    }
  }
}

