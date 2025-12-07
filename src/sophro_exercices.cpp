#include "../include/sophro_exercices.h"
#include "../include/bitmap.h"
#include "../include/display_accueil.h"
#include "../include/calou_active.h"
#include <Arduino.h>
#include <SeeedOLED.h>
#include <Wire.h>

// Forward declarations
bool inspirer_cycle();
bool tenir_cycle(int nb_ms);
bool expirer_cycle();
bool verifierActivation();
bool cycle(int tenir_secondes);

// ========================================
// Affichage initial
// ========================================
void commencer_affichage() {
    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();
}

// ========================================
// Countdown avant l'exercice : 3-2-1
// ========================================
void afficher_countdown() {
    commencer_affichage();
    
    // Titre
    SeeedOled.setTextXY(1, 2);
    SeeedOled.putString("EXERCICE");
    SeeedOled.setTextXY(2, 3);
    SeeedOled.putString("SORPHO");
    if(!verifierActivation()){
        return;
    }
    
    // Affichage du compte à rebours 3-2-1
    for(int i = 3; i >= 1; i--) {
        if(!verifierActivation()){
            return;
        }
        commencer_affichage();
        
        SeeedOled.setTextXY(1, 2);
        SeeedOled.putString("EXERCICE");
        SeeedOled.setTextXY(2, 3);
        SeeedOled.putString("SORPHO");
        
        SeeedOled.setTextXY(4, 6);
        SeeedOled.putNumber(i);
        
        delay(1000);
    }
    
    // Message "C'est parti!"
    commencer_affichage();
    SeeedOled.setTextXY(2, 3);
    SeeedOled.putString("C'est parti !");
    delay(1500);
}

// ========================================
// Exercice Sorpho Normal
// ========================================
bool exercice_sophro_normal() {
    int tenir_secondes = 1000;
    for(int i = 0; i < 5; i++){
        if(!cycle(tenir_secondes)){
            return false;
        }
        if(i!=3){
            tenir_secondes+=1000;
        }
    }
    return true;
}

// ========================================
// 5 cycles avec durées croissantes
// ========================================

bool cycle(int tenir_secondes){
    if (inspirer_cycle() && tenir_cycle(tenir_secondes) && expirer_cycle()) {
        return true; 
    } else {
        return false; 
    }
}


// ========================================
// Inspiration - Bulle grandit progressivement
// ========================================
bool inspirer_cycle() {
    static const unsigned char* const frames[] = {
        ballon_etat1,
        ballon_etat2,
        ballon_etat3,
        ballon_etat4,
        ballon_etat5,
        ballon_etat6
    };

    const uint16_t frameDelay[6] = {500, 500, 500, 500, 500, 500};
    const uint8_t frameCount = sizeof(frames) / sizeof(frames[0]);

    commencer_affichage();
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Inspire");

    for (uint8_t i = 0; i < frameCount; i++) {
        if(!verifierActivation()){
            return false;
        }
        SeeedOled.setTextXY(0, 0);
        SeeedOled.drawBitmap((unsigned char*)frames[i], TAILLE_BITMAP);
        SeeedOled.setTextXY(7, 5);
        SeeedOled.putString("Inspire");
        delay(frameDelay[i]);
    }
    return true;
}

// ========================================
// Pause avec bulle au maximum
// ========================================
bool tenir_cycle(int nb_ms) {
    commencer_affichage();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.drawBitmap((unsigned char*)ballon_etat7, TAILLE_BITMAP);
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Tiens");
    if(!verifierActivation()){
        return false;
    }
    delay(nb_ms);
    return true;
}

// ========================================
// Expiration - Bulle rétrécit progressivement
// ========================================
bool expirer_cycle() {
    static const unsigned char* const frames[] = {
        ballon_etat6,
        ballon_etat5,
        ballon_etat4,
        ballon_etat3,
        ballon_etat2,
        ballon_etat1
    };

    const uint8_t frameCount = sizeof(frames) / sizeof(frames[0]);
    const uint16_t frameDelay[6] = {1000, 1000, 1000, 1000, 1000, 1000};

    commencer_affichage();
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Souffle");

    for (uint8_t i = 0; i < frameCount; i++) {
        if(!verifierActivation()){
            return false;
        }
        SeeedOled.setTextXY(0, 0);
        SeeedOled.drawBitmap((unsigned char*)frames[i], TAILLE_BITMAP);
        SeeedOled.setTextXY(7, 5);
        SeeedOled.putString("Souffle");
        delay(frameDelay[i]);
    }

    // "Bravo!" après chaque cycle
    commencer_affichage();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.drawBitmap((unsigned char*)ballon_etat1, TAILLE_BITMAP);
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Bravo!");
    delay(2000);
    return true;
}

bool verifierActivation(){
    updateActivateBouton();
    if(!activationOn){
        SeeedOled.clearDisplay();
        displaydeactivate();
    }
    return activationOn;
}