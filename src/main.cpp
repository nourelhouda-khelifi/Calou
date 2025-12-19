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
int bpm_affiche = 0;      // Partagé avec les autres fichiers
unsigned long lastBpmUpdate = 0; 
unsigned long lastAnimationUpdate = 0;
int currentImageIndex = 0;       // Pour alterner les images de l'animation
int lastCalculatedBPM = 0;

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
    sportOn = false;
    SeeedOled.setTextXY(0, 0);
}

void displayactivate(){
    // Change image every 200ms
    if (millis() - lastAnimationUpdate >= 200) {
        
        if (currentImageIndex == 0) {
            SeeedOled.drawBitmap((unsigned char*)chat_accueil2, TAILLE_BITMAP);
            currentImageIndex = 1;
        } else {
            SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
            currentImageIndex = 0;
        }

        SeeedOled.setTextXY(7, 7);
        SeeedOled.putNumber(bpm_affiche);
        
        // Timer reset
        lastAnimationUpdate = millis();

    }
}



void loop() {
    SeeedOled.setTextXY(0,0 );
    updateActivateBouton(); 

    if (activationOn) {

        if (currentDisplayState != 1) {
            SeeedOled.clearDisplay();
            currentDisplayState = 1; 
            affichageAccueil = true; 
            // Draw initial image
            SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
        } 

        // SPORT LOGIC
        if(sportOn){
            if(currentSportState!=1){
                SeeedOled.clearDisplay();
                currentSportState = 1; 
            }
            displaySport(); 
            return;
        } else {
            if (currentSportState != 2) {
                SeeedOled.clearDisplay();
                currentSportState = 2; 
                SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
            }
            
            displayactivate(); 
        }

        int valeur = lireCapteur();

        if (!doigtPresent(valeur)) {
            return; 
        }

        detecterBPM(valeur); 

        if (millis() - startWindow >= 30000) {
            const char* etat = analyserStress();

            if (strcmp(etat,"STRESS") == 0) {
                delay(50);
                afficher_countdown();
                if(!exercice_sophro_normal()){
                    SeeedOled.clearDisplay();
                    currentDisplayState = 0; 
                    return;
                }
                
                // Reset after exercise
                SeeedOled.clearDisplay();
                SeeedOled.drawBitmap((unsigned char*)chat_accueil, TAILLE_BITMAP);
                currentDisplayState = 1; 
                startWindow = millis();
            } else {
                startWindow = millis();
            }
        }

    } else {
        // --- MODE DÉSACTIVÉ ---
        if (currentDisplayState != 2) {
            SeeedOled.clearDisplay();
            currentDisplayState = 2; 
        }
    }

    delay(5); 
}