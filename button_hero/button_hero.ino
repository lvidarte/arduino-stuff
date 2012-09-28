/* vim: set ft=c : */

/**
 *  
 *
 *  Connect leds on 3, 6, 9 and 11
 *  Connect switches on 2, 4, 7 and 8
 *  Connect speaker on 12
 */

const int totalLeds = 4;
const int pinesLeds[] = {11, 9, 6, 3};
const int pinesBotones[] = {8, 7, 4, 2};
const int pinParlante = 12;
const int sonidosLeds[] = {1319, 880, 659, 440};
const int sonidoJuegoPerdido = 330;
const int sonidoNivelGanado = 2093;

int vuelta = 0;
int limiteVueltas = 10;
int pinActual = 0;

boolean jugadaIncorrecta = false;


void setup() {
    for (int i = 0; i < totalLeds; i++) {
        pinMode(pinesLeds[i], OUTPUT);
    }
    pinMode(pinParlante, OUTPUT);
    randomSeed(analogRead(0));
}


void loop() {

    if (vuelta == 0) {
        mostrarNuevo();
    }

    if (jugadaIncorrecta || vuelta == limiteVueltas) {
        juegoPerdido();
    }


    if (vuelta++ < limiteVueltas) {
        for (int i = 0; i < totalLeds; i++) {
            bool pinLeido = false;
            while(digitalRead(pinesBotones[i]) == HIGH) {
                if (!pinLeido) {
                    pinLeido = true;
                    //digitalWrite(pinesLeds[i], HIGH);
                    //tone(pinParlante, sonidosLeds[i]);
                    if (pinActual != i) {
                        jugadaIncorrecta = true;
                    }
                }
            }
            if (pinLeido) {
                //digitalWrite(pinesLeds[i], LOW);
                //noTone(pinParlante);
                vuelta = 0; 
            }
        }
    }

    delay(50);

}

void mostrarNuevo() {
    int duracion = 50;
    pinActual = random(totalLeds);
    digitalWrite(pinesLeds[pinActual], HIGH);
    tone(pinParlante, sonidosLeds[pinActual], duracion);
    delay(duracion);
    digitalWrite(pinesLeds[pinActual], LOW);
    delay(duracion);
}


void nivelGanado() {
    delay(100);
    for (int i = 0; i < 10; i++) {
        digitalWriteAll(HIGH);
        tone(pinParlante, sonidoNivelGanado, 50);
        delay(50);
        digitalWriteAll(LOW);
        delay(50);
    }
}

void juegoPerdido() {
    delay(100);
    digitalWriteAll(HIGH);
    tone(pinParlante, sonidoJuegoPerdido, 750);
    delay(750);
    digitalWriteAll(LOW);
    while (true);
}

void digitalWriteAll(int value) {
    for (int i = 0; i < totalLeds; i++) {
        digitalWrite(pinesLeds[i], value);
    }
}

