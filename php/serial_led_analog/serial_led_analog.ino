/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#define LED 10


void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        int value = (int) Serial.read();
        // 0 - 9 (ascii 48 - 57)
        int brightness = map(value, 48, 57, 0, 255);
        Serial.println(value, DEC);
        Serial.println(brightness, DEC);
        analogWrite(LED, brightness);
    }
}
