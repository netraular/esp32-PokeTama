#ifndef PET_H
#define PET_H

#include <Arduino.h>

// Declare pet state variables as extern
extern int hunger;
extern int health;
extern int happiness;

void pet_init();
void pet_update();

#endif