#include <SeeedOLED.h>
#include <Arduino.h>
#include "display_accueil.h"
#include "calou_active.h"
#include "bitmap.h"
//TO BE REMOVED LATER

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
// --- ANIMATION FUNCTION ---

void displaydeactivate(){
    SeeedOled.clearDisplay();
}

void displaySport(){
    // Check if this is the first time in this state since the last clear
    if (currentSportState == 1) { 
        SeeedOled.setTextXY(0, 0);
        SeeedOled.drawBitmap((unsigned char*)naruto_1, TAILLE_BITMAP);
        delay(10);
        SeeedOled.drawBitmap((unsigned char*)naruto_2, TAILLE_BITMAP);
        delay(10);
        SeeedOled.drawBitmap((unsigned char*)naruto_3, TAILLE_BITMAP);
        delay(10);
    }
}

void displayNotSport(){
    
}