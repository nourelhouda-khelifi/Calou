#include <Arduino.h>
#include "sensor.h"
#include "bpm.h"
#include "analysis.h"

unsigned long startWindow = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("=== KY039 ANALYSE 30s ===");
}

void loop() {
    int valeur = lireCapteur();

    if (!doigtPresent(valeur)) {
        Serial.println("Pas de doigt");
        delay(50);
        return;
    }

    detecterBPM(valeur);

    if (millis() - startWindow >= 30000) {
        analyserStress();
        startWindow = millis();
    }

    delay(5);
}
