#include "dczia26_sd.h"

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

static int sd_init_success = false;

void SDSetup(Adafruit_SSD1306 *screen) {
    Serial.begin(115200);
    if(!SD.begin()){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);
    sd_init_success = true;  
    
    writeData("/testFile", "data data data");
}

void writeData(const char * path, const char * message){
  if (! sd_init_success)
    return;
    Serial.printf("Trying Writing file: %s\n", path);

    File file = SD.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
         file = SD.open(path, FILE_WRITE);
         if(!file){
            Serial.println("Failed to open file for writing");
            return;
          }
    }
    if(file.println(message)){
        Serial.println("File written with data");
        Serial.println(message);
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void SDRecordBLE(const char* ble_ID) {
  writeData("/ble_ids.txt", ble_ID);
}

