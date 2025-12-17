#include <Arduino.h>
#include <Wire.h>
#include <SeeedOLED.h>

// Importation de tes modules personnalisés
#include "./detection/sensor.h"
#include "./detection/bpm.h"
#include "./detection/analysis.h"
#include "./display/display_accueil.h"
#include "./display/sophro_exercices.h"
#include "./display/calou_active.h"
#include "./display/bitmap.h"

// --- VARIABLES GLOBALES ---
bool affichageAccueil = false;
unsigned long startWindow = 0;   // Chrono pour la fenêtre d'analyse de 30s
extern int bpm_affiche = 0;      // Partagé avec les autres fichiers
unsigned long lastBpmUpdate = 0; 
unsigned long lastAnimationUpdate = 0;
int currentImageIndex = 0;       // Pour alterner les images de l'animation
int lastCalculatedBPM = 0;


// ========================================
// CONFIGURATION INITIALE
// ========================================
void setup() {
    Serial.begin(9600);
    Wire.begin();
    
    // Configuration des boutons avec résistances internes
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(sportPin, INPUT_PULLUP);
    
    // Initialisation de l'écran OLED
    SeeedOled.init();
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();
    
    startWindow = millis(); // Démarre le compteur de temps
    activationOn = false;   // Bracelet éteint par défaut
    sportOn = false;
}

// ========================================
// ANIMATION DE L'ÉCRAN ACTIF
// ========================================
void displayactivate(){
    // Change d'image toutes les 200ms pour créer un petit gif du chat
    if (millis() - lastAnimationUpdate >= 200) {
        
        if (currentImageIndex == 0) {
            SeeedOled.drawBitmap((unsigned char*)chat_accueil2, TAILLE_BITMAP);
            currentImageIndex = 1;
        } else {
            SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
            currentImageIndex = 0;
        }

        // Affiche le dernier BPM calculé en bas à droite
        SeeedOled.setTextXY(7, 7);
        SeeedOled.putNumber(bpm_affiche);
        
        lastAnimationUpdate = millis();
    }
}

// ========================================
// BOUCLE PRINCIPALE (LOOP)
// ========================================
void loop() {
    updateActivateBouton(); // Vérifie si l'utilisateur appuie sur les boutons

    if (activationOn) { // --- SI LE BRACELET EST ALLUMÉ ---

        // Gestion du changement d'état vers "Ecran Actif"
        if (currentDisplayState != 1) {
            SeeedOled.clearDisplay();
            currentDisplayState = 1; 
            affichageAccueil = true; 
            SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
        } 

        // LOGIQUE MODE SPORT (Prioritaire)
        if(sportOn){
            if(currentSportState != 1){
                SeeedOled.clearDisplay();
                currentSportState = 1; 
            }
            displaySport(); 
            return; // On saute la suite pour rester sur l'animation sport
        } else {
            // Retour au mode normal si on quitte le sport
            if (currentSportState != 2) {
                SeeedOled.clearDisplay();
                currentSportState = 2; 
                SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
            }
            displayactivate(); // Affiche le chat qui bouge
        }

        // --- MESURE DU CŒUR ---
        int valeur = lireCapteur(); // Filtre médian

        if (!doigtPresent(valeur)) {
            return; // Si pas de doigt, on s'arrête là pour cette itération
        }

        detecterBPM(valeur); // Calcule et stocke le BPM dans le tableau

        // --- ANALYSE DE STRESS (Toutes les 30 secondes) ---
        if (millis() - startWindow >= 30000) {
            const char* etat = analyserStress();

            if (strcmp(etat, "STRESS") == 0) {
                // Déclenchement de l'exercice si stressé
                delay(50);
                afficher_countdown();
                if(!exercice_sophro_normal()){
                    // Si l'utilisateur quitte l'exercice
                    SeeedOled.clearDisplay();
                    currentDisplayState = 0; 
                    return;
                }
                
                // Reset de l'écran après la sophrologie
                SeeedOled.clearDisplay();
                SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
                currentDisplayState = 1; 
                startWindow = millis(); // Relance le chrono de 30s
            } else {
                // Si CALME, on repart juste pour 30s de mesure
                startWindow = millis();
            }
        }

    } else {
        // --- MODE DÉSACTIVÉ (Éteint) ---
        if (currentDisplayState != 2) {
            SeeedOled.clearDisplay();
            currentDisplayState = 2; 
        }
    }

    delay(5); // Petite pause pour la stabilité du système
}