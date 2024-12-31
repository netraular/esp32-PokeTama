#include "pet.h"
#include "persistent_data_manager.h"
#include "globals.h" // Incluir globals.h para acceder a dataManager

// Define pet state variables
String name = "TestName"; // Inicializado con "TestName"
int hunger = 100;
int health = 100;
int happiness = 100;
int coins = 0;
String birthdate = "2023-01-01";
int evolution = 0;
bool alive = true;
bool paused = false; // Inicialmente no está pausado

// Constants for state update intervals
const uint32_t HUNGER_UPDATE_INTERVAL = 10000; // 10 seconds
const uint32_t HAPPINESS_UPDATE_INTERVAL = 10000; // 10 seconds

// Variables to track the last update time
uint32_t last_hunger_update = 0;
uint32_t last_happiness_update = 0;

static uint32_t last_pet_update_time = 0; // Última vez que se actualizó el estado de la mascota

void pet_init() {
    // Load pet stats from persistent storage
    PetStats stats;
    if (dataManager->loadPetStats(stats)) {
        name = stats.name;
        hunger = stats.hunger;
        health = stats.health;
        happiness = stats.happiness;
        coins = stats.coins;
        birthdate = stats.birthdate;
        evolution = stats.evolution;
        alive = stats.alive;
    } else {
        // If loading fails, initialize with default values
        name = "TestName";
        hunger = 100;
        health = 100;
        happiness = 100;
        coins = 0;
        birthdate = "2023-01-01";
        evolution = 0;
        alive = true;

        // Save default stats to persistent storage
        stats = {name, health, hunger, happiness, coins, birthdate, evolution, alive};
        dataManager->savePetStats(stats);
    }

    // Initialize last update times
    last_hunger_update = millis();
    last_happiness_update = millis();

    Serial.println("Pet initialized with loaded stats.");
}

void pet_update() {
    uint32_t current_time = millis();

    // Actualizar cada 10 segundos
    if ((current_time - last_pet_update_time) >= 10000) {
        last_pet_update_time = current_time;

        if (petStatsExists && !paused) {
            if (hunger > 0) hunger--;
            if (happiness > 0) happiness--;

            // Guardar estadísticas actualizadas
            PetStats stats = {name, health, hunger, happiness, coins, birthdate, evolution, alive};
            dataManager->savePetStats(stats);

            Serial.print("Pet state - Hunger: ");
            Serial.print(hunger);
            Serial.print(", Happiness: ");
            Serial.println(happiness);
        }
    }
}