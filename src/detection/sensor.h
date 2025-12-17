#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <SeeedOLED.h>
#include "./display/calou_active.h"

#define SENSOR_PIN A0

int lireCapteur();
bool doigtPresent(int valeur);

#endif
