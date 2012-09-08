int n = 0;
char c;

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print("Message from Arduino: ");
    Serial.println(n);
    n++;

    if (Serial.available() > 0) {
      Serial.print("Received by Arduino: ");
      do {
        c = Serial.read();
        Serial.print(c);
      } while (c != '\n');
    }

    delay(1000);
}
