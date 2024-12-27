#ifndef PET_H
#define PET_H

#include <Arduino.h> // Include Arduino.h for Serial

// Declare pet state variables
extern int hunger;
extern int happiness;

void pet_init();
void pet_update();

#endif