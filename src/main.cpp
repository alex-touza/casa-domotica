#include <Arduino.h>
#include "NeoPixel.h"
#include "Pantalla.h"
#include "EntradaDigital.h"
#include "Joystick.h"
#include "Sensor.h"
#include "Temperatura.h"
#include "Humitat.h"
#include "Motor.h"
#include "Alarma.h"

/*
https://github.com/FastLED/FastLED/issues/1169
#define FASTLED_ALL_PINS_HARDWARE_SPI
 */


Alarma alarma(25, 16, alarmaLeds, 2);
Joystick joystick(34, 35, 10);

Motor ventilador(11, 12, 10);

DHT dht = Sensor::initDHT(17);
Temperatura temperatura(&dht, &NeoPixel::list[0], &NeoPixel::list[2], &TEMP_SETTING);
Humitat humitat(&dht, &NeoPixel::list[1]);

//TempHum dht(14, &leds.list[0], &leds.list[1]);
Pantalla pantalla(&temperatura, &humitat);

void setup() {
    alarma.begin(1000, 2);
    joystick.begin();

    NeoPixel::begin();

    dht.begin();
    temperatura.begin();
    humitat.begin();

    pantalla.begin();

    ventilador.begin();

    Serial.begin(9600);

    // Esperar fins que la comunicació estigui disponible
    while (!Serial);
}

void loop() {
    // Lectura dels receptors
    bool sensorsCanvi = temperatura.read() | humitat.read(); // clever code >>>> readability

    joystick.read(X);

    alarma.read();

    if (*joystick.getPos(X) != 0) {
        int pos = *joystick.getPos(X);

        if ((abs(pos) > 30 && (millis() / 500 % 2)) || pantalla.isIdle) {  // Segon deadzone.
            if (!pantalla.isIdle)
                TEMP_SETTING += pos < 0 ? -1 : 1; // TODO Implementar acceleració de l'augment segons posició

            pantalla.update("Establint temp", String(TEMP_SETTING));
        }
    } else if (sensorsCanvi || !pantalla.isIdle)
        pantalla.idle();


    NeoPixel::refresh();
    delay(100);
}