/* vim: set ft=c : */

#include <IRremote.h>

#define sA 7
#define sB 8
#define sC 4
#define sD 5
#define sE 6
#define sF 2
#define sG 3
#define DP 9

int RECV_PIN = 11; //define input pin on Arduino

byte digits[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6};

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
    for (byte i = 2; i <= 9; i++) {
        pinMode(i, OUTPUT);
    }
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
}

void display(byte value) {
    digitalWrite(sA, value & 0x80);
    digitalWrite(sB, value & 0x40);
    digitalWrite(sC, value & 0x20);
    digitalWrite(sD, value & 0x10);
    digitalWrite(sE, value & 0x8);
    digitalWrite(sF, value & 0x4);
    digitalWrite(sG, value & 0x2);
    digitalWrite(DP, value & 0x1);
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        if (results.value == 0xff6897) {
            display(digits[0]);
        }
        if (results.value == 0xff30cf) {
            display(digits[1]);
        }
        if (results.value == 0xff18e7) {
            display(digits[2]);
        }
        if (results.value == 0xff7a85) {
            display(digits[3]);
        }
        if (results.value == 0xff10ef) {
            display(digits[4]);
        }
        if (results.value == 0xff38c7) {
            display(digits[5]);
        }
        if (results.value == 0xff5aa5) {
            display(digits[6]);
        }
        if (results.value == 0xff42bd) {
            display(digits[7]);
        }
        if (results.value == 0xff4ab5) {
            display(digits[8]);
        }
        if (results.value == 0xff52ad) {
            display(digits[9]);
        }
        irrecv.resume(); // Receive the next value
    }
}
