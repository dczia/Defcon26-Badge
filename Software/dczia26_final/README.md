# dczia26_final

This is it.

## Overview
DC Zia 26 - 2018 Final Build Out.
This should cover what is required for building and loading the sketch onto the DC Zia badge.

### Required Libraries
- Espressif ESP32 - [ESP32 Setup Instructions](https://github.com/espressif/arduino-esp32#installation-instructions) 

### Arduino Installable Libraries
- Adafruit SSD1306 OLED Library
- Adafruit GDX Library
- Neopixel BUS Library
- Keypad (http://playground.arduino.cc/Code/Keypad)

## Build Instructions
Make sure you're running a recent version of Arduino Studio. 
Follow the instructions for installing Espressif ESP32 boards.  There's a lot in there, so make sure you go through each step.  Make sure that you're using a version newer than June 2018 as there's BLE library changes which are required for building.

Open `dczia_final.ino` in Arduino Studio.
Select the correct board:
	- TOOLS -> Board -> WEMOS LOLIN32
Select the connected COM port (should be autodetected).
Compile the sketch using the checkmark.
Upload the sketch to the board.
Enjoy the lightshow.

### Troubleshooting
- Fails to compile
	- Double check that Espressif ESP32 is installed correctly
	- Review all required libraries and make sure they're installed
	- Review errors to identify if it is a board issue vs a library issue.
- Fails to upload
	- Double check to make sure Espressif python tools were fully configured.
	- Make sure the badge is connected and on (reconnect with badge switched to ON without batteries)
- Display issues
	- Make sure you're using Adafruit libraries and it is configured for `128x32`


