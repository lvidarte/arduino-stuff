/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#define TUNITS 2

#define S0  0
#define S1  1
#define S2  2
#define PWR 3
#define MIN 4
#define MAX 5
#define VAL 6


byte units[TUNITS][7]= {
    {4, 5, 6, 7, 50, 58, 0},
    {10, 11, 12, 13, 60, 68, 0}
};


void setup()
{
    byte i, j;
    for (i = 0; i < TUNITS; i++) {
        for (j = 0; j < 4; j++) {
            pinMode(units[i][j], OUTPUT);
        }
    }
    Serial.begin(9600);
}

void turn_on_led(byte unit, byte number)
{
    //digitalWrite(units[unit][PWR], LOW);
    digitalWrite(units[unit][S0], number & 0x01);
    digitalWrite(units[unit][S1], number & 0x02); // no need to shift ;)
    digitalWrite(units[unit][S2], number & 0x04); // idem
    digitalWrite(units[unit][PWR], HIGH);
}

void turn_on_leds_on_unit(byte unit)
{
    for (byte i = 0; i < units[unit][VAL]; i++) {
        turn_on_led(unit, i);
    }
}

void set_actual(byte value)
{
    for (byte i = 0; i < TUNITS; i++) {
        if (value >= units[i][MIN] && value <= units[i][MAX]) {
            units[i][VAL] = value - units[i][MIN];
            return;
        }
    }
}

void loop()
{
    if (Serial.available() > 0) {
        byte value = Serial.read();
        set_actual(value);
    }
    for (byte i = 0; i < TUNITS; i++) {
        turn_on_leds_on_unit(i);
    }
}
