/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

int motor = 9;

void setup() {
    pinMode(motor, OUTPUT);
}

void loop() {
    for (int i = 0; i <= 255; i+=10) {
        analogWrite(motor, i);
        delay(500);
    }
    for (int i = 255; i >= 0; i-=10) {
        analogWrite(motor, i);
        delay(500);
    }
}
