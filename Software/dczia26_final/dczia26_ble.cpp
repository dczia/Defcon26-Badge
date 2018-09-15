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

Adafruit_SSD1306   *screen = NULL;

BLEAdvertising *pAdvertising;
BLEScan* pBLEScan;
BLECharacteristic *pCharacteristic;
BLEService *pService;
BLEServer *pServer;

struct timeval now;

//may need to be in a vector later
BLERemoteService *pRemoteService;
BLERemoteCharacteristic *pRemoteCharacteristic;
BLEClient *pClient;
BLEAddress *pServerAddress;

int dc26Badges;
int dcZiaBadges;
int foundDevicesCount;

bool connected = false;
bool doConnect = false;

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

  oAdvertisementData.setName(BADGE_NAME);
  oAdvertisementData.addData(strServiceData);
  oAdvertisementData.setAppearance(APPEARANCE_DC26);
  
  //Response Data doesn't need a name
  oScanResponseData.addData(strServiceData);
  oScanResponseData.setAppearance(APPEARANCE_DC26);
  
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->setScanResponseData(oScanResponseData);
  
}

void ble_setup(Adafruit_SSD1306   *oled) {
  Serial.begin(115200);
  gettimeofday(&now, NULL);

  Serial.printf("start ESP32 %d\n",bootcount++);

  Serial.printf("deep sleep (%lds since last reset, %lds since last boot)\n",now.tv_sec,now.tv_sec-last);

  last = now.tv_sec;
  
  // Create the BLE Device
  BLEDevice::init("DCZia26");

  // Create the BLE Server
  pServer = BLEDevice::createServer();

  pAdvertising = pServer->getAdvertising();
  
  setBeacon();
  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                              CHARACTERISTIC_UUID_RX,
                              BLECharacteristic::PROPERTY_READ |
                              BLECharacteristic::PROPERTY_WRITE);
  pCharacteristic->setValue("Come to the dark side... we have cookies");
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  
  // Start advertising
  pAdvertising->start();
  Serial.println("Advertising started...");
  delay(10);

  screen = oled;
}
class EmptyCallback: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) { 
      SDRecordBLE(advertisedDevice.toString().c_str());
  } // onResult
}; // MyAdvertisedDeviceCallbacks

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
          pServerAddress = new BLEAddress(advertisedDevice.getAddress());
          doConnect = true;
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

void ble_client() { 
  if(!connected && doConnect)
    connected = ble_clientConnect(pServerAddress);
  if(connected)
    ble_clientReport();
}

bool ble_clientConnect(BLEAddress * pAddress) {
  screen->clearDisplay();
  screen->setCursor(0, 0);
  screen->println("CONNECTING!");

  String tmp = String(pAddress->toString().c_str());
  tmp = String("Server Address: " + tmp);
  screen->println(tmp);
  
  Serial.print("Connecting to ");
  Serial.println(pAddress->toString().c_str());

  pClient  = BLEDevice::createClient();
  pClient->connect(*pAddress);
  
  pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(SERVICE_UUID.toString().c_str());
      return false;
  }

  pRemoteCharacteristic = pRemoteService->getCharacteristic(BEACON_UUID);
  if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(BEACON_UUID.toString().c_str());
      return false;
  }

  ble_clientReport();
  screen->display();
  return true;
}

//prints charateristic message from another server
void ble_clientWrite(char* mesg) {
  screen->clearDisplay();
  screen->setCursor(0, 0);
  if(pRemoteCharacteristic->canWrite())
  {
    screen->println("Writing client value");
    pRemoteCharacteristic->writeValue(mesg);
    screen->println(mesg);
  }
  else
    screen->println("Cannot write server value");
  screen->display();
}

//prints charateristic message from another server
void ble_clientReport() {
  screen->clearDisplay();
  screen->setCursor(0, 0);
  if(pRemoteCharacteristic->canRead())
  {
    screen->println("Reading server value");
    std::string value = pRemoteCharacteristic->readValue();
    screen->println(value.c_str());
  }
  else
    screen->println("Cannot read server value");
  screen->display();
}

// prints charateristic message from this server
void print_charateristic_msg() {
  screen->clearDisplay();
  screen->setCursor(0, 0);
  String tmp = String(pCharacteristic->getValue().c_str());
  screen->println(tmp);
  screen->display();
}

std::string string_to_hex(const std::string& input) {
  static const char* hex_values = "0123456789ABCDEF";

  std::string output;
  output.reserve(2*input.size()+2);
  output.push_back('0');
  output.push_back('x');
  
  for(const unsigned char c : input) 
  {
    output.push_back(hex_values[c >> 4]);
    output.push_back(hex_values[c & 15]);
  }
  return output;
}

