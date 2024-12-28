#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include "ui.h"
#include "pet.h"
#include <LittleFS.h> // Incluye la biblioteca LittleFS nativa

// Define the LVGL display buffer
static lv_color_t buf[240 * 10]; // Ajusta el tamaño según la resolución de tu pantalla
uint32_t lv_last_tick = 0; // Variable para rastrear el último tiempo de tick

// Constants for frame rate control
const uint32_t FRAME_INTERVAL = 1000 / 30; // 30 FPS (33ms por frame)
uint32_t last_frame_time = 0; // Variable para rastrear el último tiempo de frame

void setup() {
    // Initialize Serial communication for debugging
    Serial.begin(115200);
    Serial.println("Initializing...");

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

    // Initialize the file system
    if (!LittleFS.begin(true)) { // true formatea LittleFS si no está inicializado
        Serial.println("Failed to initialize LittleFS!");
        return;
    }
    Serial.println("LittleFS initialized.");

    // Check if food.json exists
    if (!LittleFS.exists("/data/food.json")) {
        Serial.println("Creating food.json with default data...");

        // Create the /data directory if it doesn't exist
        if (!LittleFS.exists("/data")) {
            LittleFS.mkdir("/data");
        }

        // Create the file and write default data
        File file = LittleFS.open("/data/food.json", "w");
        if (!file) {
            Serial.println("Failed to create food.json!");
            return;
        }

        // Default food data
        const char* default_data = R"(
        [
          {"id":1,"name":"Manzana","hunger":100,"health":5,"happiness":2,"quantity":3,"price":5,"image":"apple.c"},
          {"id":2,"name":"Pescado","hunger":20,"health":10,"happiness":5,"quantity":2,"price":15,"image":"fish.c"},
          {"id":3,"name":"Carne","hunger":30,"health":15,"happiness":10,"quantity":1,"price":25,"image":"meat.c"},
          {"id":4,"name":"Ensalada","hunger":15,"health":20,"happiness":5,"quantity":4,"price":10,"image":"salad.c"},
          {"id":5,"name":"Galleta","hunger":5,"health":-2,"happiness":15,"quantity":5,"price":3,"image":"cookie.c"}
        ]
        )";

        file.print(default_data);
        file.close();
        Serial.println("food.json created with default data.");
    } else {
        Serial.println("food.json already exists.");
    }

    // Initialize UI
    ui_init();
    Serial.println("UI initialized.");

    // Initialize pet
    pet_init();
    Serial.println("Pet initialized.");
}

void loop() {
    // Get the current time
    uint32_t current_time = millis();

    // Update LVGL tick
    lv_tick_inc(current_time - lv_last_tick);
    lv_last_tick = current_time;

    // Handle LVGL tasks
    lv_timer_handler();

    // Check if it's time to update (30 FPS)
    if (current_time - last_frame_time >= FRAME_INTERVAL) {
        last_frame_time = current_time;

        // Update pet state
        pet_update();

        // Update FPS counter
        update_fps();

        // Debugging: Print pet state and FPS periodically
        static uint32_t last_debug_time = 0;
        if (current_time - last_debug_time > 1000) { // Print every 1 second
            last_debug_time = current_time;
            Serial.print("Pet state - Hunger: ");
            Serial.print(hunger);
            Serial.print(", Happiness: ");
            Serial.println(happiness);

            // Get and display FPS
            uint32_t fps = get_fps();
            Serial.print("FPS: ");
            Serial.println(fps);
        }
    }
}