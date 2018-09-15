#pragma once

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEAdvertising.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>
#include <Adafruit_SSD1306.h>

#define BADGE_NAME "DCZia26"

static BLEUUID SERVICE_UUID           ("6E400001-B5A3-F393-E0A9-E50E24DCCA9E"); // UART service UUID
static BLEUUID CHARACTERISTIC_UUID_RX ("6E400002-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID CHARACTERISTIC_UUID_TX ("6E400003-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID BEACON_UUID            ("8ec76ea3-6668-48da-9866-75be8bc86f4d"); // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)

#define APPEARANCE_DC26 0x26DC
#define APPEARANCE_DC25 0x19DC

#define DCZIA_MFG_ID 0x5050
#define SHOTBOT_MFG_ID 0x5150

#define GPIO_DEEP_SLEEP_DURATION     5  // sleep x seconds and then wake up

const int BLE_SCAN_TIME = 10; // 10 seconds

#define DELAY 100

void ble_setup(Adafruit_SSD1306   *oled);
void ble_scan_dczia(int bleScanCount[]);
void ble_client();
bool ble_clientConnect(BLEAddress * pAddress);
void ble_clientWrite(char* mesg);
void ble_clientReport();
void print_charateristic_msg();
std::string string_to_hex(const std::string& input);
