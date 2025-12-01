#include <SeeedOLED.h>
#include "../../include/display_accueil.h"
#include <Arduino.h>

// ========================================
// Écran d'accueil pour bracelet anti-stress
// Design ludique, rassurant et enfantin
// ========================================

// Icône Cœur (8x8)
const unsigned char heart_icon[] = {
  0x00, 0x66, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C, 0x18
};

// Icône Étoile (8x8)
const unsigned char star_icon[] = {
  0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0x7E, 0x3C, 0x18
};

// Icône Nuage (8x8)
const unsigned char cloud_icon[] = {
  0x00, 0x38, 0x7C, 0xFE, 0xFE, 0x7C, 0x38, 0x00
};

void displayAccueil() {
    static unsigned long lastAnimTime = 0;
    static int animStep = 0;
    
    unsigned long currentTime = millis();
    
    // Animation toutes les 800ms pour un effet relaxant
    if(currentTime - lastAnimTime >= 800) {
        lastAnimTime = currentTime;
        animStep = (animStep + 1) % 4;
    }
    
    SeeedOled.clearDisplay();
    
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
