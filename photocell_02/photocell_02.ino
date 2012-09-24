/* vim: set ft=c : */

int pinLeds[] = {3, 6, 9, 11};
int pinPhotocell = A0;
int sensor = 0;
int darkness = 0;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 4; i++) {
        pinMode(pinLeds[i], OUTPUT);
    }
}

void loop() {
    sensor = analogRead(pinPhotocell);
    Serial.print("sensor: ");
    Serial.println(sensor);

    darkness = map(sensor, 1023, 0, 0, 255);
    Serial.print("darkness: ");
    Serial.println(darkness);

    digitalWrite(3, (darkness > 50 ? HIGH : LOW));
    digitalWrite(6, (darkness > 100 ? HIGH : LOW));
    digitalWrite(9, (darkness > 150 ? HIGH : LOW));
    digitalWrite(11, (darkness > 200 ? HIGH : LOW));

    delay(100);
}
