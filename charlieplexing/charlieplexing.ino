/* vim: set ft=c : */

#define PINES 3
#define LEDS 6
#define OFF -1

int pines[PINES] = {2, 3, 4};

int leds[LEDS][PINES] = {
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
    for (int i = 0; i < PINES; i++) {
        if (leds[led][i] == OFF) {
            pinMode(pines[i], INPUT);
        }
        else {
            pinMode(pines[i], OUTPUT);
            digitalWrite(pines[i], leds[led][i]);
        }
    }
}

void knightRider() {
    for (int i = 0; i < LEDS; i++) {
        turnOnLed(i);
        delay(ms);
    }
    for (int i = LEDS-2; i > 0; i--) {
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

