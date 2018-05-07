#include "dczia26_keypad.h"

//
//  Col 0 doesn't work on Proto DOS if OLED is also in use ... but it compiles okay... :)
//
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {KEY_R0C0, KEY_R0C1, KEY_R0C2, KEY_R0C3},
  {KEY_R1C0, KEY_R1C1, KEY_R1C2, KEY_R1C3},
  {KEY_R2C0, KEY_R2C1, KEY_R2C2, KEY_R2C3},
  {KEY_R3C0, KEY_R3C1, KEY_R3C2, KEY_R3C3}
};
byte rowPins[ROWS] = {16,  0,  2, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 12, 13, 15}; //connect to the column pinouts of the keypad


Keypad* keypad_setup(void)
{
  Keypad* keypd = NULL;
  // initialize an instance of class NewKeypad
  keypd = new Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
  return(keypd);
}


