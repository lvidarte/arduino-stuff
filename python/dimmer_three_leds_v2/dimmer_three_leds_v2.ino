/* vim: set ft=c : */

int leds[] = {9, 10, 11};

int pin = 0;
int brightness = 0;

void setup() {
    Serial.begin(9600);
    for (int i = 0; i < 3; i++) {
        pinMode(leds[i], OUTPUT);
    }
}

void loop() {
    if (Serial.available() > 0) {

        int value = (int) Serial.read();

        if (value >= 0 && value <= 2) {
            pin = value;
            Serial.println(pin, DEC);
        }
        else {
            brightness = map(value, 100, 125, 0, 255);
            Serial.println(brightness, DEC);
        }

        analogWrite(leds[pin], brightness);
    }
}
