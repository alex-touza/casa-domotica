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

CDPins::EntradaDigital obstacles(16);
CDPins::EntradaDigital botoAlarma(25);
Joystick joystick(34, 35, 10);

DHT dht = Sensor::initDHT(17);
Temperatura temperatura(&dht, &NeoPixel::list[0], &NeoPixel::list[2], &TEMP_SETTING);
Humitat humitat(&dht, &NeoPixel::list[1]);

//TempHum dht(14, &leds.list[0], &leds.list[1]);
Pantalla pantalla(&temperatura, &humitat);

void setup() {
    obstacles.begin();
    botoAlarma.begin();
    joystick.begin();

    NeoPixel::begin();

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
    bool sensorsCanvi = temperatura.read() | humitat.read(); // clever code >>>> readability

    joystick.read(X);

    botoAlarma.read();
    obstacles.read();
    Serial.println("Botó alarma? " + String(botoAlarma.value));
    Serial.println("Obstacle? " + String(obstacles.value));

    if (*joystick.getPos(X) != 0) {
        int pos = *joystick.getPos(X);

        if ((abs(pos) > 30 && (millis() / 500 % 2)) || pantalla.isIdle) {  // Segon deadzone.
            if (!pantalla.isIdle)
                TEMP_SETTING += pos < 0 ? -1 : 1; // TODO Implementar acceleració de l'augment segons posició

            pantalla.update("Establint temp", String(TEMP_SETTING));
        }
    } else if (sensorsCanvi || !pantalla.isIdle)
        pantalla.idle();


    if (!obstacles.value) ALARMA = true;
    else if (botoAlarma.value) ALARMA = false;

    // El segon actual és senar i l'alarma està sonant?
    if ((millis() / 1000) % 2 && ALARMA) {
        NeoPixel::list[3] = CRGB::Red;
        NeoPixel::list[4] = CRGB::Red;
    } else {
        NeoPixel::list[3] = CRGB::Black;
        NeoPixel::list[4] = CRGB::Black;
    }

    NeoPixel::refresh();
    delay(200);
}