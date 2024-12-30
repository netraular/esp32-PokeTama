#ifndef PERSISTENT_DATA_MANAGER_H
#define PERSISTENT_DATA_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include "food.h" // Incluir la definición de Food

// Structure to represent pet stats
struct PetStats {
    String name; // Nuevo campo para el nombre de la mascota
    int health;
    int hunger;
    int happiness;
    int coins;
    String birthdate;
    int evolution;
    bool alive;
};

class PersistentDataManager {
public:
    PersistentDataManager();
    bool loadPetStats(PetStats &stats);
    bool savePetStats(const PetStats &stats);
    bool loadFoodData(Food *foods, int &food_count);
    bool saveFoodData(const Food *foods, int food_count);
    bool initializeDefaultFiles(); // Inicializa archivos con valores predeterminados
    bool deleteAllFiles(); // Borra todos los archivos de datos
    bool resetToDefault(); // Borra y recrea los archivos con valores iniciales

private:
    const char* _petStatsPath = "/data/pet_stats.json";
    const char* _foodDataPath = "/data/food.json";

    bool ensureDataDirectoryExists();
    bool createDefaultPetStats(); // Crea el archivo de stats con valores predeterminados
    bool createDefaultFoodData(); // Crea el archivo de comida con valores predeterminados
};
#endif