#include "pet.h"

// Define pet state variables
int hunger = 100;
int health = 100;
int happiness = 100;


// Constants for state update intervals
const uint32_t HUNGER_UPDATE_INTERVAL = 10000; // 10 seconds
const uint32_t HAPPINESS_UPDATE_INTERVAL = 10000; // 10 seconds

// Variables to track the last update time
uint32_t last_hunger_update = 0;
uint32_t last_happiness_update = 0;

void pet_init() {
  // Initialize pet state
  hunger = 100;
  happiness = 100;
  last_hunger_update = millis();
  last_happiness_update = millis();
  Serial.println("Pet initialized with full hunger and happiness.");
}

void pet_update() {
  // Get the current time
  uint32_t current_time = millis();

  // Update hunger every 10 seconds
  if (current_time - last_hunger_update >= HUNGER_UPDATE_INTERVAL) {
    last_hunger_update = current_time;
    if (hunger > 0) hunger--;
    Serial.print("Hunger updated: ");
    Serial.println(hunger);
  }

  // Update happiness every 10 seconds
  if (current_time - last_happiness_update >= HAPPINESS_UPDATE_INTERVAL) {
    last_happiness_update = current_time;
    if (happiness > 0) happiness--;
    Serial.print("Happiness updated: ");
    Serial.println(happiness);
  }

  // Debugging: Notify if hunger or happiness is critically low
  if (hunger <= 20) {
    Serial.println("Warning: Pet is very hungry!");
  }
  if (happiness <= 20) {
    Serial.println("Warning: Pet is very unhappy!");
  }
}