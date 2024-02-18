#include <Arduino.h>
#include "EntradaDigital.h"
#include "../lib/DHT_sensor_library-1.4.6/DHT.h"

EntradaDigital obstacles(5);
EntradaDigital botoAlarma(23);
DHT dht14(14, DHT11);

void setup() {
    obstacles.begin();
    dht14.begin();
}

void loop() {
    obstacles.pulseIn();
}