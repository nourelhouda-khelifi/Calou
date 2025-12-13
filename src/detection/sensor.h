#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

#define SENSOR_PIN A0

int lireCapteur();
bool doigtPresent(int valeur);

#endif
