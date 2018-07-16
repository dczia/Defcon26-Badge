#include "dczia26_oled.h"

SSD1306* oled_setup(void)
{
 // Use the corresponding display class:

 // Initialize the OLED display using SPI
 // D5 -> CLK
 // D7 -> MOSI (DOUT)
 // D0 -> RES
 // D2 -> DC
 // D8 -> CS
 // SSD1306Spi        display(D0, D2, D8);
 // or
 // SH1106Spi         display(D0, D2);

 // Initialize the OLED display using brzo_i2c
 // D3 -> SDA
 // D5 -> SCL
 // SSD1306Brzo display(0x3c, D3, D5);
 // or
 // SH1106Brzo  display(0x3c, D3, D5);

 // Initialize the OLED display using Wire library
 // SH1106 display(0x3c, D3, D5);

  SSD1306* screen = NULL;

  screen = new SSD1306(0x3c, 5, 4);
  screen->init();
  screen->flipScreenVertically();
  screen->setContrast(255);

  // Initialize the log buffer
  // allocate memory to store 8 lines of text and 25 chars per line.
  screen->setLogBuffer(5, 25);

  screen->clear();

  return(screen);
}


void oled_welcome(SSD1306 *screen)
{
  screen->clear();
  screen->println("Welcome, dczia..");
  screen->println("main_menu() starts in 5..");
  screen->drawLogBuffer(0, 0);
  screen->display();
  delay(250);
  screen->clear();
  screen->print("4..");
  screen->drawLogBuffer(0, 0);
  screen->display();
  delay(250);
  screen->clear();
  screen->print("3..");
  screen->drawLogBuffer(0, 0);
  screen->display();
  delay(250);
  screen->clear();
  screen->print("2..");
  screen->drawLogBuffer(0, 0);
  screen->display();
  delay(250);
  screen->clear();
  screen->print("1..");
  screen->drawLogBuffer(0, 0);
  screen->display();
  delay(250);
}


// Adapted from Adafruit_SSD1306
void oled_drawLines(SSD1306 *screen) {
  for (int16_t i=0; i<DISPLAY_WIDTH; i+=4) {
    screen->drawLine(0, 0, i, DISPLAY_HEIGHT-1);
    screen->display();
    delay(10);
  }
  for (int16_t i=0; i<DISPLAY_HEIGHT; i+=4) {
    screen->drawLine(0, 0, DISPLAY_WIDTH-1, i);
    screen->display();
    delay(10);
  }
  delay(250);

  screen->clear();
  for (int16_t i=0; i<DISPLAY_WIDTH; i+=4) {
    screen->drawLine(0, DISPLAY_HEIGHT-1, i, 0);
    screen->display();
    delay(10);
  }
  for (int16_t i=DISPLAY_HEIGHT-1; i>=0; i-=4) {
    screen->drawLine(0, DISPLAY_HEIGHT-1, DISPLAY_WIDTH-1, i);
    screen->display();
    delay(10);
  }
  delay(250);

  screen->clear();
  for (int16_t i=DISPLAY_WIDTH-1; i>=0; i-=4) {
    screen->drawLine(DISPLAY_WIDTH-1, DISPLAY_HEIGHT-1, i, 0);
    screen->display();
    delay(10);
  }
  for (int16_t i=DISPLAY_HEIGHT-1; i>=0; i-=4) {
    screen->drawLine(DISPLAY_WIDTH-1, DISPLAY_HEIGHT-1, 0, i);
    screen->display();
    delay(10);
  }
  delay(250);
  screen->clear();
  for (int16_t i=0; i<DISPLAY_HEIGHT; i+=4) {
    screen->drawLine(DISPLAY_WIDTH-1, 0, 0, i);
    screen->display();
    delay(10);
  }
  for (int16_t i=0; i<DISPLAY_WIDTH; i+=4) {
    screen->drawLine(DISPLAY_WIDTH-1, 0, i, DISPLAY_HEIGHT-1);
    screen->display();
    delay(10);
  }
  delay(250);
}

// Adapted from Adafruit_SSD1306
void oled_drawRect(SSD1306 *screen) {
  for (int16_t i=0; i<DISPLAY_HEIGHT/2; i+=2) {
    screen->drawRect(i, i, DISPLAY_WIDTH-2*i, DISPLAY_HEIGHT-2*i);
    screen->display();
    delay(10);
  }
}

//draw zia
void oled_drawZia(SSD1306 *screen) {
     
  for (int16_t i=0; i<DISPLAY_WIDTH-DISPLAY_HEIGHT; ++i) {
    screen->clear();
    screen->drawFastImage(i, 0, 64, 64, zia);
    screen->display();
    delay(10);
  }
  
  for (int16_t i=0; i<DISPLAY_WIDTH-DISPLAY_HEIGHT; ++i) {
    screen->clear();
    screen->drawFastImage(DISPLAY_WIDTH-DISPLAY_HEIGHT-i, 0, 64, 64, zia);
    screen->display();
    delay(10);
  }
}

// Adapted from Adafruit_SSD1306
void oled_fillRect(SSD1306 *screen) {
  uint8_t color = 1;
  for (int16_t i=0; i<DISPLAY_HEIGHT/2; i+=3) {
    screen->setColor((color % 2 == 0) ? BLACK : WHITE); // alternate colors
    screen->fillRect(i, i, DISPLAY_WIDTH - i*2, DISPLAY_HEIGHT - i*2);
    screen->display();
    delay(10);
    color++;
  }
  // Reset back to WHITE
  screen->setColor(WHITE);
}

// Adapted from Adafruit_SSD1306
void oled_drawCircle(SSD1306 *screen) {

  

  for (int16_t i=0; i<DISPLAY_HEIGHT; i+=2) {
    screen->drawCircle(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, i);
    screen->display();
    delay(10);
  }
  delay(1000);
  screen->clear();

  // This will draw the part of the circel in quadrant 1
  // Quadrants are numberd like this:
  //   0010 | 0001
  //  ------|-----
  //   0100 | 1000
  //
  screen->drawCircleQuads(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, DISPLAY_HEIGHT/4, 0b00000001);
  screen->display();
  delay(200);
  screen->drawCircleQuads(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, DISPLAY_HEIGHT/4, 0b00000011);
  screen->display();
  delay(200);
  screen->drawCircleQuads(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, DISPLAY_HEIGHT/4, 0b00000111);
  screen->display();
  delay(200);
  screen->drawCircleQuads(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, DISPLAY_HEIGHT/4, 0b00001111);
  screen->display();
}

