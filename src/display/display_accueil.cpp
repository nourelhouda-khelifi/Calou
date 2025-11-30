#include <SeeedOLED.h>
#include "../../include/display_accueil.h"
#include <Arduino.h>

// ========================================
// Écran d'accueil moderne et animé
// ========================================
void displayAccueil() {
    static unsigned long lastAnimTime = 0;
    static int animStep = 0;
    
    unsigned long currentTime = millis();
    
    // Animation toutes les 600ms
    if(currentTime - lastAnimTime >= 600) {
        lastAnimTime = currentTime;
        animStep = (animStep + 1) % 4;
    }
    
    SeeedOled.clearDisplay();
    
    // ========== LIGNE 1 : Titre avec décoration ==========
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("  << CALOU >>");
    
    // ========== LIGNE 2 : Barre de séparation animée ==========
    SeeedOled.setTextXY(1, 0);
    const char* barres[] = {
        "~~~~~~~~~~~~~~~~",
        "================",
        "~~~~~~~~~~~~~~~~",
        "~~~~~~~~~~~~~~~~"
    };
    SeeedOled.putString(barres[animStep]);
    
    // ========== LIGNE 3 : Vide ==========
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("                ");
    
    // ========== LIGNE 4 : Message principal ==========
    SeeedOled.setTextXY(3, 1);
    SeeedOled.putString("Detente & Bien-etre");
    
    // ========== LIGNE 5 : Sous-message ==========
    SeeedOled.setTextXY(4, 3);
    SeeedOled.putString("Mets ton doigt!");
    
    // ========== LIGNE 6 : Vide ==========
    SeeedOled.setTextXY(5, 0);
    SeeedOled.putString("                ");
    
    // ========== LIGNE 7 : Animation de pulse ==========
    SeeedOled.setTextXY(6, 4);
    const char* pulses[] = {
        "   o   ",
        "  o o  ",
        " o   o ",
        "  o o  "
    };
    SeeedOled.putString(pulses[animStep]);
    
    // ========== LIGNE 8 : Footer avec chevrons ==========
    SeeedOled.setTextXY(7, 1);
    SeeedOled.putString(">>> en attente <<<");
}
