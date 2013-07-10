/* vim: set ft=c : */

#include <IRremote.h>


int RECV_PIN = 11; // IR remote pin

IRrecv irrecv(RECV_PIN);
decode_results results;
 
byte digits[] = {0x3f, 0x09, 0x5e, 0x5b, 0x69, 0x73, 0x77, 0x19, 0x7f, 0x7b};
byte segments[] = {0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
byte actual = 0;


void setup() {
    for (int i = 0; i < 7; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    irrecv.enableIRIn(); // Start the receiver
    putNumber(actual); // Set digit to 0
}

void loop() {
    if (irrecv.decode(&results)) {
        if (results.value == 0xFF906F && actual < 9) { // Up
            putNumber(++actual);
        }
        if (results.value == 0xFFA857 && actual > 0) { // Down
            putNumber(--actual);
        }
        irrecv.resume(); // Receive the next value
    }
}

void putNumber(byte n) {
    for (int i = 0; i < 7; i++) {
        digitalWrite(i, digits[n] & segments[i]);
    }
}
