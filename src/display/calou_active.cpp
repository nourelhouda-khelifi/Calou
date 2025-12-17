#include <Arduino.h>
#include "./detection/sensor.h"
#include "./detection/bpm.h"
#include "./detection/analysis.h"
#include "display_accueil.h"
#include "sophro_exercices.h"

const int buttonPin = 12;        
const int sportPin = 13;  

const unsigned long debounceDelay = 50;
const unsigned long LONG_PRESS_DURATION = 3000;
unsigned long lastDebounceTimeActive = 0;
unsigned long pressStartTimeActive; 
int buttonActiveState = HIGH;
int lastButtonActiveState = HIGH;

unsigned long lastDebounceTimeSport = 0;
unsigned long pressStartTimeSport; 
int buttonSportState = HIGH;
int lastButtonSportState = HIGH;

bool activationOn = false;  
bool sportOn = false;

/**
 * @brief Lit un bouton, applique un anti-rebond, et enregistre un appui seulement s'il est maintenu 3 secondes.
 * @return true si un changement d'état du bouton (appui OU relâchement) s'est produit.
 */

bool updateActivateBouton() {
    bool stateChanged = false;
    int readingActive = digitalRead(buttonPin);
    int readingSport = digitalRead(sportPin);
    static bool buttonActiveRegistered = false; // Indique si l'appui long a déjà été traité
    static bool buttonSportRegistered = false; 

    // 1. Réinitialiser le minuteur si la lecture brute change
    if (readingActive != lastButtonActiveState) {
        lastDebounceTimeActive = millis();
    }
    if (readingSport != lastButtonSportState) {
        lastDebounceTimeSport = millis();
    }

    // 2. Vérifier la stabilité après anti-rebond
    if ((millis() - lastDebounceTimeActive) > debounceDelay) {
        
        // --- A. Si l'état stable A changé ---
        // Bouton Active
        if (readingActive != buttonActiveState) {
        
            // Mettre à jour l'état stable
            buttonActiveState = readingActive;
            stateChanged = true;
            
            if (buttonActiveState == LOW) {
                // Le bouton vient de passer à l'état stable LOW (appuyé)
                // DÉMARRER le suivi de la durée d'appui
                pressStartTimeActive = millis(); 
                Serial.println("Bouton Active stable LOW. Démarrage du minuteur.");
            } else {
                // Le bouton vient de passer à l'état stable HIGH (relâché)
                Serial.println("Bouton Active relâché.");                
                // Réinitialiser le drapeau d'enregistrement au relâchement
                buttonActiveRegistered = false; 
            }
        }

        // Bouton Sport
        if (readingSport != buttonSportState) {
            buttonSportState = readingSport;
            stateChanged = true;
            
            if (buttonSportState == LOW) {
                pressStartTimeSport = millis(); 
                Serial.println("Bouton SPORT stable LOW. Démarrage du minuteur.");
            } else {
                Serial.println("Bouton SPORT relâché.");                
                buttonSportRegistered = false; 
            }
        }

        // --- B. Vérification de l'appui long (Uniquement si le bouton est actuellement appuyé) ---
        //Bouton Active
        if (buttonActiveState == LOW) {
            
            // Vérifier si la durée requise est écoulée ET si l'action n'a pas encore été exécutée
            if ((millis() - pressStartTimeActive >= LONG_PRESS_DURATION) && !buttonActiveRegistered) {
                
                // --- ACTION : Appui long ENREGISTRÉ (3+ secondes) ! ---
                Serial.println("--- Appui long REGISTERED (3+ secondes) ! ---");
                
                // 1. Basculer la variable de l'application
                activationOn = !activationOn;
                
                // 2. Marquer l'action comme faite pour ne pas la redéclencher avant relâchement/ré-appui
                buttonActiveRegistered = true; 
                
                // Note : stateChanged reste faux car l'état physique du bouton
                // (LOW) n'a pas changé, seul l'état de l'*application* a changé.
            }
        }

        //Bouton Sport
        if (buttonSportState == LOW) {

            if ((millis() - pressStartTimeSport >= LONG_PRESS_DURATION) && !buttonSportRegistered) {
                Serial.println("--- Appui long SPORT REGISTERED (3+ secondes) ! ---");
                sportOn = !sportOn;
                buttonSportRegistered = true; 
            }
        }
    }

    // 3. Sauvegarder la lecture brute actuelle pour la prochaine itération de la boucle
    lastButtonActiveState = readingActive;
    lastButtonSportState = readingSport;
    delay(50); // Petite pause pour éviter une boucle trop rapide
    return stateChanged;
}