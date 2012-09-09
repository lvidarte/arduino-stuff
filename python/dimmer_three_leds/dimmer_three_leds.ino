/* vim: set ft=c : */

int leds[] = {3, 6, 9};

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
        }
        else {
            brightness = value;
        }

        if (brightness < 5) {
            brightness = 0;
        }

        analogWrite(leds[pin], brightness);
    }
}
