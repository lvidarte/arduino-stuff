#define trigPin A0
#define echoPin A1

void setup()
{
    Serial.begin (9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop()
{
    int duration, distance;
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // in microseconds
    //distance = (duration/2) / 29.1; // 1/0.03435
    Serial.println(duration);
    distance = (duration/2) * 0.03435;
    if (distance >= 200 || distance <= 0){
        Serial.println("Out of range");
    }
    else {
        Serial.print(distance);
        Serial.println(" cm");
    }
    delay(500);
}
