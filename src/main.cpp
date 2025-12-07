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
#include "../include/calou_active.h"


bool affichageAccueil = false;
unsigned long startWindow = 0;


// 1. GLOBAL VARIABLES: These MUST be defined outside of any function

void setup() {
    Serial.begin(9600);
    Wire.begin();
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(sportPin, INPUT_PULLUP);
    SeeedOled.init();
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();
    startWindow = millis();
    activationOn = false;
}

// Assurez-vous que ces variables sont globales/externes et définies.
// extern bool activationOn;
// extern int currentDisplayState; // 1: Active, 2: Deactive
// extern bool affichageAccueil;
// extern unsigned long startWindow; 
// extern const int buttonPin;
// extern const unsigned long debounceDelay; 
// ... etc.

void loop() {
    // 1. GESTION DU BOUTON (Doit toujours s'exécuter)
    // Ceci met à jour la variable 'activationOn' et gère le long-press.
    updateActivateBouton(); 

    // 2. LOGIQUE PRINCIPALE DU SYSTÈME
    if (activationOn) {
        // --- A. MODE ACTIVÉ (Le système de monitoring est ON) ---
        
        // Gérer le changement d'écran initial si l'état vient de passer à ACTIF
        if (currentDisplayState != 1) {
            SeeedOled.clearDisplay();
            currentDisplayState = 1; 
            // Lors de l'activation, on s'attend à être sur l'écran d'accueil du capteur.
            affichageAccueil = true; 
        }
        
        // Mettre à jour la ligne d'état de l'écran ACTIF
        displayactivate(); 

        // 3. LOGIQUE DU CAPTEUR ET DÉTECTION DE STRESS
        int valeur = lireCapteur();

        // Vérification de la présence du doigt
        if (!doigtPresent(valeur)) {
            return; // Sortir de la boucle : inutile de faire d'autres calculs sans doigt
        }

        // Calculer le BPM (même si on n'est pas encore à 30s)
        int bpm = detecterBPM(valeur);
        (void)bpm; // Supprime l'avertissement si bpm n'est pas utilisé directement ici

        // Vérifier si la fenêtre d'analyse de 30 secondes est écoulée
        if (millis() - startWindow >= 30000) {
            const char* etat = analyserStress();

            if (strcmp(etat,"STRESS") == 0) {
                delay(50);
                // Stress détecté : Lancer l'exercice
                afficher_countdown();
                if(!exercice_sophro_normal()){
                    SeeedOled.clearDisplay();
                    displaydeactivate();
                    return;
                }
                
                // Après l'exercice, revenir à l'écran d'accueil/monitoring
                displayactivate();                
                // Remise à zéro de l'état d'affichage pour forcer le redraw
                currentDisplayState = 0; 
            }
            
            // Si état calme ou après un exercice, on réinitialise le minuteur
            startWindow = millis();
        }

    } else {
        // --- B. MODE DÉSACTIVÉ (Le système est OFF) ---
        
        // Gérer le changement d'écran initial si l'état vient de passer à DÉSACTIVÉ
        if (currentDisplayState != 2) {
            SeeedOled.clearDisplay();
            currentDisplayState = 2; 
        }
        
        // Mettre à jour la ligne d'état de l'écran DÉSACTIVÉ
        displaydeactivate();
    }

    // Petite pause pour ne pas surcharger le processeur
    delay(5); 
}