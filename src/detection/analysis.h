#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <Arduino.h>
#include <SeeedOLED.h>
#include "bpm.h"
#include "./display/display_accueil.h"
#include "./display/calou_active.h"

const char* analyserStress(); 
void resetAnalyse();
extern int bpm_affiche;
#endif
