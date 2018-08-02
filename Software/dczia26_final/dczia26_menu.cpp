#include "dczia26_menu.h"
#include "dczia26_keypad.h"

void main_menu(SSD1306 *screen, Keypad *keypd, Adafruit_NeoPixel *ledstrip)
{
  // keypad layout
  // 1 2 3 A
  // 4 5 6 B
  // 7 8 9 C
  // * 0 # D

  if (screen)
  {
    // Print to the screen
    screen->setFont(ArialMT_Plain_10);
    screen->setTextAlignment(TEXT_ALIGN_LEFT);
    screen->clear();
    screen->println("dczia 2018 proto dos menu");
    screen->println("2) led test");
    screen->println("3) screen test");
    screen->println("A) keypad test");
    screen->println("");

    /* ***********
    screen->println("add your menu choice here");
    *********** */

    // Draw it to the internal screen buffer
    screen->drawLogBuffer(0, 0);
    // Display it on the screen
    screen->display();
  }

  
  // wait for keypress
  char keypress = NO_KEY;
  if (keypd) 
  {
    //keypress = keypd->waitForKey(); // blocking
    keypress = keypd->getKey(); // non-blocking
    if (keypress == NO_KEY) return;
  }
  
  switch (keypress)
  {
    case '2':
    {
      Serial.println("main_menu(): case '2'");

      screen->clear();
      screen->display();
      screen->setTextAlignment(TEXT_ALIGN_LEFT);
      screen->setFont(ArialMT_Plain_24);
      
      uint8_t i = 0;
      int led_delay = 2000;

      // red
      screen->clear();
      screen->drawString(0, 0, "Red!");
      screen->display();
      for(i=0; i< ledstrip->numPixels(); i++)
      {
        ledstrip->setPixelColor(i, ledstrip->Color(255, 0, 0));
      }
      ledstrip->show();
      delay(led_delay);
      
      // green
      screen->clear();
      screen->drawString(0, 0, "Green!");
      screen->display();
      for(i=0; i< ledstrip->numPixels(); i++)
      {
        ledstrip->setPixelColor(i, ledstrip->Color(0, 255, 0));
      }
      ledstrip->show();
      delay(led_delay);

      // blue
      screen->clear();
      screen->drawString(0, 0, "Blue!");
      screen->display();
      for(i=0; i< ledstrip->numPixels(); i++)
      {
        ledstrip->setPixelColor(i, ledstrip->Color(0, 0, 255));
      }
      ledstrip->show();
      delay(led_delay);

      break;
    }
          
    case '3':
    {
      Serial.println("main_menu(): case '3'");
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
      }
      break;
    }

    case 'A':
    {
      Serial.println("main_menu(): case 'A'");

      led_brightness_set(ledstrip, 255);
      
      if (keypd)
      {
        while (keypd->getState(KEY_R3C3) != RELEASED)
        {
          String outstr;
          
          if (screen)
          {
            screen->clear();
            screen->setTextAlignment(TEXT_ALIGN_LEFT);
            screen->setFont(ArialMT_Plain_16);
          }
      
          keypd->getKeys();
      
          // Row 0
          outstr  = keypd->getState(KEY_R0C0);
          outstr += keypd->getState(KEY_R0C1);
          outstr += keypd->getState(KEY_R0C2);
          outstr += keypd->getState(KEY_R0C3);
          outstr += "    'D' to exit";
          //Serial.println(outstr);
          if (screen) screen->drawString(0, 0, outstr);
      
          // Row 1
          outstr  = keypd->getState(KEY_R1C0);
          outstr += keypd->getState(KEY_R1C1);
          outstr += keypd->getState(KEY_R1C2);
          outstr += keypd->getState(KEY_R1C3);
          //Serial.println(outstr);
          if (screen) screen->drawString(0, 16, outstr);
      
          // Row 2
          outstr  = keypd->getState(KEY_R2C0);
          outstr += keypd->getState(KEY_R2C1);
          outstr += keypd->getState(KEY_R2C2);
          outstr += keypd->getState(KEY_R2C3);
          //Serial.println(outstr);
          if (screen) screen->drawString(0, 32, outstr);
      
          // Row 3
          outstr  = keypd->getState(KEY_R3C0);
          outstr += keypd->getState(KEY_R3C1);
          outstr += keypd->getState(KEY_R3C2);
          outstr += keypd->getState(KEY_R3C3);
          // Serial.println(outstr);
          if (screen) screen->drawString(0, 48, outstr);
      
          // finally, update screen with new contents
          if (screen) screen->display();
          delay(1);

          // now let's add some key fun... if key depressed, light it up!
          if ((keypd) && (ledstrip)) 
          {
            set_led_from_keystate(keypd, KEY_R0C0, ledstrip, LED_R0C0, false);
            set_led_from_keystate(keypd, KEY_R0C1, ledstrip, LED_R0C1, false);
            set_led_from_keystate(keypd, KEY_R0C2, ledstrip, LED_R0C2, false);
            set_led_from_keystate(keypd, KEY_R0C3, ledstrip, LED_R0C3, false);

            set_led_from_keystate(keypd, KEY_R1C0, ledstrip, LED_R1C0, false);
            set_led_from_keystate(keypd, KEY_R1C1, ledstrip, LED_R1C1, false);
            set_led_from_keystate(keypd, KEY_R1C2, ledstrip, LED_R1C2, false);
            set_led_from_keystate(keypd, KEY_R1C3, ledstrip, LED_R1C3, false);

            set_led_from_keystate(keypd, KEY_R2C0, ledstrip, LED_R2C0, false);
            set_led_from_keystate(keypd, KEY_R2C1, ledstrip, LED_R2C1, false);
            set_led_from_keystate(keypd, KEY_R2C2, ledstrip, LED_R2C2, false);
            set_led_from_keystate(keypd, KEY_R2C3, ledstrip, LED_R2C3, false);

            set_led_from_keystate(keypd, KEY_R3C0, ledstrip, LED_R3C0, false);
            set_led_from_keystate(keypd, KEY_R3C1, ledstrip, LED_R3C1, false);
            set_led_from_keystate(keypd, KEY_R3C2, ledstrip, LED_R3C2, false);
            set_led_from_keystate(keypd, KEY_R3C3, ledstrip, LED_R3C3, true);

            delay(1);
          }
        }
      }
      led_brightness_restore_last(ledstrip);
      break;
    }

/*
    case {** YOUR_KEY **}:
    {
      Serial.println("main_menu(): case **YOUR_KEY**");
      do_your_stuff();
      break;
    }
*/

    default:
    {
//      Serial.print("main_menu(): case default: "); Serial.println(keypress);
//      if (screen)
//      {
//        screen->println(keypress);    // Print to the screen
//        screen->drawLogBuffer(0, 0);  // Draw it to the internal screen buffer
//        screen->display();            // Display it on the screen
//      }
      break;
    }
  }
}

void set_led_from_keystate(Keypad *keypd, char key, Adafruit_NeoPixel *ledstrip, uint8_t led, bool shownow)
{
  // sanity checks
  if (!key || !ledstrip) return; 

  // states are: typedef enum{ IDLE, PRESSED, HOLD, RELEASED } KeyState;
  KeyState key_state = keypd->getState(key);

  // change color based on state
  // Serial.print("key "); Serial.print(key); Serial.print(" state "); Serial.println(key_state);

  switch (key_state)
  {
    case PRESSED:
    {
      led_set_color(ledstrip, led, 0, 255, 0, shownow);
      break;
    }

    case HOLD:
    {
      led_set_color(ledstrip, led, 0, 0, 255, shownow);
      break;
    }

    default: // includes IDLE
    {
      led_set_color(ledstrip, led, 1, 1, 1, shownow);
      break;
    }
  }
}

