#ifndef SOPHRO_EXERCICES_H
#define SOPHRO_EXERCICES_H

#include <Wire.h>
#include <SeeedOLED.h>

void displayAlerte();
bool exercice_sophro_normal();
bool inspirer_cycle();
bool tenir_cycle(int nb_ms);
bool expirer_cycle();
void commencer_affichage();
void afficher_countdown();
bool verifierActivation();
bool cycle(int tenir_secondes);

#endif
