/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

int pinLed = 11;
int pinSensor = A0;
int sensor = 0;
int brightness = 0;

void setup() {
    Serial.begin(9600);
    pinMode(pinLed, OUTPUT);
}

void loop() {
    sensor = analogRead(pinSensor);
    Serial.print("sensor: ");
    Serial.println(sensor);

    brightness = map(sensor, 1023, 0, 0, 255);
    Serial.print("brightness: ");
    Serial.println(brightness);

    analogWrite(pinLed, brightness);  
    delay(100);
}
