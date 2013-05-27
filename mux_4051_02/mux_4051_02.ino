/* vim: set ft=c : */

/**
 * @see http://www.arduino.cc/playground/learning/4051
 *
 * Connect mux 4051 with pines s0, s1 and s2 on 2, 3 and 4 resp.
 * Connect z to pin 7
 */

const int r0 = 4;
const int r1 = 5;
const int r2 = 6;
const int y = 7; // power
const int s0 = 10;
const int s1 = 11;
const int s2 = 12;
const int z = 13; // power

void setup() {
    pinMode(r0, OUTPUT);
    pinMode(r1, OUTPUT);
    pinMode(r2, OUTPUT);
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(y, OUTPUT);
    pinMode(z, OUTPUT);
}

void loop() {

    // Knight Rider 1 
    for (int i = 0; i <= 7; i++) {
        turn_on_led(i);
        delay(500);
    }
    for (int i = 6; i > 0; i--) {
        turn_on_led(i);
        delay(500);
    }


}

void turn_on_led(int number) {
    digitalWrite(y, LOW);
    digitalWrite(z, LOW);
    digitalWrite(r0, number & 0x01);
    digitalWrite(s0, number & 0x01);
    digitalWrite(r1, number & 0x02); // no need to shift ;)
    digitalWrite(s1, number & 0x02); // no need to shift ;)
    digitalWrite(r2, number & 0x04); // idem
    digitalWrite(s2, number & 0x04); // idem
    digitalWrite(y, HIGH);
    digitalWrite(z, HIGH);
}

void turn_on_leds(int leds[], int length, int times) {
    for (int i = 0; i < times; i++) {
        for (int j = 0; j < length; j++) {
            turn_on_led(leds[j]);
        }
    }
}

