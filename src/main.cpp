#include <Arduino.h>
#include <Wire.h>
#include <SeeedOLED.h>

#include "sensor.h"
#include "bpm.h"
#include "analysis.h"
#include "display_accueil.h"
#include "display_alerte.h"
#include "display_exercice.h"
#include "display_resultat.h"

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
        float moyenne = getMeanBPM();

        if(strcmp(etat,"STRESS") == 0){
            displayAlerte();
            delay(2000); // pause 2s

            // Exercice respiratoire : 5 cycles
            for(int i=1;i<=5;i++){
                displayExercice(i,true);  // inspiration 4s
                delay(4000);
                displayExercice(i,false); // expiration 6s
                delay(6000);
            }

            // Ecran félicitations
            displayResult(moyenne,"Calme :)");
            delay(3000);
        } else {
            displayResult(moyenne,etat);
            delay(3000);
        }

        startWindow = millis();
    }

    delay(5);
}
