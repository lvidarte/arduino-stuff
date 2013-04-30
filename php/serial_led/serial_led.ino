/* vim: set ft=c : */

#define LED 10


void setup() {
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
}

void loop() {
    if (Serial.available() > 0) {
        int incomingByte = Serial.read();
        if (incomingByte == '1') {
            digitalWrite(LED, HIGH);
        }
        if (incomingByte == '0') {
            digitalWrite(LED, LOW);
        }
    }
}
