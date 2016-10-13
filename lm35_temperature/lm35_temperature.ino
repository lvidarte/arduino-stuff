/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

int sensor = 0;


void setup() {
    Serial.begin(9600);
}

void loop() {
    int reading = analogRead(sensor);
    float temperature_c = (5.0 * reading * 100.0) / 1024.0;

    Serial.print(temperature_c);
    Serial.println(" degrees C");

    delay(5000);
}
