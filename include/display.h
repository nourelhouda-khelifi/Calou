#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

void displayInit();
void displayShowBPM(int bpm);
void displayShowState(const char* state);
void displayClear();
// Nouvelle fonction pour afficher moyenne BPM + état
void displayShowResult(float moyenne, const char* etat);

#endif
