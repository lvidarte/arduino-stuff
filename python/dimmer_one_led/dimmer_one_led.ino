/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

int led = 9;
int brightness = 0;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        brightness = (int) Serial.read();
        //Serial.println(brightness, DEC);
        analogWrite(led, brightness);
    }
}
