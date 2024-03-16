#include <Arduino.h>
#include "Pantalla.h"
#include "Joystick.h"
#include "Sensor.h"
#include "Temperatura.h"
#include "Humitat.h"
#include "Motor.h"
#include "Alarma.h"

#define NEOPIXEL_PIN 27
#define NEOPIXEL_N_LEDS 8

const Axis DIR_TEMP_SETTING = Y;

enum Pantalles {
    ALT = -1,
    IDLE = 0,
    TEMPSET = 1,
};

CRGB leds[NEOPIXEL_N_LEDS];

void NeoPixelBegin() {
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN, GRB>(leds, NEOPIXEL_N_LEDS); // NOLINT(*-static-accessed-through-instance)
    FastLED.setBrightness(80);
}

void NeoPixelRefresh() {
    FastLED.show();
}

/*
https://github.com/FastLED/FastLED/issues/1169
#define FASTLED_ALL_PINS_HARDWARE_SPI

 https://github.com/espressif/arduino-esp32/issues/3461#issuecomment-557943652
 */

/*
Compte amb els punters a ítems de les llistes. Com que les classes
 sempre utilitzaran punters a les variables originals i no les
 mateixes variables, per passar el punter d'un ítem d'una llista
 al constructor d'una classe, és suficient amb sumar el seu índex
 a la variable de la mateixa llista (que realment és un punter al
 primer ítem de la llista).
 */
CRGB* alarmaLeds[]{leds + 3, leds + 4};

Alarma alarma(25, 16, alarmaLeds, 2);
Joystick joystick(34, 35, 10);

Motor ventilador(11, 12, 10);

DHT dht = Sensor::initDHT(17);
Temperatura temperatura(24, &dht, leds, leds + 2, &ventilador);
Humitat humitat(&dht, leds + 1);

Pantalla pantalla(&temperatura, &humitat);

void setup() {
    alarma.begin(1000, 2);

    //bool* alarmaPtr = &ALARMA;

    //botoAlarma.attachInterrupt<bool*>(SIGNALFALLING, ([](bool* _alarma) { *_alarma = false; }), &alarmaPtr);
    //obstacles.attachInterrupt<bool*>(SIGNALFALLING, ([](bool* _alarma) { *_alarma = true; }), &alarmaPtr);

    joystick.begin();

    NeoPixelBegin();

    dht.begin();
    temperatura.begin();
    humitat.begin();

    pantalla.begin();

    ventilador.begin();

    Serial.begin(9600);

    // Esperar fins que la comunicació estigui disponible
    while (!Serial);

    Serial.println("Hola");
}

void loop() {
    // Lectura dels receptors
    bool sensorsCanvi = temperatura.read() | humitat.read(); // clever code >>>> readability

    joystick.read(DIR_TEMP_SETTING);

    alarma.read();

    if (*joystick.getPos(DIR_TEMP_SETTING) != 0) {
        int pos = *joystick.getPos(DIR_TEMP_SETTING);

        if ((abs(pos) > 20 && (millis() / 500 % 5)) || pantalla.screenId != Pantalles::TEMPSET) {
            if (pantalla.screenId != Pantalles::IDLE)
                temperatura.setting += (pos < 0 ? -1 : 1) * (1 + (abs(pos) > 60));

            pantalla.update("Establint temp", String(temperatura.setting), Pantalles::TEMPSET);
        }
    } else if (sensorsCanvi || pantalla.screenId == Pantalles::IDLE)
        pantalla.idle();

    NeoPixelRefresh();
    delay(100);
}