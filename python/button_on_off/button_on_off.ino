/* vim: set ft=c : */

int led = 3;
int state = 0;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        state = (int) Serial.read();
        state = map(state, 0, 1, LOW, HIGH);
        //Serial.println(state, DEC);
        digitalWrite(led, state);
    }
}

