/* vim: set ft=c : */

/**
 * @see 
 *
 */

#define SPACE { \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0}  \
}

#define LOVE { \
    {0, 0, 0, 0, 0}, \
    {0, 1, 0, 1, 0}, \
    {1, 0, 1, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {0, 1, 0, 1, 0}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 0, 0, 0}  \
}

#define A { \
    {0, 1, 1, 1, 0}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 1, 1, 1, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}  \
}

#define B { \
    {1, 1, 1, 1, 0}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 1, 1, 1, 0}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 1, 1, 1, 0}  \
}

#define C { \
    {0, 1, 1, 1, 1}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1}  \
}

#define E { \
    {1, 1, 1, 1, 1}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 0, 0, 0, 0}, \
    {1, 1, 1, 1, 1}  \
}

#define M { \
    {1, 0, 0, 0, 1}, \
    {1, 1, 0, 1, 1}, \
    {1, 0, 1, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}  \
}

#define O { \
    {0, 1, 1, 1, 0}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {1, 0, 0, 0, 1}, \
    {0, 1, 1, 1, 0}  \
}

#define T { \
    {1, 1, 1, 1, 1}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0}  \
}

const byte cols[5] = {9, 10, 11, 12, 13};
const byte rows[7] = {2, 3, 4, 5, 6, 7, 8};

byte arrow_up[7][5] = {
    {0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0},
    {1, 0, 1, 0, 1},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0}
};

byte smile[7][5] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0},
    {1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

void refresh(int matrix[7][5]) {
    for (int row = 0; row < 7; row++) {
        for (int col = 0; col < 5; col++) {
            digitalWrite(cols[col], (matrix[row][col] ? LOW: HIGH));
        }
        digitalWrite(rows[row], HIGH);
        delayMicroseconds(500);
        digitalWrite(rows[row], LOW);
    }
}

void draw(int matrix[7][5], int times) {
    for (int i = 0; i < times; i++) {
        refresh(matrix);
    }
}

void setup() {
    for (int i = 2; i <= 13; i++) {
        pinMode(i, OUTPUT);
    }
}

void loop() {

    /*
    draw(smile, 100);
    delay(100);
    draw(arrow_up, 100);
    delay(1000);
    */

    int msg[][7][5] = {A, B, SPACE, C, E, SPACE, M, O, SPACE, LOVE, SPACE};

    // Marquee
    int buffer[7][5];
    int index, col_offset;
    for (int i = 0; i < 10; i++) {
        for (int offset = 0; offset < 6; offset++) {
            for (int row = 0; row < 7; row++) {
                for (int col = 0; col < 5; col++) {
                    if (offset == 5 - col) {
                        buffer[row][col] = 0;
                    }
                    else {
                        index = (col + offset < 5) ? i : i + 1;
                        col_offset = (col + offset < 5) ? col + offset : col + offset - 5 - 1;
                        buffer[row][col] = msg[index][row][col_offset];
                    }
                }
            }
            draw(buffer, 50);
        }
    }

    /*
    for (int i = 0; i < 12; i++) {
        draw(msg[i], 100);
        delay(200);
    }
    */

}

