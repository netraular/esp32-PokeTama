#include "persistent_data_manager.h"

PersistentDataManager::PersistentDataManager() {
    ensureDataDirectoryExists();
}

bool PersistentDataManager::ensureDataDirectoryExists() {
    if (!LittleFS.exists("/data")) {
        return LittleFS.mkdir("/data");
    }
    return true;
}

bool PersistentDataManager::loadPetStats(PetStats &stats) {
    if (!LittleFS.exists(_petStatsPath)) {
        return false; // El archivo no existe
    }

    File file = LittleFS.open(_petStatsPath, "r");
    if (!file) {
        Serial.println("Failed to open pet_stats.json!");
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        Serial.print("Failed to parse pet_stats.json: ");
        Serial.println(error.c_str());
        return false;
    }

    stats.name = doc["name"].as<String>();
    stats.health = doc["health"];
    stats.hunger = doc["hunger"];
    stats.happiness = doc["happiness"];
    stats.coins = doc["coins"];
    stats.birthdate = doc["birthdate"].as<String>();
    stats.evolution = doc["evolution"];
    stats.alive = doc["alive"];

    return true;
}

bool PersistentDataManager::savePetStats(const PetStats &stats) {
    File file = LittleFS.open(_petStatsPath, "w");
    if (!file) {
        Serial.println("Failed to open pet_stats.json for writing!");
        return false;
    }

    JsonDocument doc;
    doc["name"] = stats.name;
    doc["health"] = stats.health;
    doc["hunger"] = stats.hunger;
    doc["happiness"] = stats.happiness;
    doc["coins"] = stats.coins;
    doc["birthdate"] = stats.birthdate;
    doc["evolution"] = stats.evolution;
    doc["alive"] = stats.alive;

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to pet_stats.json!");
        file.close();
        return false;
    }

    file.close();
    return true;
}

bool PersistentDataManager::createDefaultPetStats() {
    PetStats defaultStats = {"TestName", 100, 100, 100, 0, "2023-01-01", 0, true};

    // Crear el archivo /data/pet_stats.json
    File file = LittleFS.open("/data/pet_stats.json", "w");
    if (!file) {
        Serial.println("Failed to create /data/pet_stats.json!");
        return false;
    }

    // Serializar los datos a JSON
    JsonDocument doc;
    doc["name"] = defaultStats.name;
    doc["health"] = defaultStats.health;
    doc["hunger"] = defaultStats.hunger;
    doc["happiness"] = defaultStats.happiness;
    doc["coins"] = defaultStats.coins;
    doc["birthdate"] = defaultStats.birthdate;
    doc["evolution"] = defaultStats.evolution;
    doc["alive"] = defaultStats.alive;

    // Escribir el JSON en el archivo
    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to /data/pet_stats.json!");
        file.close();
        return false;
    }

    file.close();
    return true;
}

bool PersistentDataManager::loadFoodData(Food *foods, int &food_count) {
    if (!LittleFS.exists(_foodDataPath)) {
        return false; // El archivo no existe
    }

    File file = LittleFS.open(_foodDataPath, "r");
    if (!file) {
        Serial.println("Failed to open food.json! U.U");
        return false;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        Serial.print("Failed to parse food.json: ");
        Serial.println(error.c_str());
        return false;
    }

    food_count = doc.size();
    for (int i = 0; i < food_count; i++) {
        foods[i].id = doc[i]["id"];
        foods[i].name = doc[i]["name"].as<String>();
        foods[i].hunger = doc[i]["hunger"];
        foods[i].health = doc[i]["health"];
        foods[i].happiness = doc[i]["happiness"];
        foods[i].quantity = doc[i]["quantity"];
        foods[i].price = doc[i]["price"];
        foods[i].image = doc[i]["image"].as<String>();
    }

    return true;
}

bool PersistentDataManager::saveFoodData(const Food *foods, int food_count) {
    File file = LittleFS.open(_foodDataPath, "w");
    if (!file) {
        Serial.println("Failed to open food.json for writing!");
        return false;
    }

    JsonDocument doc;
    for (int i = 0; i < food_count; i++) {
        JsonObject food = doc.add<JsonObject>();
        food["id"] = foods[i].id;
        food["name"] = foods[i].name;
        food["hunger"] = foods[i].hunger;
        food["health"] = foods[i].health;
        food["happiness"] = foods[i].happiness;
        food["quantity"] = foods[i].quantity;
        food["price"] = foods[i].price;
        food["image"] = foods[i].image;
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to food.json!");
        file.close();
        return false;
    }

    file.close();
    return true;
}


bool PersistentDataManager::createDefaultFoodData() {
    const char* default_data = R"(
    [
        {"id":1,"name":"Apple Pie","hunger":100,"health":5,"happiness":2,"quantity":5,"price":5,"image":"/assets/food/n05ApplePie.c"},
        {"id":2,"name":"Bread","hunger":20,"health":10,"happiness":5,"quantity":5,"price":15,"image":"/assets/food/n07Bread.c"}
    ]
    )";

    File file = LittleFS.open(_foodDataPath, "w");
    if (!file) {
        Serial.println("Failed to create food.json!");
        return false;
    }

    file.print(default_data);
    file.close();
    return true;
}

bool PersistentDataManager::initializeDefaultFiles() {
    bool success = true;

    if (!LittleFS.exists(_petStatsPath)) {
        success &= createDefaultPetStats();
    }
    
    if (!LittleFS.exists(_foodDataPath)) {
        success &= createDefaultFoodData();
    }

    return success;
}

bool PersistentDataManager::deleteAllFiles() {
    bool success = true;

    if (LittleFS.exists(_foodDataPath)) {
        success &= LittleFS.remove(_foodDataPath);
    }
    
    if (LittleFS.exists(_petStatsPath)) {
        success &= LittleFS.remove(_petStatsPath);
    }


    return success;
}

bool PersistentDataManager::resetToDefault() {
    bool success = deleteAllFiles();
    success &= initializeDefaultFiles();
    return success;
}