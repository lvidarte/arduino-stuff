/* vim: set ft=c : */

int motor = 9;

void setup() {
    pinMode(motor, OUTPUT);
}

void loop() {
    for (int i = 0; i <= 255; i+=10) {
        analogWrite(motor, i);
        delay(500);
    }
    for (int i = 255; i >= 0; i-=10) {
        analogWrite(motor, i);
        delay(500);
    }
}
