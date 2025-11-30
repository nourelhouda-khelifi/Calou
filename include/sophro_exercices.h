#ifndef SOPHRO_EXERCICES_H
#define SOPHRO_EXERCICES_H

#include <Wire.h>
#include <SeeedOLED.h>

void exercice_sophro_normal();
void premier_cycle();
void deuxieme_cycle();
void troisieme_cycle();
void quatrieme_cycle();
void cinquieme_cycle();
void inspirer_cycle();
void tenir_cycle(int nb_ms);
void expirer_cycle();
void commencer_affichage();
void afficher_countdown();

#endif
