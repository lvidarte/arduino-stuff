/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */


#define STEPS_PER_REVOLUTION 512
#define MOTOR_SPEED 1200
#define MSECS 2000

int motorPins[4] = {6, 7, 8, 9};
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

void setup() {
    for (int i = 0; i <= 3; i++) {
        pinMode(motorPins[i], OUTPUT);
    }
}

void loop() {
    moveSteps(STEPS_PER_REVOLUTION);
    delay(MSECS);
    moveSteps(-STEPS_PER_REVOLUTION);
    delay(MSECS);
}

void moveSteps(int steps) {
    int i;
    if (steps > 0) {
        for (i = 0; i < steps; i++) {
            moveClockWise();
        }
    }
    if (steps < 0) {
        for (i = steps; i <= 0; i++) {
            moveAntiClockWise();
        }
    }
}

void moveClockWise() {
    for (int j = 7; j >= 0; j--) {
        setMotor(j);
        delayMicroseconds(MOTOR_SPEED);
    }
}

void moveAntiClockWise() {
    for (int j = 0; j <= 7; j++) {
        setMotor(j);
        delayMicroseconds(MOTOR_SPEED);
    }
}

void setMotor(int j) {
    for (int i = 0; i < 4; i++) {
        digitalWrite(motorPins[i], bitRead(lookup[j], i));
    }
}
