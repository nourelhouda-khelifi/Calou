#include "calou_active.h"

// --- PARAMÈTRES TEMPORELS ---
const unsigned long debounceDelay = 50;         // Temps de stabilisation (anti-rebond) en ms
const unsigned long LONG_PRESS_DURATION = 3000; // Seuil pour l'appui long (3 secondes)

// --- VARIABLES D'ÉTAT (BOUTON ACTIVE) ---
unsigned long lastDebounceTimeActive = 0; // Dernier moment où le signal a bougé
unsigned long pressStartTimeActive;       // Heure précise du début de l'appui
int buttonActiveState = HIGH;             // État stable actuel (HIGH = relâché en PULL-UP)
int lastButtonActiveState = HIGH;         // Dernière lecture brute enregistrée

// --- VARIABLES D'ÉTAT (BOUTON SPORT) ---
unsigned long lastDebounceTimeSport = 0;
unsigned long pressStartTimeSport; 
int buttonSportState = HIGH;
int lastButtonSportState = HIGH;

// --- VARIABLES DE SORTIE (L'ÉTAT DU SYSTÈME) ---
bool activationOn = false;  // Le système est-il allumé ?
bool sportOn = false;        // Le mode sport est-il actif ?

/**
 * Gère la lecture des boutons, l'anti-rebond et la logique des 3 secondes.
 * @return true si l'état PHYSIQUE d'un bouton a changé.
 */
bool updateActivateBouton() {
    bool stateChanged = false;
    
    // Lecture brute instantanée des broches
    int readingActive = digitalRead(buttonPin);
    int readingSport = digitalRead(sportPin);

    // Drapeaux statiques pour ne déclencher l'action "3s" qu'une seule fois par appui
    static bool buttonActiveRegistered = false; 
    static bool buttonSportRegistered = false; 

    // --- 1. DÉTECTION DE CHANGEMENT BRUT (Anti-rebond) ---
    // Si le doigt bouge, on réinitialise le chrono de stabilité (Debounce)
    if (readingActive != lastButtonActiveState) {
        lastDebounceTimeActive = millis();
    }
    if (readingSport != lastButtonSportState) {
        lastDebounceTimeSport = millis();
    }

    // --- 2. TRAITEMENT SI LE SIGNAL EST STABLE (après 50ms) ---
    if ((millis() - lastDebounceTimeActive) > debounceDelay) {
        
        // A. Changement d'état stable pour le bouton ACTIVE
        if (readingActive != buttonActiveState) {
            buttonActiveState = readingActive; // On valide le nouvel état
            stateChanged = true;
            
            if (buttonActiveState == LOW) { // LOW signifie "Appuyé" (montage Pull-Up)
                pressStartTimeActive = millis(); // On commence à compter les 3 secondes
                Serial.println("Bouton Active stable LOW. Démarrage du minuteur.");
            } else {
                buttonActiveRegistered = false; // On autorise un futur appui long au relâchement
                Serial.println("Bouton Active relâché.");                
            }
        }

        // Changement d'état stable pour le bouton SPORT
        if (readingSport != buttonSportState) {
            buttonSportState = readingSport;
            stateChanged = true;
            
            if (buttonSportState == LOW) {
                pressStartTimeSport = millis(); 
                Serial.println("Bouton SPORT stable LOW. Démarrage du minuteur.");
            } else {
                buttonSportRegistered = false; 
                Serial.println("Bouton SPORT relâché.");                
            }
        }

        // --- B. VÉRIFICATION DE LA DURÉE (L'appui long) ---
        
        // Logique pour le bouton ACTIVE : si appuyé depuis plus de 3s
        if (buttonActiveState == LOW) {
            if ((millis() - pressStartTimeActive >= LONG_PRESS_DURATION) && !buttonActiveRegistered) {
                Serial.println("--- Appui long REGISTERED (3+ secondes) ! ---");
                activationOn = !activationOn;  // On bascule l'état (ON/OFF)
                buttonActiveRegistered = true; // Empêche de basculer en boucle sans relâcher
            }
        }

        // Logique pour le bouton SPORT
        if (buttonSportState == LOW) {
            if ((millis() - pressStartTimeSport >= LONG_PRESS_DURATION) && !buttonSportRegistered) {
                Serial.println("--- Appui long SPORT REGISTERED (3+ secondes) ! ---");
                sportOn = !sportOn;            // On bascule le mode sport (ON/OFF)
                buttonSportRegistered = true; 
            }
        }
    }

    // --- 3. MÉMOIRE ET MAINTENANCE ---
    lastButtonActiveState = readingActive; // Sauvegarde pour la prochaine lecture
    lastButtonSportState = readingSport;
    
    delay(50); // Limite la vitesse de la boucle pour économiser le processeur
    return stateChanged;
}