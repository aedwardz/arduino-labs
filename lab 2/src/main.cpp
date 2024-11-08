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

int tl_state; // Traffic light state.
unsigned long tl_timer; // Traffic light timer.
int buttonState = 0;
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
  // tone(BUZZER_PIN, 440);
  // if (buttonState == HIGH){
    
  //   digitalWrite(GREEN_PIN, LOW);
  //   digitalWrite(RED_PIN, LOW);
  //   digitalWrite(YELLOW_PIN, LOW);
  // }
  // if (buttonState == LOW){
  //   // tone(BUZZER_PIN, 440);
  //   digitalWrite(GREEN_PIN, HIGH);
  //   digitalWrite(RED_PIN, HIGH);
  //   digitalWrite(YELLOW_PIN, HIGH);
  // }
  // TL state machine
  switch (tl_state){
    case RED_STATE:
    // Turn red light on.
    digitalWrite(RED_PIN, HIGH);
    if (/*Timer expired*/){
      // Turn red light off.
      digitalWrite(RED_PIN, LOW);
      // Set timer for red-yellow state.
      tl_state = RED_YELLOW_STATE;
    }
    break;
    case RED_YELLOW_STATE:
    // Code for red-yellow state.
    break;
    case YELLOW_STATE:
    // Code for yellow state.
    break;
    case GREEN_STATE:
    // Turn green light on.
    if (/*Timer expired AND touch-button was pressed*/){
      // Turn green light off.
      // Set timer for yellow
      state.tl_state = YELLOW_STATE;
    }
    break;
  }
  // Detect touch - button pressed.
  // Buzzer state machine.
  // .
  // .
}
