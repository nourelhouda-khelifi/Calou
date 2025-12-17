#ifndef BPM_H
#define BPM_H

#include <Arduino.h>
#include <SeeedOLED.h>
#include "./display/display_accueil.h"
#include "./display/calou_active.h"

int detecterBPM(int valeur);
int getBPMCount();
float getMeanBPM();
void resetBPM();

#endif
