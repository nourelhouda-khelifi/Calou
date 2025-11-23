#include "sophro_exercices.h"

void setup() {

    Wire.begin();
    SeeedOled.init();  
    SeeedOled.clearDisplay();          
}

void loop() {
    exercice_sophro_normal();
}
