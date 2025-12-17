#ifndef CALOU_ACTIVE_H
#define CALOU_ACTIVE_H

#include <Arduino.h>

const int buttonPin = 12;
const int sportPin = 13;
extern int buttonActiveState;        
extern unsigned long lastDebounceTimeActive;
extern unsigned long pressStartTimeActive; 
extern bool activationOn;
extern bool sportOn;

bool updateActivateBouton();
boolean activerCalou();
boolean boutonActive();

#endif