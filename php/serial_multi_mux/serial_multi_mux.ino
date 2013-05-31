/* vim: set ft=c : */

#define UNITS 2

int units [UNITS][4]= {
    {1, 2, 3, 10},
    {5, 6, 7, 11}
};

void setup() {
    int i, j;
    for (i = 0; i < UNITS; i++) {
        for (j = 0; j < 4; j++) {
            pinMode(units[i][j], OUTPUT);
        }
    }
    //Serial.begin(9600);
}

void turn_on_led(int unit, int number) {
    digitalWrite(units[unit][3], LOW);
    digitalWrite(units[unit][0], number & 0x01);
    digitalWrite(units[unit][1], number & 0x02); // no need to shift ;)
    digitalWrite(units[unit][2], number & 0x04); // idem
    digitalWrite(units[unit][3], HIGH);
}

void turn_on_leds_on_unit(int unit, int leds) {
    int i;
    for (i = 0; i < leds; i++) {
        turn_on_led(unit, i);
    }
}

void loop() {
    int i, j;
    /*
    if (Serial.available() > 0) {
        char incomingByte = Serial.read();
        Serial.println(incomingByte);
    }
    */
    for (i = 0; i < UNITS; i++) {
        for (j = 0; j <= 8; j++) {
            turn_on_led(i, j);
        }
    }
}
