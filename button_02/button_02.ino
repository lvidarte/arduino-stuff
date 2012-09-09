/* vim: set ft=c : */

/**
 *  Connect leds on 8, 10, 12
 *  Connect switches on 2, 4, 6
 */

int buttons[3] = {2, 4, 6};
int leds[3] = {8, 10, 12};
int states[3] = {LOW, LOW, LOW};
boolean changed;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 3; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < 3; i++) {
        changed = false;
        while(digitalRead(buttons[i]) == HIGH) {
            if (!changed) {
                states[i] = (states[i] == HIGH) ? LOW : HIGH;
                digitalWrite(leds[i], states[i]);
                changed = true;
            }
        }
    }
    delay(10);
}

