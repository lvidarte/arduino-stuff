/* vim: set ft=c : */

int pinLed = 11;
int pinSensor = A0;
int sensor = 0;
int brightness = 0;

void setup() {
    Serial.begin(9600);
    pinMode(pinLed, OUTPUT);
}

void loop() {
    sensor = analogRead(pinSensor);
    Serial.print("sensor: ");
    Serial.println(sensor);

    brightness = map(sensor, 1023, 0, 0, 255);
    Serial.print("brightness: ");
    Serial.println(brightness);

    analogWrite(pinLed, brightness);  
    delay(100);
}
