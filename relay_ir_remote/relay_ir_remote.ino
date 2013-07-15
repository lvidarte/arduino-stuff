/* vim: set ft=c : */

#include <IRremote.h>

int relay_pin = 13;
int recv_pin = 11;
int actual_state = LOW;

IRrecv irrecv(recv_pin);
decode_results results;


void setup() {
    pinMode(relay_pin, OUTPUT);
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        if (results.value == 0xffa25d) { // On/Off button
            actual_state = (actual_state == LOW) ? HIGH : LOW;
            digitalWrite(relay_pin, actual_state);
        }
        irrecv.resume(); // Receive the next value
    }
}
