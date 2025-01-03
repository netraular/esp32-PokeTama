#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include "ui.h"
#include "pet.h"
#include "persistent_data_manager.h"
#include "screens/initial_screen/initial_screen.h"
#include "globals.h"

// Define the LVGL display buffer
static lv_color_t buf[240 * 10];
uint32_t lv_last_tick = 0;

// Constants for frame rate control
const uint32_t FRAME_INTERVAL = 1000 / 30;

// Persistent data manager (como puntero)
PersistentDataManager* dataManager = nullptr;

// Variable para almacenar si el archivo pet_stats.json existe
bool petStatsExists = false;

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    // Mostrar información sobre la memoria
    Serial.print("Free heap: ");
    Serial.println(ESP.getFreeHeap());
    Serial.print("Total heap: ");
    Serial.println(ESP.getHeapSize());
    Serial.print("Min free heap: ");
    Serial.println(ESP.getMinFreeHeap());

    // Initialize the display
    smartdisplay_init();
    Serial.println("Display initialized.");

    // Initialize LVGL
    lv_init();
    Serial.println("LVGL initialized.");

    // Set up LVGL display buffer
    auto disp = lv_display_get_default();
    lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
    Serial.println("LVGL display buffer set.");

    // Initialize LittleFS
    if (!LittleFS.begin(true)) {
        Serial.println("Failed to initialize LittleFS!");
        return;
    }
    Serial.println("LittleFS initialized.");

    // Inicializar dataManager después de LittleFS
    dataManager = new PersistentDataManager();

    // Verificar si el directorio /data existe, si no, crearlo
    if (!LittleFS.exists("/data")) {
        Serial.println("/data directory does not exist. Creating...");
        if (!LittleFS.mkdir("/data")) {
            Serial.println("Failed to create /data directory!");
            return;
        }
        Serial.println("/data directory created.");
    }

    // Verificar si pet_stats.json existe
    petStatsExists = LittleFS.exists("/data/pet_stats.json");
    Serial.println(petStatsExists ? "pet_stats.json exists." : "pet_stats.json does not exist.");

    if (!petStatsExists) {
        // Show the initial screen
        initial_screen_init();
        initial_screen_show();
        Serial.println("Initial screen shown.");
    } else {
        // Load pet stats
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
            Serial.println("Pet stats loaded successfully.");
        } else {
            Serial.println("Failed to load pet stats.");
        }

        // Initialize UI
        ui_init();
        Serial.println("UI initialized.");

        // Initialize pet
        pet_init();
        Serial.println("Pet initialized.");

        // Show the main screen
        show_main_screen();
    }
}

void loop() {
    static uint32_t initial_time = millis(); // Tiempo inicial de referencia para fotogramas
    static uint32_t last_pet_update_time = millis(); // Tiempo de la última actualización de la mascota
    uint32_t current_time = millis();
    uint32_t elapsed_time = current_time - initial_time; // Tiempo transcurrido desde el último fotograma

    // Actualizar cada fotograma (30 FPS)
    if (elapsed_time >= FRAME_INTERVAL) {
        initial_time = current_time; // Reiniciar el tiempo inicial para el próximo fotograma

        // Actualizar LVGL
        lv_tick_inc(current_time - lv_last_tick);
        lv_last_tick = current_time;
        lv_timer_handler();

        update_fps(); // Contador de  FPS
    }

    // Actualizar la mascota cada 10 segundos
    if ((current_time - last_pet_update_time) >= 10000) {
        last_pet_update_time = current_time; // Reiniciar el tiempo de la última actualización
        pet_update(); // Actualizar estado de la mascota
    }
}