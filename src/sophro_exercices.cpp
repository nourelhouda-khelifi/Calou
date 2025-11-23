#include "sophro_exercices.h"
#include "bitmap.h"

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


void inspirer_cycle(){
    commencer_affichage();

    SeeedOled.putString("Inspire");
    SeeedOled.drawBitmap((unsigned char*) ballon_etat1, TAILLE_BITMAP);
    delay(500);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat2, TAILLE_BITMAP);
    delay(500);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat3, TAILLE_BITMAP);
    delay(500);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat4, TAILLE_BITMAP);
    delay(500);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat5, TAILLE_BITMAP);
    delay(500);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat6, TAILLE_BITMAP);
    delay(500);
    //Trois secondes d'inspiration
}

void tenir_cycle(int nb_ms){
    commencer_affichage();

    SeeedOled.putString("Tiens la respiration");
    SeeedOled.drawBitmap((unsigned char*) ballon_etat7, TAILLE_BITMAP);
    delay(nb_ms);
}

void expirer_cycle(){
    commencer_affichage();
    SeeedOled.putString("Souffle doucement");
    SeeedOled.drawBitmap((unsigned char*) ballon_etat6, TAILLE_BITMAP);
    delay(1000);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat5, TAILLE_BITMAP);
    delay(1000);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat4, TAILLE_BITMAP);
    delay(1000);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat3, TAILLE_BITMAP);    
    delay(1000);
    SeeedOled.drawBitmap((unsigned char*) ballon_etat2, TAILLE_BITMAP);
    delay(1000);
    commencer_affichage();
    SeeedOled.putString("Bravo!");
    SeeedOled.drawBitmap((unsigned char*) ballon_etat1, TAILLE_BITMAP);
    delay(2000);
}