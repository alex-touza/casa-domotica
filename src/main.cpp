#include <Arduino.h>
#include "NeoPixel.h"
#include "Pantalla.h"
#include "EntradaDigital.h"
#include "TempHum.h"
#include "Joystick.h"

int TEMP = 24;
bool ALARMA = false;

CDPins::EntradaDigital obstacles(5);
CDPins::EntradaDigital botoAlarma(23);
Joystick joystick(34, 35, 10);

NeoPixel leds;
TempHum dht(14, &leds.list[0], &leds.list[1]);
Pantalla pantalla(&dht, &TEMP);

bool joystickXCanvi = false;

void setup() {
    obstacles.begin();
    botoAlarma.begin();
    joystick.begin();

    leds.begin();

    dht.begin();
    pantalla.begin();

    Serial.begin(9600);

    // Esperar fins que la comunicació estigui disponible
    while (!Serial);
}

void loop() {
    bool sensorsCanvi = dht.read();

    bool prevJx = joystickXCanvi;
    joystickXCanvi = joystick.read(X);

    bool tempSetCanvi = prevJx != joystickXCanvi;

    botoAlarma.read();
    obstacles.read();

    if (joystickXCanvi || *joystick.getPos(X) != 0) {
        int pos = *joystick.getPos(X);
        if (abs(pos) > 20) {
            TEMP += pos < 0 ? -1 : 1;
        }
        pantalla.update("Establint temp", String(TEMP));


    } else if (sensorsCanvi || tempSetCanvi) {
        pantalla.idle();
    }

    if (!obstacles.value) ALARMA = true;
    else if (botoAlarma.value) ALARMA = false;

    if ((millis()/1000)%2 == 0 && ALARMA) {
        leds.list[3] = CRGB::Red;
        leds.list[4] = CRGB::Red;
    } else {
        leds.list[3] = CRGB::Black;
        leds.list[4] = CRGB::Black;
    }

    leds.refresh();
}