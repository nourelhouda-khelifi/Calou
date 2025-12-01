#include <Arduino.h>
#include <Wire.h>
#include <SeeedOLED.h>

#include "../include/sensor.h"
#include "../include/bpm.h"
#include "../include/analysis.h"
#include "../include/display_accueil.h"
#include "../include/display_alerte.h"
#include "../include/display_exercice.h"
#include "../include/sophro_exercices.h"

// Forward declaration au cas où
void afficher_countdown();
void exercice_sophro_normal();

unsigned long startWindow = 0;
bool affichageAccueil = false;

void setup() {
    Serial.begin(9600);
    Wire.begin();
    SeeedOled.init();
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();

    displayAccueil();
    startWindow = millis();
}

void loop() {
    int valeur = lireCapteur();

    if(!doigtPresent(valeur)) {
        if(!affichageAccueil){
            displayAccueil();
            affichageAccueil = true;
        }
        return;
    } else {
        affichageAccueil = false;
    }

    int bpm = detecterBPM(valeur);
    (void)bpm;

    if(millis() - startWindow >= 30000){
        const char* etat = analyserStress();

        if(strcmp(etat,"STRESS") == 0){
            // Afficher countdown 3-2-1
            afficher_countdown();
            
            // Exercice sophro avec bulle animée
            exercice_sophro_normal();
            
            // Retour à l'écran d'accueil
            displayAccueil();
            affichageAccueil = true;
        }
        // Si état calme : ne rien afficher (garder l'écran d'accueil)

        startWindow = millis();
    }

    delay(5);
}
