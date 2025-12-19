#ifndef CALOU_ACTIVE_H
#define CALOU_ACTIVE_H

#include <Arduino.h>
#include "display_accueil.h"
#include "sophro_exercices.h"
#include "./detection/sensor.h"
#include "./detection/bpm.h"
#include "./detection/analysis.h"

// --- CONFIGURATION DES BROCHES ---
const int buttonPin = 12;        // Bouton d'activation générale
const int sportPin = 13;         // Bouton du mode sport
extern int buttonActiveState;        
extern unsigned long lastDebounceTimeActive;
extern unsigned long pressStartTimeActive; 
extern bool activationOn;
extern bool sportOn;

bool updateActivateBouton();
boolean activerCalou();
boolean boutonActive();

#endif