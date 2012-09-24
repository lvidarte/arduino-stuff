/* vim: set ft=c : */

int pinLed = 11;
int pinSensor = A0;
int sensor = 0;
int darkness = 0;

void setup() {
    Serial.begin(9600);
    pinMode(pinLed, OUTPUT);
}

void loop() {
    sensor = analogRead(pinSensor);
    Serial.print("sensor: ");
    Serial.println(sensor);

    darkness = map(sensor, 1023, 0, 0, 255);
    Serial.print("darkness: ");
    Serial.println(darkness);

    analogWrite(pinLed, darkness);  
    delay(100);
}
