/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

/**
 *  Connect leds on 3, 6, 9, 11
 *  Connect switches on 2, 4, 7, 8
 */

const int totalLeds = 4;
int leds[] = {11, 9, 6, 3};
int buttons[] = {8, 7, 4, 2};
int states[] = {LOW, LOW, LOW, LOW};
boolean changed;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < totalLeds; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < totalLeds; i++) {
        changed = false;
        while(digitalRead(buttons[i]) == HIGH) {
            if (!changed) {
                states[i] = (states[i] == HIGH) ? LOW : HIGH;
                digitalWrite(leds[i], states[i]);
                changed = true;
            }
        }
    }
    delay(10);
}

