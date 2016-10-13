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
        char incomingByte = Serial.read();
        Serial.println(incomingByte);
        if (incomingByte == '1') {
            digitalWrite(LED, HIGH);
        }
        if (incomingByte == '0') {
            digitalWrite(LED, LOW);
        }
    }
}
