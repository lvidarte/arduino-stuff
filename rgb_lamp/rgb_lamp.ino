/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#define T_STEP 25
#define T_CHANGE 20000

#define RED 11
#define GREEN 10
#define BLUE 9

int pins[] = {RED, GREEN, BLUE};
int valuePins[] = {0, 0, 0};


void setup() {
    randomSeed(analogRead(0));
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
}

void changeColor(int i, int value) {
    int j;
    if (value > valuePins[i]) {
        for (j = valuePins[i]; j <= value; j++) {
            analogWrite(pins[i], j);
            delay(T_STEP);
        }
    }
    if (value < valuePins[i]) {
        for (j = valuePins[i]; j >= value; j--) {
            analogWrite(pins[i], j);
            delay(T_STEP);
        }
    }
}

void loop() {
    int i, value;
    for (i = 0; i <= 2; i++) {
        value = random(256);
        changeColor(i, value);
        valuePins[i] = value;
    }
    delay(T_CHANGE);
}
