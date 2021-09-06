# dczia26_final

This is it.

## Overview
DC Zia 26 - 2018 Final Build Out.
This should cover what is required for building and loading the sketch onto the DC Zia badge.
You can build the firmware using the arduino .ino sketch, or we now have a binay file that can be uploaded using something like esptool (https://diyprojects.io/esp-easy-flash-firmware-esptool-py-esp8266/)

### Required Libraries
- Espressif ESP32 - [ESP32 Setup Instructions](https://github.com/espressif/arduino-esp32#installation-instructions)
- NeopixelBus
- arduinoFFT
- Adafruit SSD1306 OLED Library
- Adafruit GDX Library
- Neopixel BUS Library
- Keypad (http://playground.arduino.cc/Code/Keypad)

### Build Instructions
Make sure you're running a recent version of Arduino Studio. 
Follow the instructions for installing the Espressif ESP32 boards via the board manager at ([ESP32 Setup Instructions](https://github.com/espressif/arduino-esp32#installation-instructions)).

Open `dczia_final.ino` in Arduino Studio.
Select the correct board:
  - TOOLS -> Board -> ESP 32 Dev Module
Select the connected COM port (should be autodetected).
Compile the sketch using the checkmark.
Upload the sketch to the board.
Enjoy the lightshow.

### Usage of the Badge
The Board will boot into a default light mode. Press and hold the bottom right key to exit the current mode and goto the main menu.
The top 9 buttons each will activate a different mode.
Press and hold the bottom right key to exit the current mode.

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


