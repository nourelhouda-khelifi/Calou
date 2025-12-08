#include <SeeedOLED.h>
#include "../../include/display_accueil.h"
#include <Arduino.h>
#include "../../include/calou_active.h"

// ========================================
// Écran d'accueil pour bracelet anti-stress
// Design ludique, rassurant et enfantin
// ========================================
int currentDisplayState = 0;

int currentSportState = 0;

void displayAccueil() {
    static unsigned long lastAnimTime = 0;
    static int animStep = 0;
    
    unsigned long currentTime = millis();
    
    // Animation toutes les 800ms pour un effet relaxant
    if(currentTime - lastAnimTime >= 800) {
        lastAnimTime = currentTime;
        animStep = (animStep + 1) % 4;
    }
    
    // ========== LIGNE 0 : En-tête avec décoration ==========
    SeeedOled.setTextXY(0, 0);
    
    // Afficher icônes décoratives selon animation
    if(animStep == 0) {
        SeeedOled.putString("* CALOU *");
    } else if(animStep == 1) {
        SeeedOled.putString("~ CALOU ~");
    } else if(animStep == 2) {
        SeeedOled.putString("o CALOU o");
    } else {
        SeeedOled.putString("+ CALOU +");
    }
    
    // ========== LIGNE 1 : Ligne séparatrice ==========
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("================");
    
    // ========== LIGNE 2 : Vide ==========
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("                ");
    
    // ========== LIGNE 3 : Message d'accueil chaleureux ==========
    SeeedOled.setTextXY(3, 1);
    SeeedOled.putString("Bonjour! :)");
    
    // ========== LIGNE 4 : Message rassurant ==========
    SeeedOled.setTextXY(4, 3);
    SeeedOled.putString("Je suis la");
    
    // ========== LIGNE 5 : Mascotte animée (cœur qui pulse) ==========
    SeeedOled.setTextXY(5, 5);
    if(animStep < 2) {
        SeeedOled.putString("<3 <3");
    } else {
        SeeedOled.putString(">< ><");
    }
    
    // ========== LIGNE 6 : Instruction claire ==========
    SeeedOled.setTextXY(6, 2);
    SeeedOled.putString("Pose ton doigt");
    
    // ========== LIGNE 7 : Pied de page avec animation ==========
    SeeedOled.setTextXY(7, 1);
    if(animStep == 0) {
        SeeedOled.putString(". . . . .");
    } else if(animStep == 1) {
        SeeedOled.putString("  . . .  ");
    } else if(animStep == 2) {
        SeeedOled.putString(". . . . .");
    } else {
        SeeedOled.putString("  . . .  ");
    }
}
void displayactivate(){
    // Check if this is the first time in this state since the last clear
    if (currentDisplayState == 1) { 
        SeeedOled.setTextXY(2, 0);
        SeeedOled.putString("Display Activate");
        // We do *not* set a static flag here, the global currentDisplayState handles it.
    }
    
    // This line updates continuously, regardless of the state change
    SeeedOled.setTextXY(3, 0);
    const char* stateString = activationOn ? "ON" : "OFF";
    SeeedOled.putString(stateString); 
}
void displaydeactivate(){
    // Check if this is the first time in this state since the last clear
    if (currentDisplayState == 2) { 
        SeeedOled.setTextXY(2, 0);
        SeeedOled.putString("Dis Deactivate");
    }
    
    // This line updates continuously, regardless of the state change
    SeeedOled.setTextXY(3, 0);
    const char* stateString = activationOn ? "ON" : "OFF";
    SeeedOled.putString(stateString);
}

void displaySport(){
    // Check if this is the first time in this state since the last clear
    if (currentSportState == 1) { 
        SeeedOled.setTextXY(0, 0);
        SeeedOled.putString("MODE SPORT");
        // We do *not* set a static flag here, the global currentDisplayState handles it.
    }
    
    // This line updates continuously, regardless of the state change
    SeeedOled.setTextXY(1, 0);
    const char* stateString = sportOn ? "ON" : "OFF";
    SeeedOled.putString(stateString); 
}

void displayNotSport(){
    // Check if this is the first time in this state since the last clear
    if (currentSportState == 2) { 
        SeeedOled.setTextXY(5, 0);
        SeeedOled.putString("NOT SPORT");
        // We do *not* set a static flag here, the global currentDisplayState handles it.
    }
    
    // This line updates continuously, regardless of the state change
    SeeedOled.setTextXY(6, 0);
    const char* stateString = sportOn ? "ON" : "OFF";
    SeeedOled.putString(stateString); 
}