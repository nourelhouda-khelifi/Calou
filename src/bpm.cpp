#include "../include/bpm.h"

const int seuil_pic = 20;
const int bpm_min = 50;
const int bpm_max = 150;

unsigned long lastBeat = 0;
float baseline = 0;

int bpm_values[200];
int bpm_index = 0;

// 🔥 VERSION CORRIGÉE : detecterBPM retourne maintenant un int
int detecterBPM(int valeur) {

    baseline = baseline * 0.9 + valeur * 0.1; // filtrage baseline

    if (valeur > baseline + seuil_pic) {

        unsigned long now = millis();

        if (now - lastBeat > 300) { // anti double battement

            int bpm = 60000 / (now - lastBeat);

            lastBeat = now;

            if (bpm >= bpm_min && bpm <= bpm_max) {

                bpm_values[bpm_index++] = bpm;

                Serial.print("BPM : ");
                Serial.println(bpm);

                return bpm;   // 🔥 maintenant on retourne le BPM !
            }
        }
    }

    return 0;  // 🔥 aucun battement détecté
}

int getBPMCount() {
    return bpm_index;
}

float getMeanBPM() {
    if (bpm_index == 0) return 0;

    float somme = 0;
    for (int i = 0; i < bpm_index; i++) somme += bpm_values[i];

    return somme / bpm_index;
}

void resetBPM() {
    bpm_index = 0;
}
