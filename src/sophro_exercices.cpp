#include "../include/sophro_exercices.h"
#include "../include/bitmap.h"
#include <Arduino.h>
#include <SeeedOLED.h>
#include <Wire.h>

// Forward declarations
void inspirer_cycle();
void tenir_cycle(int nb_ms);
void expirer_cycle();

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
    
    // Affichage du compte à rebours 3-2-1
    for(int i = 3; i >= 1; i--) {
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
void exercice_sophro_normal() {
    premier_cycle();
    deuxieme_cycle();
    troisieme_cycle();
    quatrieme_cycle();
    cinquieme_cycle();
}

// ========================================
// 5 cycles avec durées croissantes
// ========================================
void premier_cycle() {
    inspirer_cycle();
    tenir_cycle(1000);
    expirer_cycle();
}

void deuxieme_cycle() {
    inspirer_cycle();
    tenir_cycle(2000);
    expirer_cycle();
}

void troisieme_cycle() {
    inspirer_cycle();
    tenir_cycle(3000);
    expirer_cycle();
}

void quatrieme_cycle() {
    inspirer_cycle();
    tenir_cycle(3000);
    expirer_cycle();
}

void cinquieme_cycle() {
    inspirer_cycle();
    tenir_cycle(4000);
    expirer_cycle();
}

// ========================================
// Inspiration - Bulle grandit progressivement
// ========================================
void inspirer_cycle() {
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
        SeeedOled.setTextXY(0, 0);
        SeeedOled.drawBitmap((unsigned char*)frames[i], TAILLE_BITMAP);
        SeeedOled.setTextXY(7, 5);
        SeeedOled.putString("Inspire");
        delay(frameDelay[i]);
    }
}

// ========================================
// Pause avec bulle au maximum
// ========================================
void tenir_cycle(int nb_ms) {
    commencer_affichage();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.drawBitmap((unsigned char*)ballon_etat7, TAILLE_BITMAP);
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Tiens");
    delay(nb_ms);
}

// ========================================
// Expiration - Bulle rétrécit progressivement
// ========================================
void expirer_cycle() {
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
}