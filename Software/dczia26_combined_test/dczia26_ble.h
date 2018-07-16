#pragma once

#include "Arduino.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEAdvertising.h>
#include <BLEAdvertisedDevice.h>
#include <BLEBeacon.h>


#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"
#define BEACON_UUID           "8ec76ea3-6668-48da-9866-75be8bc86f4d" // UUID 1 128-Bit (may use linux tool uuidgen or random numbers via https://www.uuidgenerator.net/)

#define APPEARANCE_DC26 0x26DC
#define APPEARANCE_DC25 0x19DC

#define DCZIA_MFG_ID 0x5050
#define SHOTBOT_MFG_ID 0x5150

#define GPIO_DEEP_SLEEP_DURATION     10  // sleep x seconds and then wake up

void ble_setup(void);
void ble_loop(void);
