#include "actuators.h"
#include "config.h"
#include <Arduino.h>

Servo myServo;
int currentServoPos = 0;
bool ledState = false;

void setupActuators() {
  // LED setup
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  // Servo setup
  myServo.attach(SERVO_PIN);
  myServo.write(0);
  
  Serial.println("Actuators initialized");
}

void setServo(int angle) {
  if (angle >= 0 && angle <= 180) {
    myServo.write(angle);
    currentServoPos = angle;
    Serial.print("Servo set to: ");
    Serial.println(angle);
  }
}

void setLED(bool on) {
  ledState = on;
  digitalWrite(LED_PIN, on ? HIGH : LOW);
  Serial.print("LED: ");
  Serial.println(on ? "ON" : "OFF");
}

int getServoPosition() {
  return currentServoPos;
}

bool getLEDState() {
  return ledState;
}
