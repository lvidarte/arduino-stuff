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
 * Connect a button (switch) on pin 2
 */

String s;
int button = 2;
int state = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    state = digitalRead(button);

    if (state == HIGH) {
        s = String("hello");
        for (int i = 0; i < 10; i++) {
            s += " #";
            Serial.println(s + " world " + i);
        }
    }
}
