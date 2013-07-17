#include <AFMotor.h>

const int LED_PIN = 13;
const int speed = 80;

AF_DCMotor motor_left(1, MOTOR12_2KHZ);
AF_DCMotor motor_right(2, MOTOR12_2KHZ);

int pwm;

void setup()
{
    pwm = map(speed, 0, 100, 0, 255);
    motor_left.setSpeed(pwm);
    motor_right.setSpeed(pwm);
}

void loop()
{
    forward(1000);
    stop(500);
    right(1000);
    stop(500);
    backward(1000);
    stop(500);
    left(1000);
    stop(500);
}

void forward(int time)
{
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
    delay(time);
}

void backward(int time)
{
    motor_left.run(BACKWARD);
    motor_right.run(BACKWARD);
    delay(time);
}

void left(int time) {
    motor_left.run(FORWARD);
    motor_right.run(BACKWARD);
    delay(time);
}

void right(int time) {
    motor_left.run(BACKWARD);
    motor_right.run(FORWARD);
    delay(time);
}

void stop(int time) {
    motor_left.run(RELEASE);
    motor_right.run(RELEASE);
    delay(time);
}
