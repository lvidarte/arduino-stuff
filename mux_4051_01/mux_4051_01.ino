/* vim: set ft=c : */

/**
 * @see http://www.arduino.cc/playground/learning/4051
 *
 * Connect mux 4051 with pines s0, s1 and s2 on 2, 3 and 4 resp.
 * Connect z to pin 7
 */

const int s0 = 10;
const int s1 = 11;
const int s2 = 12;
const int z = 13; // power

void setup() {
    pinMode(s0, OUTPUT);
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(z, OUTPUT);
    randomSeed(analogRead(0));
}

void loop() {

    // Knight Rider 1 
    for (int i = 0; i <= 7; i++) {
        turn_on_led(i);
        delay(100);
    }
    for (int i = 6; i >= 0; i--) {
        turn_on_led(i);
        delay(100);
    }

    // Knight Rider 2 (two leds)
    int leds[][2] = {
        {0, 7}, {1, 6}, {2, 5}, {3, 4}
    };
    for (int i = 0; i <= 3; i++) {
        turn_on_leds(leds[i], 2, 5000);
    }
    for (int i = 2; i >= 0; i--) {
        turn_on_leds(leds[i], 2, 5000);
    }

    // Three leds
    int leds2[][3] = {
        {0, 2, 4}, {1, 3, 5}, {2, 4, 6}, {3, 5, 7}
    };
    for (int i = 0; i < 4; i++) {
        turn_on_leds(leds2[i], 3, 5000);
    }

    // Random led
    int last = -1;
    int next;
    for (int i = 0; i < 20; i++) {
        do {
            next = random(8);
        } while (next == last);
        turn_on_led(next);
        delay(100);
        last = next;
    }

}

void turn_on_led(int number) {
    digitalWrite(z, LOW);
    digitalWrite(s0, number & 0x01);
    digitalWrite(s1, number & 0x02); // no need to shift ;)
    digitalWrite(s2, number & 0x04); // idem
    digitalWrite(z, HIGH);
}

void turn_on_leds(int leds[], int length, int times) {
    for (int i = 0; i < times; i++) {
        for (int j = 0; j < length; j++) {
            turn_on_led(leds[j]);
        }
    }
}

