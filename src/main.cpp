#include <Arduino.h>
#include "EntradaDigital.h"
#include <DHT.h>

EntradaDigital obstacles(5);
EntradaDigital botoAlarma(23);

void setup() {
    obstacles.setup();
}

void loop() {
    obstacles.pulseIn();
}