#ifndef DISPLAY_ACCUEIL_H
#define DISPLAY_ACCUEIL_H

#include <SeeedOLED.h>
#include <Arduino.h>
#include "calou_active.h"
#include "bitmap.h"

extern int currentDisplayState;
extern int currentSportState;
void displayAccueil();
void displaydeactivate();
void displaySport();
void displayNotSport();

#endif
