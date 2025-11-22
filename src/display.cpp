#include <SeeedOLED.h>
#include <Wire.h>
#include "display.h"

void displayInit() {
    Wire.begin();
    SeeedOled.init();          
    SeeedOled.clearDisplay();  
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();
}

// Effacer écran
void displayClear() {
    SeeedOled.clearDisplay();
}

// Afficher un message simple (ex. "Init..." ou "Pas de doigt")
void displayShowState(const char* state) {
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString(state);
}

// Affiche la moyenne BPM et l'état
void displayShowResult(float moyenne, const char* etat) {
    SeeedOled.clearDisplay();
    
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("Moyenne BPM:");
    SeeedOled.setTextXY(0, 2);
    SeeedOled.putNumber((int)moyenne);

    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("Etat:");
    SeeedOled.setTextXY(1, 2);
    SeeedOled.putString(etat);
}
