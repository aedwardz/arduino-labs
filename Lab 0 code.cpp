#include <Arduino.h>
#include <Servo.h>
Servo myServo;

// servo pin = 32
int ledPin = 2;
int servoPin = 27;
int photoCellPin = 32;
int photocellReading;
// put function declarations here


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  myServo.attach(servoPin);
  pinMode(photoCellPin, INPUT);
}
// Servo pin
void loop() {

  int max = -999999999;
  int min = 9999999999;
  
  Serial.println("Calibrating...");
  for (int i = 0; i < 10; i++){
    if (i % 2 == 0){
      digitalWrite(ledPin, HIGH);
    }
    else{
      digitalWrite(ledPin, LOW);
    }
      photocellReading = analogRead(photoCellPin);
      if (photocellReading < min){
        min = photocellReading;
        Serial.print("Min: ");
        Serial.println(min);
      }
      else if (photocellReading > max){
        max = photocellReading;
        Serial.print("Max: ");
        Serial.println(max);
      }
      delay(1000);
  }
  Serial.println("Done!");
  Serial.print("Min: ");
  Serial.println(min);
  Serial.print("Max: ");
  Serial.println(max);
  digitalWrite(ledPin, LOW);

  Serial.println("Operating...");
  for (int i = 0; i < 20; i++){
   
      photocellReading = analogRead(photoCellPin);
      
      int angle = map(photocellReading, min,max, 0, 179);
      Serial.print(angle);
      Serial.println(" degrees");
      myServo.write(angle);

      delay(1000);
  }
  Serial.print("Done!");
    delay(999999999);

  
  // put your main code here, to run repeatedly:
  // Serial.print("Hello");
  // delay(1000);

  // digitalWrite(ledPin, HIGH);
  // myServo.write(0);
  // Serial.print(0);
  // delay(1000);
  // myServo.write(90);
  // Serial.print(90);
  // delay(1000);

}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}