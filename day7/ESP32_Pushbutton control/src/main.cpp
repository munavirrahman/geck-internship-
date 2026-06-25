#include <Arduino.h> // Required for PlatformIO

// Define pins
const int SWITCH_PIN = 12; 
const int LED_PIN = 1; // Standard built-in LED pin for ESP32

void setup() {
  // Configure the switch pin with the internal pull-up resistor
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // Configure the built-in LED as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read the state of the switch
  int switchState = digitalRead(SWITCH_PIN);

  // INPUT_PULLUP Logic:
  // LOW (0) = Switch is Pressed (connected to GND)
  // HIGH (1) = Switch is Released
  if (switchState == LOW) {
    digitalWrite(LED_PIN, HIGH);   // Turn the built-in LED ON
  } else {
    digitalWrite(LED_PIN, LOW);    // Turn the built-in LED OFF
  }

  delay(20); // Small delay to handle button bouncing
}