#include <AFMotor.h>

#define trigPin A0
#define echoPin A1
#define SPEED 200


AF_DCMotor motor_left(1, MOTOR12_2KHZ);
AF_DCMotor motor_right(2, MOTOR12_2KHZ);


void setup()
{
    randomSeed(analogRead(0));
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    motor_left.setSpeed(SPEED);
    motor_right.setSpeed(SPEED);
}

void loop()
{
    int rvalue;
    int distance = get_distance();
    if (distance > 40 || distance <= 0) {
        forward();
    } else {
        turn();
    }
}

void forward()
{
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
}

void backward()
{
    motor_left.run(BACKWARD);
    motor_right.run(BACKWARD);
}

void left() {
    motor_left.run(FORWARD);
    motor_right.run(BACKWARD);
}

void right() {
    motor_left.run(BACKWARD);
    motor_right.run(FORWARD);
}

void stop() {
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
}

void turn() {
    stop();
    delay(500);
    if (random(0, 2)) {
        backward();
        delay(random(1, 5) * 250);
        stop();
        delay(500);
    }
    if (random(0, 2)) {
        right();
        delay(random(1, 5) * 250);
    } else {
        left();
        delay(random(1, 5) * 250);
    }
    stop();
    delay(500);
}

long _get_distance()
{
    long duration, distance;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) * 0.03435;
    return distance;
}

long get_distance()
{
    long total_distance = 0;
    int amount = 20;
    for (int i = 0; i < amount; i++) {
        total_distance += _get_distance();
        delay(25);
    }
    return total_distance / amount;
}
