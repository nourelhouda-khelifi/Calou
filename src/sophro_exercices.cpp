#include "sophro_exercices.h"
#include "bitmap.h"

// Forward declarations for functions used before their definitions
void exercice_sophro_normal();
void commencer_affichage();
void premier_cycle();
void deuxieme_cycle();
void troisieme_cycle();
void quatrieme_cycle();
void cinquieme_cycle();
void inspirer_cycle();
void tenir_cycle(int nb_ms);
void expirer_cycle();

void exercice_sophro_normal(){
    premier_cycle();
    deuxieme_cycle();
    troisieme_cycle();
    quatrieme_cycle();
    cinquieme_cycle();
}


void commencer_affichage(){
    SeeedOled.clearDisplay();          
    SeeedOled.setNormalDisplay();      
    SeeedOled.setPageMode();  
    SeeedOled.setTextXY(4, 7);
}


void premier_cycle(){
    inspirer_cycle();
    tenir_cycle(1000);
    expirer_cycle();
}

void deuxieme_cycle(){
    inspirer_cycle();
    tenir_cycle(2000);
    expirer_cycle();
}

void troisieme_cycle(){
    inspirer_cycle();
    tenir_cycle(3000);
    expirer_cycle();
}

void quatrieme_cycle(){
    inspirer_cycle();
    tenir_cycle(3000);
    expirer_cycle();
}

void cinquieme_cycle(){
    inspirer_cycle();
    tenir_cycle(4000);
    expirer_cycle();
}



void inspirer_cycle() {
    static const unsigned char* const frames[] = {
        ballon_etat1,
        ballon_etat2,
        ballon_etat3,
        ballon_etat4,
        ballon_etat5,
        ballon_etat6
    };

    // 6 delays of 500 ms
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


void tenir_cycle(int nb_ms){
    commencer_affichage();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat7, TAILLE_BITMAP);
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Tiens");
    delay(nb_ms);
}

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

    // Per-frame delays (ms)
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

    commencer_affichage();
    SeeedOled.setTextXY(0, 0);
    SeeedOled.drawBitmap((unsigned char*)ballon_etat1, TAILLE_BITMAP);
    SeeedOled.setTextXY(7, 5);
    SeeedOled.putString("Bravo!");
    delay(2000);
}