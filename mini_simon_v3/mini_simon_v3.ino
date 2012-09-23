/* vim: set ft=c : */

/**
 *  Mini version of Simon (1978)
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
const int maximoNivelPosible = 32;

int nivel = 5;
int jugada = 0;
int secuencia[maximoNivelPosible];
int largoSecuencia = 0;
int esperaEntreJugadas = 0;

boolean esperandoJugada = false;
boolean jugadaIncorrecta = false;


void setup() {
    for (int i = 0; i < totalLeds; i++) {
        pinMode(pinesLeds[i], OUTPUT);
    }
    pinMode(pinParlante, OUTPUT);
    randomSeed(analogRead(0));
}

void loop() {
    // Game Over
    if (jugadaIncorrecta || esperaEntreJugadas++ > 50) {
        juegoPerdido();
    }

    // Nivel completado
    if (jugada == nivel) {
        nivelGanado();
        if (nivel < maximoNivelPosible) {
            nivel ++;
        }
        jugada = 0;
        largoSecuencia = 0;
        esperandoJugada = false;
        delay(1500);
    }

    // 
    if (esperandoJugada) {
        for (int i = 0; i < totalLeds; i++) {
            bool pinLeido = false;
            while(digitalRead(pinesBotones[i]) == HIGH) {
                if (!pinLeido) {
                    pinLeido = true;
                    digitalWrite(pinesLeds[i], HIGH);
                    tone(pinParlante, sonidosLeds[i]);
                    if (secuencia[jugada++] != i) {
                        jugadaIncorrecta = true;
                    }
                }
            }
            if (pinLeido) {
                digitalWrite(pinesLeds[i], LOW);
                noTone(pinParlante);
                esperaEntreJugadas = 0;
            }
        }
        if (jugada == largoSecuencia) {
            esperandoJugada = false;
        }
    }
    // Mostrando nueva secuencia
    else {
        mostrarSecuencia();
        jugada = 0;
        esperandoJugada = true;
        esperaEntreJugadas = 0;
    }

    delay(50);
}

void mostrarSecuencia() {
    delay(1000);
    int duracion = calcularDuracion(largoSecuencia);
    secuencia[largoSecuencia++] = random(totalLeds);
    for (int i = 0; i < largoSecuencia; i++) {
        digitalWrite(pinesLeds[secuencia[i]], HIGH);
        tone(pinParlante, sonidosLeds[secuencia[i]], duracion);
        delay(duracion);
        digitalWrite(pinesLeds[secuencia[i]], LOW);
        delay(duracion);
    }
}

int calcularDuracion(int largoSecuencia) {
    if (largoSecuencia == nivel - 1) {
        return 100;
    }
    if (largoSecuencia > 4) {
        return 250;
    }
    return 500;
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

