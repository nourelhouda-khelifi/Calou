#include <Arduino.h>
#include "sensor.h"
#include "bpm.h"
#include "analysis.h"
#include "display.h"   // <= AJOUT POUR L’ÉCRAN

unsigned long startWindow = 0;

void setup() {
    Serial.begin(9600);
    
    // --- INIT ECRAN OLED ---
    displayInit();
    displayClear();
    displayShowState("Init...");
    
    Serial.println("=== KY039 ANALYSE 30s ===");

    startWindow = millis();
}

void loop() {
    int valeur = lireCapteur();

    // --- Vérifier la présence du doigt ---
    if (!doigtPresent(valeur)) {
        Serial.println("Pas de doigt");
        return;
    }

    // --- Calcul BPM ---
    int bpm = detecterBPM(valeur);
    (void)bpm;

    

    // --- Analyse fenêtre 30s ---
    if (millis() - startWindow >= 30000) {
        const char* etat = analyserStress();
        
        float moyenne = getMeanBPM();          // moyenne des BPM sur la fenêtre

        // Affichage OLED du résultat (moyenne + état)
        displayShowResult(moyenne, etat);

        // Affichage console pour debug
        Serial.print("Moyenne BPM: "); Serial.println(moyenne);
        Serial.print("Etat: "); Serial.println(etat);

        // Réinitialisation de la fenêtre
        startWindow = millis();
    }

    delay(5);
}
