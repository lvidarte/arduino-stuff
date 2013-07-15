/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
#include <IRremote.h>
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
decode_results results;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);   
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver  
}

int state = LOW;

// the loop routine runs over and over again forever:
void loop() {
      if (irrecv.decode(&results)) {
        Serial.println(results.value, HEX);
        if (results.value == 0xffa25d) {
          state = (state == LOW) ? HIGH : LOW;
          digitalWrite(led, state);
          
        }
        irrecv.resume(); // Receive the next value
      }
      
  /*    
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(10000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(10000);               // wait for a second
*/
}
