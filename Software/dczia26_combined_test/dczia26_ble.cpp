#include "dczia26_ble.h"
#include "sys/time.h"

RTC_DATA_ATTR static time_t last;        // remember last boot in RTC Memory
RTC_DATA_ATTR static uint32_t bootcount; // remember number of boots in RTC Memory

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

BLEAdvertising *pAdvertising;
struct timeval now;



void setBeacon() {

  BLEBeacon oBeacon = BLEBeacon();
  oBeacon.setManufacturerId(DCZIA_MFG_ID);
  oBeacon.setProximityUUID(BLEUUID(BEACON_UUID));
  oBeacon.setMajor((bootcount & 0xFFFF0000) >> 16);
  oBeacon.setMinor(bootcount&0xFFFF);
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  BLEAdvertisementData oScanResponseData = BLEAdvertisementData();
  
  oAdvertisementData.setFlags(0x04); // BR_EDR_NOT_SUPPORTED 0x04
  
  std::string strServiceData = "";
  
  strServiceData += (char)26;     // Len
  strServiceData += (char)0xFF;   // Type
  strServiceData += oBeacon.getData(); 

  oAdvertisementData.setName("DCZia26");
  oAdvertisementData.addData(strServiceData);
  oAdvertisementData.setAppearance(APPEARANCE_DC26);
  
  //Response Data doesn't need a name
  oScanResponseData.addData(strServiceData);
  oScanResponseData.setAppearance(APPEARANCE_DC26);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  
}

void ble_setup() {
  Serial.begin(115200);
  gettimeofday(&now, NULL);

  Serial.printf("start ESP32 %d\n",bootcount++);

  Serial.printf("deep sleep (%lds since last reset, %lds since last boot)\n",now.tv_sec,now.tv_sec-last);

  last = now.tv_sec;
  
  // Create the BLE Device
  BLEDevice::init("DCZia26");

  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();

  pAdvertising = pServer->getAdvertising();
  
  setBeacon();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pService->start();
   // Start advertising
  pAdvertising->start();
  Serial.println("Advertising started...");
  delay(100);
  
}

void ble_loop() {

}
