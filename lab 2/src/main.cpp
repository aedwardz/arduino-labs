#include <Arduino.h>
#define GREEN_PIN 12
#define YELLOW_PIN 33
#define RED_PIN 25
#define BUZZER_PIN 13
#define BUTTON_PIN 15

// put function declarations here:
#define RED_STATE 0
#define RED_YELLOW_STATE 1
#define YELLOW_STATE 2
#define GREEN_STATE 3
#define RED_MILLIS 10000
#define YELLOW_MILLIS 2000
#define GREEN_MILLIS 5000

int tl_state; // Traffic light state.
unsigned long tl_timer; // Traffic light timer.
int buttonState;  // Button state.

void setup(){
// Configure LED pins as outputs.
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  // Initial state for states and timers..
  tl_state = RED_STATE;
  tl_timer = millis() + RED_MILLIS;
}
void loop(){
  buttonState = digitalRead(BUTTON_PIN);

  // TL state machine
  switch (tl_state){
    case RED_STATE:
    // Turn red light on.
    digitalWrite(RED_PIN, HIGH);
    // Activate buzzer.
    tone(BUZZER_PIN, 440);
    delay(250);
    noTone(BUZZER_PIN);
    delay(250);

    if (millis() >= tl_timer){
      // Turn red light off.
      digitalWrite(RED_PIN, LOW);
      // Set timer for red-yellow state.
      tl_state = RED_YELLOW_STATE;
      tl_timer = millis() + YELLOW_MILLIS;
    }
    break;
    
    case RED_YELLOW_STATE:
    // Code for red-yellow state.
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, HIGH);

    if (millis() >= tl_timer){
      digitalWrite(RED_PIN, LOW);
      digitalWrite(YELLOW_PIN, LOW);
      tl_state = GREEN_STATE;
      tl_timer = millis() + GREEN_MILLIS;
    }
    break;

    case YELLOW_STATE:
    // Code for yellow state.
    digitalWrite(YELLOW_PIN, HIGH);

     if (millis() >= tl_timer){
      digitalWrite(YELLOW_PIN, LOW);
      tl_state = RED_STATE;
      tl_timer = millis() + RED_MILLIS;
    }
    break;

    case GREEN_STATE:
    // Turn green light on. 
    digitalWrite(GREEN_PIN, HIGH);

    // Activate buzzer
    tone(BUZZER_PIN, 523);
    delay(500);
    noTone(BUZZER_PIN);
    delay(1500);

    if (buttonState == LOW){
      delay(500);
      // Turn green light off.
      digitalWrite(GREEN_PIN, LOW);

      // Set timer for yellow state.
      tl_state = YELLOW_STATE;
      tl_timer = millis() + YELLOW_MILLIS;

    }
  }
}