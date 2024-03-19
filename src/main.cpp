#include <Arduino.h>
#include "Pantalla.h"
#include "Joystick.h"
#include "Sensor.h"
#include "Temperatura.h"
#include "Humitat.h"
#include "Motor.h"
#include "Alarma.h"

const Axis DIR_TEMP_SETTING = Y;
const Axis DIR_ILUM = X;

enum Pantalles {
    ALT = -1,
    IDLE = 0,
    TEMPSET = 1,
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
Joystick joystick(34, 35, 10);
Timer joystickCooldown(250);

Motor ventilador(23, 19, 5);

DHT dht = Sensor::initDHT(17);
Temperatura temperatura(24, &dht, leds, leds + 2, &ventilador);
Humitat humitat(&dht, leds + 1);

Pantalla pantalla(&temperatura, &humitat);

CRGB* ilumLeds[]{leds + 5, leds + 6, leds + 7};

LEDArray iluminacio(ilumLeds, 3);
EntradaDigital botoIluminacio(13);
bool ilumEncesa = false;
int llum = 255;


void setup() {
    alarma.begin(1000, 2);

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

    botoIluminacio.begin();

    Serial.begin(9600);

    // Esperar fins que la comunicació estigui disponible
    while (!Serial);

    Serial.println("Hola");
    ventilador.on();
    delay(2000);
}

void loop() {
    // Lectura dels receptors
    temperatura.read();
    humitat.read();

    bool joystickActiu = joystick.read(DIR_TEMP_SETTING);
    joystick.read(DIR_ILUM);

    alarma.read();

    if (joystickActiu) {
        int pos = *joystick.getPos(DIR_TEMP_SETTING);

        if (joystickCooldown.hasFinished() && pantalla.screenId == Pantalles::TEMPSET && abs(pos) > 25) {
            joystickCooldown.active = true;
            joystickCooldown.reset();
            temperatura.setting += (pos < 0 ? -1 : 1) * (1 + (abs(pos) > 90));
        }

        pantalla.update("Establint temp", String(temperatura.setting) + " C", Pantalles::TEMPSET);
        
    } else {
        joystickCooldown.active = false;
        pantalla.idle();
    }

    if (botoIluminacio.read(true, true)) ilumEncesa = !ilumEncesa;
    CRGB color;
    if (ilumEncesa) {
      int v = map(*joystick.getPos(DIR_ILUM), 0, 100, 0, 255);
      color.setHSV(0, 0, llum);
    } else
      color = CRGB::Black;

    iluminacio.setColorAll(color);

    FastLED.show();
    delay(100);
}
