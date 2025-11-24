#include <SeeedOLED.h>
#include "display_accueil.h"

void displayAccueil() {
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("Bienvenue!");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("Heure: 12:34"); // à remplacer par vraie heure si besoin
    SeeedOled.setTextXY(2,0);
    SeeedOled.putString("Amuse-toi bien!");
    // Animation simple
    for(int i=0;i<3;i++){
        SeeedOled.setTextXY(4+i,0);
        SeeedOled.putString("*");
    }
}
