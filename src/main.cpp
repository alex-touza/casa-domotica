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

    // Pantalles d'interacció
    TEMPSET = 1,
    LIGHTSET = 2,
    LIGHTOFF = 3,

    // Pantalles d'informació
    LIGHTTOGGLE = 4,
    ALARMACTIVE = 5,
    ALARMOFF = 6,
    SEASONSET = 7,
    TEMPRESET = 8
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
//Timer joystickCooldown(500);

Motor ventilador(23, 19, 5);

DHT dht = Sensor::initDHT(17);
Temperatura temperatura(DEFAULT_TEMP, &dht, leds, leds + 2, &ventilador);
Humitat humitat(&dht, leds + 1);

CRGB* ilumLeds[]{leds + 5, leds + 6, leds + 7};

Iluminacio iluminacio(18, ilumLeds, 3);

Pantalla pantalla(&temperatura, &humitat, &iluminacio);


void setup() {
    alarma.begin(400, 2);

    //bool* alarmaPtr = &ALARMA;

    //botoAlarma.attachInterrupt<bool*>(SIGNALFALLING, ([](bool* _alarma) { *_alarma = false; }), &alarmaPtr);
    //obstacles.attachInterrupt<bool*>(SIGNALFALLING, ([](bool* _alarma) { *_alarma = true; }), &alarmaPtr);

    joystick.begin();

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

    if (alarma.active)
        // Si l'alarma està activada, la resta no importa.
        pantalla.update("ALARMA ACTIVADA", "ALERTA", Pantalles::ALARMACTIVE);

    else if (alarma.state == Alarma::State::IDLE && pantalla.screenId == Pantalles::ALARMACTIVE)
        // La pantalla mostra l'alerta, però l'alarma ja no està activa, forcem tornar a idle
        pantalla.idle();

    else if (alarma.state == Alarma::State::DEACTIVATED)
        pantalla.updateTimed({"Alarma", "desactivada"}, 1500, Pantalles::ALARMOFF);
    else {
        // PRESSED indica que el botó s'ha premut sense estar l'alarma activa.
        if (alarma.state == Alarma::State::PRESSED) {
            String prevSeason = Temperatura::seasonsName[temperatura.season];
            temperatura.setSeason(
                    temperatura.season == Temperatura::WINTER ? Temperatura::SUMMER : Temperatura::WINTER);

            pantalla.updateTimed(
                    {"Epoca de l'any", prevSeason + " => " + (Temperatura::seasonsName[temperatura.season])},
                    1500,
                    SEASONSET);
        } else if (iluminacio.read())
            pantalla.updateTimed({iluminacio.isOn ? "Llums encesos" : "Llums apagats", ""}, 1500, LIGHTTOGGLE);


        // Si la pantalla és idle o ja és d'interacció, podem utilitzar les accions del joystick.
        // Això és per evitar que les pantalles mostrades anteriorment (SEASONSET i LIGHTTOGGLE)
        // desapareguin abans de temps.
        if (pantalla.screenId < 4) {

            joystick.readState();

            if (joystick.isPressed(true) && pantalla.screenId == Pantalles::IDLE) {
                temperatura.setting = (int) round(temperatura.value);
                pantalla.updateTimed({"Temp restablerta", String(temperatura.setting) + " C"}, 1500, TEMPRESET);
                Serial.println("temp reset pressed"); }



            if (joystick.state.idle && (millis() - joystick.state.lastActive > 1000 || joystick.state.lastActive == 0) ) {
                pantalla.idle();
            } else if (joystick.state.axis == DIR_ILUM) {
                // Control de la brillantor

                if (iluminacio.isOn) {
                    if (pantalla.screenId == Pantalles::LIGHTSET && abs(joystick.state.pos) > 25) {
                        // Pujar/baixar la brillantor 16 unitats, o 32 si el joystick està al màxim
                        iluminacio.changeBrightness(
                                (joystick.state.pos < 0 ? -1 : 1) * (8 * (1 + (abs(joystick.state.pos) > 90))));
                                delay(150);
                    }

                    pantalla.update("Brillantor llums", iluminacio.brightnessStr(),
                                    Pantalles::LIGHTSET);
                } else
                    pantalla.update("Llums apagats", "", Pantalles::LIGHTOFF);


            } else if (joystick.state.axis == DIR_TEMP_SETTING) {
                // Control de la consigna


                if (pantalla.screenId == Pantalles::TEMPSET && abs(joystick.state.pos) > 25) {
                    temperatura.setting += (joystick.state.pos < 0 ? -1 : 1) * (1 + (abs(joystick.state.pos) > 90));
                    delay(150);
                }

                pantalla.update("Establint temp", String(temperatura.setting) + " C", Pantalles::TEMPSET);

            }
        }

    }


    //pantalla.checkTime();

    FastLED.show();
    delay(50);
}
