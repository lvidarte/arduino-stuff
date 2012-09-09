/* vim: set ft=c : */

/**
 *  Mini version of Simon (1978)
 *
 *  Connect leds on 8, 10, 12
 *  Connect switches on 2, 4, 6
 */

const int totalLeds = 3;
const int leds[totalLeds] = {8, 10, 12};
const int buttons[totalLeds] = {2, 4, 6};

boolean done;
boolean gameOver = false;

const int seqLength = 5;
int seq[seqLength];
int seqIndex = 0;


void setup() {

    for (int i = 0; i < totalLeds; i++) {
        pinMode(leds[i], OUTPUT);
    }

    /* Gen and show sequence */
    randomSeed(analogRead(0));
    for (int i = 0; i < seqLength; i++) {
        seq[i] = random(totalLeds);
        digitalWrite(leds[seq[i]], HIGH);
        delay(500);
        digitalWrite(leds[seq[i]], LOW);
        delay(500);
    }

}

void loop() {

    // Game
    if (!gameOver && seqIndex < seqLength) {
        for (int i = 0; i < totalLeds; i++) {
            done = false;
            while(digitalRead(buttons[i]) == HIGH) {
                if (!done) {
                    done = true;
                    digitalWrite(leds[i], HIGH);
                    if (seq[seqIndex++] != i) {
                        gameOver = true;
                    }
                }
            }
            digitalWrite(leds[i], LOW);
        }
    }

    // You Win
    if (!gameOver && seqIndex == seqLength) {
        delay(50);
        digitalWriteAll(HIGH);
        delay(50);
        digitalWriteAll(LOW);
    }

    // Game Over
    if (gameOver) {
        delay(50);
        digitalWriteAll(HIGH);
    }

    delay(50);

}

void digitalWriteAll(int value) {
    for (int i = 0; i < totalLeds; i++) {
        digitalWrite(leds[i], value);
    }
}

