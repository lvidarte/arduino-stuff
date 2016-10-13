/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#include <Stepper.h>

const int stepsPerRevolution = 24;

Stepper motor0(stepsPerRevolution, 6, 7, 8, 9);
Stepper motor1(stepsPerRevolution, 10, 11, 12, 13);

void setup()
{
    Serial.begin(9600);
    motor0.setSpeed(60);
    motor1.setSpeed(60);
}

void loop()
{
    int motors[2] = {0, 0};
    if (serialRead(motors))
    {
        Serial.print(motors[0]);
        Serial.print(",");
        Serial.println(motors[1]);
        motor0.step(motors[0]);
        //motor1.step(motors[1]);
    }
}

int serialRead(int motors[])
{
    int i;
    char c, command = NULL;
    if (Serial.available())
    {
        int last[2] = {0, 0};
        int sign[2] = {1, 1};
        do {
            c = Serial.read();
            if (c != -1) {
                i = (command == 's') ? 0 : 1;
                switch (c)
                {
                    case 's':
                    case ',':
                        command = c;
                        break;
                    case '-':
                        sign[i] = -1;
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        motors[i] = (last[i] * 10) + (c - '0');
                        last[i] = motors[i];
                        break;
                }
            }
        } while (c != '\0');
        motors[0] *= sign[0];
        motors[1] *= sign[1];
        return 1;
    }
    return 0;
}
