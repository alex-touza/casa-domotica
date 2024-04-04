#include <Arduino.h>
#include "Pantalla.h"
#include "Joystick.h"
#include "Sensor.h"
#include "Temperatura.h"
#include "Humitat.h"
#include "Motor.h"
#include "Alarma.h"
#include "Iluminacio.h"

const Axis DIR_TEMP_SETTING = Y;
const Axis DIR_ILUM = X;

const int DEFAULT_TEMP = 24;

enum Pantalles {
    ALT = -1,
    IDLE = 0,
    TEMPSET = 1,
    LIGHTSET = 2,
    LIGHTOFF = 3
};

CRGB leds[8];

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
Joystick joystick(34, 35, 14, 10);
Timer joystickCooldown(250);

Motor ventilador(23, 19, 5);

DHT dht = Sensor::initDHT(17);
Temperatura temperatura(DEFAULT_TEMP, &dht, leds, leds + 2, &ventilador);
Humitat humitat(&dht, leds + 1);

CRGB* ilumLeds[]{leds + 5, leds + 6, leds + 7};

Iluminacio iluminacio(13, ilumLeds, 3);

Pantalla pantalla(&temperatura, &humitat, &iluminacio);


void setup() {
    alarma.begin(400, 2);

    //bool* alarmaPtr = &ALARMA;

    //botoAlarma.attachInterrupt<bool*>(SIGNALFALLING, ([](bool* _alarma) { *_alarma = false; }), &alarmaPtr);
    //obstacles.attachInterrupt<bool*>(SIGNALFALLING, ([](bool* _alarma) { *_alarma = true; }), &alarmaPtr);

    joystick.begin();
    joystickCooldown.active = false;

    FastLED.addLeds<WS2812B, 27, GRB>(leds, 8); // NOLINT(*-static-accessed-through-instance)
    FastLED.setBrightness(80);

    dht.begin();
    temperatura.begin();
    humitat.begin();

    pantalla.begin();

    ventilador.begin();

    //botoIluminacio.begin();
    iluminacio.begin();

    Serial.begin(9600);

    // Esperar fins que la comunicació estigui disponible
    while (!Serial);

    Serial.println("Hola");
    ventilador.on();
    delay(2000);
}

void loop() {
    // Lectura dels receptors
    // També il·luminen els LEDs corresponents.
    temperatura.read(); // També fa funcionar el ventilador
    humitat.read();

    alarma.read();
    iluminacio.read();
    joystick.readState();

    if (joystick.isPressed(true)) temperatura.setting = (int) round(temperatura.value);


    if (joystick.state.axis == DIR_ILUM && joystick.state.idle) {
        if (iluminacio.on) {
            if (joystickCooldown.hasFinished() && pantalla.screenId == Pantalles::LIGHTSET && abs(joystick.state.pos) > 25) {
                joystickCooldown.active = true;
                joystickCooldown.reset();

                // Pujar/baixar la brillantor 16 unitats, o 32 si el joystick està al màxim
                iluminacio.changeBrightness((joystick.state.pos < 0 ? -1 : 1) * (8 * (1 + (abs(joystick.state.pos) > 90))));
            } else joystickCooldown.active = false;

            pantalla.update("Brillantor llums", iluminacio.brightnessStr(),
                            Pantalles::LIGHTSET);
        } else {
            pantalla.update("Llums apagats", "", Pantalles::LIGHTOFF);
            joystickCooldown.active = false;
        }


    } else if (joystick.state.axis == DIR_TEMP_SETTING && joystick.state.idle) {
        if (joystickCooldown.hasFinished() && pantalla.screenId == Pantalles::TEMPSET && abs(joystick.state.pos) > 25) {
            joystickCooldown.active = true;
            joystickCooldown.reset();
            temperatura.setting += (joystick.state.pos < 0 ? -1 : 1) * (1 + (abs(joystick.state.pos) > 90));
        } else joystickCooldown.active = false;

        pantalla.update("Establint temp", String(temperatura.setting) + " C", Pantalles::TEMPSET);

    } else {
        joystickCooldown.active = false;
        pantalla.idle();
    }


    FastLED.show();
    delay(100);
}
