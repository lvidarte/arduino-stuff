/* vim: set ft=c : */

/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#define sA 7
#define sB 8
#define sC 4
#define sD 5
#define sE 6
#define sF 2
#define sG 3
#define DP 9

/*
    A B C D E F G DP
  0 x x x x x x - -  0xfc
  1 - x x - - - - -  0x60
  2 x x - x x - x -  0xda
  3 x x x x - - x -  0xf2
  4 - x x - - x x -  0x66
  5 x - x x - x x -  0xb6
  6 x - x x x x x -  0xbe
  7 x x x - - - - -  0xe0
  8 x x x x x x x -  0xfe
  9 x x x x - x x -  0xf6
*/

byte digits[] = {0xfc, 0x60, 0xda, 0xf2, 0x66, 0xb6, 0xbe, 0xe0, 0xfe, 0xf6};


void setup() {
    for (byte i = 2; i <= 9; i++) {
        pinMode(i, OUTPUT);
    }
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
    for (int i = 0; i < 10; i++) {
        display(digits[i]);
        delay(1000);
    }
}
