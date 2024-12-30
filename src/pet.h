#ifndef PET_H
#define PET_H

#include <Arduino.h>

// Declare pet state variables as extern
extern String name;
extern int hunger;
extern int health;
extern int happiness;
extern int coins;
extern String birthdate;
extern int evolution;
extern bool alive;
extern bool paused; // Variable para pausar la actualización de los stats

void pet_init();
void pet_update();

#endif