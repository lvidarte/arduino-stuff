/* vim: set ft=c : */

/**
 *  Connect leds on 8, 10, 12
 *  Connect switches on 2, 4, 6
 */

const int buttons[3] = {2, 4, 6};
const int leds[3] = {8, 10, 12};

boolean done;
boolean gameover = false;

const int len = 5;
int seq[len];
int actual = 0;


void setup() {

    for (int i = 0; i < 3; i++) {
        pinMode(leds[i], OUTPUT);
    }

    /* Gen and show sequence */
    randomSeed(analogRead(0));
    for (int i = 0; i < len; i++) {
        seq[i] = random(3);
        digitalWrite(leds[seq[i]], HIGH);
        delay(500);
        digitalWrite(leds[seq[i]], LOW);
        delay(500);
    }

}

void loop() {

    // Game
    if (!gameover && actual < len) {
        for (int i = 0; i < 3; i++) {
            done = false;
            while(digitalRead(buttons[i]) == HIGH) {
                if (!done) {
                    done = true;
                    digitalWrite(leds[i], HIGH);
                    if (seq[actual++] != i) {
                        gameover = true;
                    }
                }
            }
            digitalWrite(leds[i], LOW);
        }
    }

    // You Win
    if (!gameover && actual == len) {
        delay(50);
        digitalWriteAll(HIGH);
        delay(50);
        digitalWriteAll(LOW);
    }

    // Game Over
    if (gameover) {
        delay(200);
        digitalWriteAll(HIGH);
    }

    delay(50);

}

void digitalWriteAll(int value) {
    for (int i = 0; i < 3; i++) {
        digitalWrite(leds[i], value);
    }
}

