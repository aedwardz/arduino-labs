#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "SparkFunLSM6DSO.h"
#include <limits>
#include <string>

#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"

int ledPin = 25;
LSM6DSO myIMU;
float x;
float y;
float threshold;
int steps = 0;


BLECharacteristic *pCharacteristic;

class MyCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
  std::string value = pCharacteristic->getValue();
  // if (value.length() > 0) {
  //   Serial.println("*********");
  //   Serial.print("New value: ");
  //   for (int i = 0; i < value.length(); i++)
  //     Serial.print(value[i]);
  //     Serial.println();
  //     Serial.println("*********");
  // }
  if (value == "on"){
    digitalWrite(ledPin, HIGH);
    Serial.println("Turning on LED");
  }
  if (value == "off"){
    digitalWrite(ledPin, LOW);
    Serial.println("Turning off LED");
  }
  }
};
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to MyESP32");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");
  BLEDevice::init("MyESP32-group 59");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
  CHARACTERISTIC_UUID,
  BLECharacteristic::PROPERTY_READ |
  BLECharacteristic::PROPERTY_WRITE
);
pCharacteristic->setCallbacks(new MyCallbacks());
pCharacteristic->setValue("Hello World");

pService->start();
BLEAdvertising *pAdvertising = pServer->getAdvertising();
pAdvertising->start();

//Set up accelarometer
Wire.begin();
  delay(10);
  if( myIMU.begin() )
    Serial.println("Ready.");
  else { 
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
  }

  if( myIMU.initialize(BASIC_SETTINGS) )
    Serial.println("Loaded Settings.");

//calibrate phase
float xMax = -std::numeric_limits<float>::infinity();
float yMax = -std::numeric_limits<float>::infinity();
Serial.println("Calibrating...");
for (int i = 0; i < 10; i++){
  x = myIMU.readFloatAccelX();
  y = myIMU.readFloatAccelY();
  if (x > xMax){
    xMax = x;
      }
  if (y > yMax){
    yMax = y;
      }
  delay(1000);

}
threshold = sqrt(pow(xMax, 2) + pow(yMax, 2));
Serial.println(threshold);
}
void loop() {
  // 
  // pCharacteristic->notify();
  x = myIMU.readFloatAccelX();
  y = myIMU.readFloatAccelY();

  // Serial.print("\nAccelerometer:\n");
  // Serial.print(" X = ");

  // Serial.println(x, 3);
  // Serial.print(" Y = ");
  // Serial.println(y, 3);

  float rms = sqrt(pow(x, 2) + pow(y, 2));

  if (rms >= threshold){
    steps++;
    char stepString[20];
    snprintf(stepString, sizeof(stepString), "steps: %d", steps);

    pCharacteristic->setValue((uint8_t*)stepString, strlen(stepString));
    Serial.println(stepString);
    
  }
  
  delay(1000);
}