#include <Arduino.h>
#include "NeoPixel.h"
#include "Pantalla.h"
#include "EntradaDigital.h"
#include "Joystick.h"
#include "Sensor.h"
#include "Temperatura.h"
#include "Humitat.h"

/*
https://github.com/FastLED/FastLED/issues/1169
#define FASTLED_ALL_PINS_HARDWARE_SPI
 */

int TEMP_SETTING = 24;
bool ALARMA = false;

CDPins::EntradaDigital obstacles(5);
CDPins::EntradaDigital botoAlarma(23);
Joystick joystick(34, 35, 10);

NeoPixel leds;

DHT dht = Sensor::initDHT(14);
Temperatura temperatura(&dht, &leds.list[0]);
Humitat humitat(&dht, &leds.list[1]);

//TempHum dht(14, &leds.list[0], &leds.list[1]);
Pantalla pantalla(&temperatura, &humitat, &TEMP_SETTING);

void setup() {
    obstacles.begin();
    botoAlarma.begin();
    joystick.begin();

    leds.begin();

    dht.begin();
    temperatura.begin();
    humitat.begin();

    pantalla.begin();

    Serial.begin(9600);

    // Esperar fins que la comunicació estigui disponible
    while (!Serial);
}

void loop() {
    // Lectura dels receptors
    bool sensorsCanvi = dht.read();

    joystick.read(X);

    botoAlarma.read();
    obstacles.read();

    if (*joystick.getPos(X) != 0) {
        int pos = *joystick.getPos(X);

        if (abs(pos) > 30)  // Segon deadzone.
            TEMP_SETTING += pos < 0 ? -1 : 1; // TODO Implementar acceleració de l'augment segons posició

        if (abs(pos) > 30 || pantalla.isIdle)
            pantalla.update("Establint temp", String(TEMP_SETTING));
    } else if (sensorsCanvi || !pantalla.isIdle)
        pantalla.idle();


    if (!obstacles.value) ALARMA = true;
    else if (botoAlarma.value) ALARMA = false;

    // El segon actual és parell i l'alarma està sonant?
    if ((millis() / 1000) % 2 == 0 && ALARMA) {
        leds.list[3] = CRGB::Red;
        leds.list[4] = CRGB::Red;
    } else {
        leds.list[3] = CRGB::Black;
        leds.list[4] = CRGB::Black;
    }

    leds.refresh();
}