#include <SeeedOLED.h>
#include "../../include/display_alerte.h"

void displayAlerte() {
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("Vous etes stress!");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putString("Respirons ensemble!");
    // Animation cercle clignotant
    for(int i=0;i<3;i++){
        SeeedOled.setTextXY(3+i,2);
        SeeedOled.putString("O");
    }
}
