#pragma once

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include <Adafruit_SSD1306.h>


// pin out
/*const byte SPI_CLK = 30;
const byte SPI_MISO = 31;
const byte SPI_MOSI = 37;
const byte SD_CS = 29;  */

void SDSetup(Adafruit_SSD1306*);
void SDRecordBLE(const char* ble_ID);
void writeData(const char * path, const char * message);

