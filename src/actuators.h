#ifndef ACTUATORS_H
#define ACTUATORS_H

#include <Servo.h>

// Initialiserer servo og LED
void setupActuators();

// Sætter servo position (0-180 grader)
void setServo(int angle);

// Tænder/slukker LED
void setLED(bool on);

// Henter aktuel servo position
int getServoPosition();

// Henter LED status
bool getLEDState();

#endif
