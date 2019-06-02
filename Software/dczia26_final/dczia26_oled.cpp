#include "dczia26_oled.h"

Adafruit_SSD1306* oled_setup(void){
  //Initialize the screen
  Adafruit_SSD1306* screen = NULL;
  screen = new Adafruit_SSD1306();
  screen->begin(SSD1306_SWITCHCAPVCC, 0x3c);
  screen->setTextSize(1);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 0);
  screen->clearDisplay();

  //Get test text in at the start.
  screen->println("INITIALIZING...");
  screen->display();
  delay(1500);
  return (screen);
}

void oled_displaytest(Adafruit_SSD1306 *screen){
  screen->clearDisplay();
  oled_drawLines(screen);
  screen->clearDisplay();
  oled_drawRect(screen);
  screen->clearDisplay();
  oled_fillRect(screen);
  screen->clearDisplay();
  oled_drawCircle(screen);
  screen->clearDisplay();
  oled_drawZia(screen);
  screen->clearDisplay();
}

void oled_welcome(Adafruit_SSD1306 *screen){
  screen->clearDisplay();
  screen->println("Welcome, dczia..");
  screen->println("main_menu() in 3..");
  screen->display();
  delay(750);

  screen->clearDisplay();
  screen->setCursor(0, 0);
  screen->println("2..");
  screen->display();
  delay(750);

  screen->clearDisplay();
  screen->setCursor(0, 0);
  screen->println("1..");
  screen->display();
  delay(1000);

  screen->clearDisplay();
  screen->setCursor(0, 0);
  screen->setTextSize(2);
  screen->println(" -DCZia26-");
  screen->setTextSize(1);
  screen->println("     main_menu()");
  screen->display();
  delay(250);
  screen->invertDisplay(true);
  delay(750);
  screen->invertDisplay(false);
}

void oled_drawLines(Adafruit_SSD1306 *screen){
  for(int16_t i = 0; i < DISPLAY_WIDTH; i += 4){
    screen->drawLine(0, 0, i, DISPLAY_HEIGHT - 1, 1);
    screen->display();
    delay(10);
  }
  for(int16_t i = 0; i < DISPLAY_HEIGHT; i += 4){
    screen->drawLine(0, 0, DISPLAY_WIDTH - 1, i, 1);
    screen->display();
    delay(10);
  }
  delay(250);

  screen->clearDisplay();
  for(int16_t i = 0; i < DISPLAY_WIDTH; i += 4){
    screen->drawLine(0, DISPLAY_HEIGHT - 1, i, 0, 1);
    screen->display();
    delay(10);
  }
  for(int16_t i = DISPLAY_HEIGHT - 1; i >= 0; i -= 4){
    screen->drawLine(0, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH - 1, i, 1);
    screen->display();
    delay(10);
  }
  delay(250);

  screen->clearDisplay();
  for(int16_t i = DISPLAY_WIDTH - 1; i >= 0; i -= 4){
    screen->drawLine(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, i, 0, 1);
    screen->display();
    delay(10);
  }
  for(int16_t i = DISPLAY_HEIGHT - 1; i >= 0; i -= 4){
    screen->drawLine(DISPLAY_WIDTH - 1, DISPLAY_HEIGHT - 1, 0, i, 1);
    screen->display();
    delay(10);
  }
  delay(250);
  screen->clearDisplay();
  for(int16_t i = 0; i < DISPLAY_HEIGHT; i += 4){
    screen->drawLine(DISPLAY_WIDTH - 1, 0, 0, i, 1);
    screen->display();
    delay(10);
  }
  for(int16_t i = 0; i < DISPLAY_WIDTH; i += 4){
    screen->drawLine(DISPLAY_WIDTH - 1, 0, i, DISPLAY_HEIGHT - 1, 1);
    screen->display();
    delay(10);
  }
  delay(250);
}

// Adapted from Adafruit_SSD1306
void oled_drawRect(Adafruit_SSD1306 *screen){
  for(int16_t i = 0; i < DISPLAY_HEIGHT / 2; i += 2){
    screen->drawRect(i, i, DISPLAY_WIDTH - 2 * i, DISPLAY_HEIGHT - 2 * i, 1);
    screen->display();
    delay(10);
  }
}


//draw zia
void oled_drawZia(Adafruit_SSD1306 *screen){

  for(int16_t i = 0; i < DISPLAY_WIDTH - dczia_size; ++i){
    screen->clearDisplay();
    screen->drawBitmap(i, 0, zia, dczia_size, dczia_size, 1);
    screen->display();
  }

  for(int16_t i = 0; i < DISPLAY_WIDTH - dczia_size; ++i){
    screen->clearDisplay();
    screen->drawBitmap(DISPLAY_WIDTH - dczia_size - i, 0, zia, dczia_size, dczia_size, 1);
    screen->display();
  }
}

// Adapted from Adafruit_SSD1306
void oled_fillRect(Adafruit_SSD1306 *screen){
  uint8_t color = 1;
  for(int16_t i = 0; i < DISPLAY_HEIGHT / 2; i += 3) {
    screen->fillRect(i, i, DISPLAY_WIDTH - i * 2, DISPLAY_HEIGHT - i * 2, 1);
    screen->display();
    delay(10);
  }
}

void oled_drawCircle(Adafruit_SSD1306 *screen){
  for(int16_t i = 0; i < DISPLAY_HEIGHT; i += 2) {
    screen->drawCircle(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, i, 1);
    screen->display();
    delay(10);
  }
  delay(1000);
  screen->clearDisplay();

  // This will draw the part of the circel in quadrant 1
  // Quadrants are numberd like this:
  //   0010 | 0001
  //  ------|-----
  //   0100 | 1000
  //
  screen->drawCircle(DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4, DISPLAY_HEIGHT / 4, 1);
  screen->display();
  delay(200);
  screen->drawCircle(DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4 * 3, DISPLAY_HEIGHT / 4, 1);
  screen->display();
  delay(200);
  screen->drawCircle(DISPLAY_WIDTH / 4 * 3, DISPLAY_HEIGHT / 4 * 3, DISPLAY_HEIGHT / 4, 1);
  screen->display();
  delay(200);
  screen->drawCircle(DISPLAY_WIDTH / 4 * 3, DISPLAY_HEIGHT / 4, DISPLAY_HEIGHT / 4, 1);
  screen->display();
}

void oled_displayCredits(Adafruit_SSD1306 *screen){
  screen->clearDisplay();
  screen->setTextSize(2);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 0);
  screen->println("Credits!");
  screen->setTextSize(1);
  screen->print("hamster, lithochasm..");
  screen->display();
  delay(2000);
  screen->clearDisplay();
  screen->setTextSize(2);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 0);
  screen->println("Credits!");
  screen->setTextSize(1);
  screen->println("gateherder, kexel...");
  screen->display();
  delay(2000);
  screen->clearDisplay();
  screen->setTextSize(2);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 0);
  screen->println("Credits!");
  screen->setTextSize(1);
  screen->print("catblade, joe...");
  screen->display();
  delay(2000);
  screen->clearDisplay();
  screen->setTextSize(2);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 0);
  screen->println("Credits!");
  screen->setTextSize(1);
  screen->println("ancients, jediguybob");
  screen->println("& the @DCZia505 Crew!");
  screen->display();
  delay(2000);
  screen->clearDisplay();
  screen->setTextSize(2);
  screen->setTextColor(WHITE);
  screen->setCursor(0, 0);
  screen->println("Credits!");
  screen->setTextSize(1);
  screen->println("audio EQ by:");
  screen->println("Aask");
  screen->display();
  delay(3000);
}
