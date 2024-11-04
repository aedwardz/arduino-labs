#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include <Adafruit_CAP1188.h>

int mosiPin = 32;
int misoPin = 33;
int clkPin = 25;
int csPin  = 26;
int resetPin = 9;
Adafruit_CAP1188 cap = Adafruit_CAP1188(clkPin, misoPin, mosiPin, csPin, resetPin);
TFT_eSPI tft = TFT_eSPI();
int addy = 0x29;

void setup() {
  Serial.begin(9600);
  Wire.begin();
 
 //tft initializations
  tft.init();              
  tft.setRotation(1);      
  tft.fillScreen(TFT_BLACK); 
  tft.setTextColor(TFT_WHITE); 
  // tft.drawString("Initialized", 10, 10, 4);


  //touch sensor inits
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!");
}


void loop() {
  int count = 0;
  tft.drawNumber(count, 10, 10, 2);
  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    return;
  }
  
  
  tft.fillScreen(TFT_BLACK);

  for (uint8_t i=0; i<8; i++) {
    if (touched & (1 << i)) {
        count ++;
        Serial.print("C"); Serial.print(i+'1'); Serial.print("\t");
    }
  }

  Serial.println(count);
  tft.drawNumber(count, 10, 10, 2);
  Serial.println();
  delay(250);

  tft.fillScreen(TFT_BLACK);
    // byte error, address;
    // int nDevices;
    // Serial.println("Scanning...");
    // nDevices = 0;
    // for(address = 1; address < 127; address++ ) {
    // Wire.beginTransmission(address);
    // error = Wire.endTransmission();
    // if (error == 0) {
    // Serial.print("I2C device found at address 0x");
    // if (address<16) {
    // Serial.print("0");
    // }
    // Serial.println(address,HEX);
    // nDevices++;
    // }
    // else if (error==4) {
    // Serial.print("Unknow error at address 0x");
    // if (address<16) {
    // Serial.print("0");
    // }
    // Serial.println(address,HEX);
    // }
    // }
    // if (nDevices == 0) {
    // Serial.println("No I2C devices found\n");
    // }
    // else {
    // Serial.println("done\n");
    // }
    // delay(5000);
}