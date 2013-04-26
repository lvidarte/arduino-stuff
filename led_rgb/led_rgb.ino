/* vim: set ft=c : */

/**
 * 
 */

int time_step = 25;
int time_change = 20000;

int colors[] = {9, 10, 11};
int values[] = {0, 0, 0};

void changeColor(int led) {
    int i;
    int value = random(256);

    /*
    Serial.println("-----------");
    Serial.println(led);
    Serial.println(values[led]);
    Serial.println(value);
    */

    if (value > values[led]) {
        for (i = values[led]; i <= value; i++) {
            analogWrite(colors[led], i);
            delay(time_step);
        }
    }
    if (value < values[led]) {
        for (i = values[led]; i >= value; i--) {
            analogWrite(colors[led], i);
            delay(time_step);
        }
    }
    values[led] = value;
}

void setup() {
    //Serial.begin(9600);
    randomSeed(analogRead(0));
    for (int i = 0; i < 3; i++) {
        pinMode(colors[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < 3; i++) {
        changeColor(i);
    }
    delay(time_change);
}
