/* vim: set ft=c : */

#define PINS 3
#define LEDS 6
#define OFF -1

int pins[PINS] = {2, 3, 4};

int leds[LEDS][PINS] = {
    {HIGH, LOW, OFF},
    {LOW, HIGH, OFF},
    {OFF, HIGH, LOW},
    {OFF, LOW, HIGH},
    {LOW, OFF, HIGH},
    {HIGH, OFF, LOW},
};

int ms = 100; // milliseconds


void setup() {
}

void turnOnLed(int led) {
    for (int i = 0; i < PINS; i++) {
        if (leds[led][i] == OFF) {
            pinMode(pins[i], INPUT);
        }
        else {
            pinMode(pins[i], OUTPUT);
            digitalWrite(pins[i], leds[led][i]);
        }
    }
}

void knightRider() {
    for (int i = 0; i < LEDS; i++) {
        turnOnLed(i);
        delay(ms);
    }
    for (int i = LEDS - 2; i > 0; i--) {
        turnOnLed(i);
        delay(ms);
    }
}

void turnOnTwoLeds(int led0, int led1) {
    for (int i = 0; i < ms * 30; i++) {
        turnOnLed(led0);
        turnOnLed(led1);
    }
}

void modernKnightRider() {
    turnOnTwoLeds(0, 5);
    turnOnTwoLeds(1, 4);
    turnOnTwoLeds(2, 3);
    turnOnTwoLeds(1, 4);
}

void loop() {
    knightRider();
    //modernKnightRider();
}

