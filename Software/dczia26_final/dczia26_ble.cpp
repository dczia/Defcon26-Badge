#include "dczia26_ble.h"
#include "dczia26_sd.h"
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

int dc26Badges;
int dcZiaBadges;
int foundDevicesCount;

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
  delay(10);
  
}

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
      SDRecordBLE(advertisedDevice.toString().c_str());
      if(advertisedDevice.getAppearance() == APPEARANCE_DC26) {
        Serial.printf("*** DC26!!\n");
        dc26Badges = dc26Badges + 1;
        if(advertisedDevice.getName() == "DCZia26") {
          Serial.printf("*** DCZia!!\n");
          dcZiaBadges = dcZiaBadges + 1;
        }
      }
    }
};

void ble_scan_dczia(int bleScanCount[]) { 
  dc26Badges = 0;
  dcZiaBadges = 0;
  foundDevicesCount = 0;
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(BLE_SCAN_TIME);
  bleScanCount[0] = dc26Badges;
  bleScanCount[1] = dcZiaBadges;
  bleScanCount[2] = foundDevices.getCount();
  //Serial Information
  Serial.print("Devices found: ");
  Serial.println(foundDevices.getCount());
  Serial.println("DC26 Badges: ");
  Serial.println(dc26Badges);
  Serial.println("DCZia Badges: ");
  Serial.println(dcZiaBadges);
  Serial.println("Scan done!");
} 
