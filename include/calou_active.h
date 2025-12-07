#ifndef CALOU_ACTIVE_H
#define CALOU_ACTIVE_H

#include <Arduino.h>

const int buttonPin = 12;
const int sportPin = 13;

// Debouncing and State Variables
// These need to be accessible and modifiable across your sketch files.
// The 'extern' keyword declares the existence of the variable, telling 
// the compiler it will be defined in a different source file (.ino or .cpp).
// Existing State tracking variables
extern int buttonState;        
extern unsigned long lastDebounceTime;
extern unsigned long pressStartTime; 
// 🆕 New variable to track the start of the press

// Configuration


// The main toggle state variable
extern bool activationOn;

bool updateActivateBouton();
boolean activerCalou();
boolean boutonActive();

#endif