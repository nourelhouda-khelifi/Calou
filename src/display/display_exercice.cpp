#include <SeeedOLED.h>
#include "../../include/display_exercice.h"

void displayExercice(int cycle, bool inspirer) {
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("Respirez !");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("Cycle: ");
    SeeedOled.putNumber(cycle);

    // Animation bulle
    int taille = inspirer ? 5 : 2;
    for(int i=0;i<taille;i++){
        SeeedOled.setTextXY(3+i,4);
        SeeedOled.putString("O");
    }
}
