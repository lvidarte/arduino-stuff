/* vim: set ft=c : */

/**
 *
 */

const int rows[3] = {10, 9, 8};
const int cols[3] = {7, 6, 5};


void setup() {
    for (int i = 5; i <= 10; i++) {
        pinMode(i, OUTPUT);
    }
}

void turn_on(int row, int col) {
    for (int i = 0; i < 3; i++) {
        digitalWrite(rows[i], (i == row ? HIGH : LOW));
        digitalWrite(cols[i], (i == col ? LOW : HIGH));
    }
}

void scan_matrix() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            turn_on(i, j);
            delay(200);
        }
    }
}

void draw(byte *c) {
    int pos = 0;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            digitalWrite(cols[col], (c[pos++] == 1 ? LOW: HIGH));
        }
        digitalWrite(rows[row], HIGH);
        delayMicroseconds(500);
        digitalWrite(rows[row], LOW);
    }
}

void show(byte *c, int times) {
    for (int i = 0; i < times; i++) {
        draw(c);
    }
}

void loop() {
    /*
    for (int i = 0; i < 3; i++) {
        scan_matrix();
    }

    byte a[9] = {1, 0, 1, 0, 1, 0, 1, 0, 1};
    byte b[9] = {0, 1, 0, 1, 1, 1, 0, 1, 0};

    for (int i = 0; i < 3; i++) {
        show(a, 500);
        show(b, 500);
    }
    */

    digitalWrite(rows[0], HIGH);
    digitalWrite(cols[0], HIGH);
    digitalWrite(cols[2], HIGH);
}

