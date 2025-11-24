#include <SeeedOLED.h>
#include "display_resultat.h"

void displayResult(float moyenne, const char* etat) {
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("Moyenne BPM:");
    SeeedOled.setTextXY(1,0);
    SeeedOled.putNumber((int)moyenne);
    SeeedOled.setTextXY(2,0);
    SeeedOled.putString("Etat:");
    SeeedOled.setTextXY(3,0);
    SeeedOled.putString(etat);
}
