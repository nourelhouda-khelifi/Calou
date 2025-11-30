#include "../include/sensor.h"

const int seuil_doigt = 30;

// Filtre médian 5 mesures
int lireCapteur() {
    int v[5];
    for (int i = 0; i < 5; i++) {
        v[i] = analogRead(SENSOR_PIN);
        delay(2);
    }

    // Tri pour trouver médiane
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++)
            if (v[j] < v[i]) {
                int tmp = v[i]; v[i] = v[j]; v[j] = tmp;
            }

    return v[2]; // valeur médiane
}

bool doigtPresent(int valeur) {
    return valeur >= seuil_doigt;
}
