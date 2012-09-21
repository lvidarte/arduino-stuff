/* vim: set ft=c : */

int led = 9;
int brightness = 0;

void setup() {
    Serial.begin(9600);
    pinMode(led, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        brightness = (int) Serial.read();
        analogWrite(led, brightness);
    }
}
