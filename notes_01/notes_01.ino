/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

int speaker = 12;

void setup() {
  pinMode(speaker, OUTPUT);
}

void playNote(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speaker, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speaker, LOW);
    delayMicroseconds(tone);
  }
}

void loop() {

  int notes[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 1915};
  for (int i=0; i<9; i++) {
    playNote(notes[i], 300);
    //delay(10);
  }

  delay(1000);
}
