#include <Arduino.h>
#include <HttpClient.h>
#include <WiFi.h>
#include <inttypes.h>
#include <stdio.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <SparkFun_STHS34PF80_Arduino_Library.h>

char ssid[50]; // Network SSID
char pass[50]; // Network Password

// Number of milliseconds to wait without receiving any data before we give up
const int kNetworkTimeout = 30 * 1000;
// Number of milliseconds to wait if no data is available before trying again
const int kNetworkDelay = 1000;

void nvs_access() {
  // Initialize NVS
  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES ||
  err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
  // NVS partition was truncated and needs to be erased
  // Retry nvs_flash_init
  ESP_ERROR_CHECK(nvs_flash_erase());
  err = nvs_flash_init();
  }
ESP_ERROR_CHECK(err);

// Open
Serial.printf("\n");
Serial.printf("Opening Non-Volatile Storage (NVS) handle... ");
nvs_handle_t my_handle;
err = nvs_open("storage", NVS_READWRITE, &my_handle);
if (err != ESP_OK) {
  Serial.printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
} else {
  Serial.printf("Done\n");
  Serial.printf("Retrieving SSID/PASSWD\n");
  size_t ssid_len;
  size_t pass_len;
  err = nvs_get_str(my_handle, "ssid", ssid, &ssid_len);
  err |= nvs_get_str(my_handle, "pass", pass, &pass_len);
  switch (err) {
    case ESP_OK:
    Serial.printf("Done\n");
    break;
    case ESP_ERR_NVS_NOT_FOUND:
    Serial.printf("The value is not initialized yet!\n");
    break;
    default:
    Serial.printf("Error (%s) reading!\n", esp_err_to_name(err));
  }
}
// Close
nvs_close(my_handle);
}

STHS34PF80_I2C mySensor;

// Values to fill with presence and motion data
int16_t presenceVal = 0;
int16_t motionVal = 0;
float temperatureVal = 0;
int ledPin1 = 26;
int ledPin2 = 25;
int ledPin3 = 33;
int ledPin4 = 32;
int ledPin5 = 27;

int threshold = 1000;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  Serial.begin(9600);

    // Begin I2C
    if(Wire.begin() == 0)
    {
      Serial.println("I2C Error - check I2C Address");
      while(1);
    }

    // Establish communication with device 
    if(mySensor.begin() == false)
    {
      Serial.println("Error setting up device - please check wiring.");
      while(1);
    }

    // Retrieve SSID/PASSWD from flash before anything else
    nvs_access();

    // Connect to WiFi network
    delay(1000);
    Serial.println();
    Serial.println();
    // Serial.println(WiFi.macAddress());
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("MAC address: ");
    Serial.println(WiFi.macAddress());
}

void loop() {
  char url[256];

  // snprintf(url, sizeof(url), "/?var=%f,%f", humidity.relative_humidity, temp.temperature);

  int err = 0;

  WiFiClient c;
  HttpClient http(c);
  

  sths34pf80_tmos_drdy_status_t dataReady;
  mySensor.getDataReady(&dataReady);

  // Check whether sensor has new data - run through loop if data is ready
  if(dataReady.drdy == 1)
  {
    sths34pf80_tmos_func_status_t status;
    mySensor.getStatus(&status);
    
    // If presence flag is high, then print data
    if(status.pres_flag == 1)
    {
      // Presence Units: cm^-1
      mySensor.getPresenceValue(&presenceVal);
      Serial.print("Presence: ");
      Serial.print(presenceVal);
      Serial.println(" cm^-1");     
      
      if (presenceVal > threshold){
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
        digitalWrite(ledPin4, HIGH);
        digitalWrite(ledPin5, HIGH);
        }
      else{
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(ledPin4, LOW);
        digitalWrite(ledPin5, LOW);
      }
      
    }
    else{

      presenceVal = 0;
      Serial.print(presenceVal);
    }


    
  }

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}