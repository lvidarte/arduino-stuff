/* vim: set ft=c : */

#define RED 11
#define GREEN 10
#define BLUE 9

int pins[] = {RED, GREEN, BLUE};

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  int i;
  for (i = 0; i <= 2; i++) {
    digitalWrite(pins[i], HIGH);
    delay(1000);
  }
  for (i = 0; i <= 2; i++) {
    digitalWrite(pins[i], LOW);
    delay(1000);
  }
}
