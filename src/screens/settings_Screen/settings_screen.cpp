#include "screens/settings_screen/settings_screen.h"
#include "ui.h"
#include "persistent_data_manager.h"
#include "globals.h"
#include "pet.h"

lv_obj_t * settings_screen;

// Función para manejar el botón de reset
static void reset_button_event_handler(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        // Pausar la actualización de los stats de la mascota
        paused = true;

        // Borrar todos los archivos de datos
        if (dataManager->deleteAllFiles()) {
            Serial.println("All files deleted successfully.");
        } else {
            Serial.println("Failed to delete files.");
        }

        // Crear archivos con valores iniciales
        if (dataManager->resetToDefault()) {
            Serial.println("Reset to default values successful.");
        } else {
            Serial.println("Failed to reset to default values.");
        }

        // Reiniciar la mascota con valores iniciales
        PetStats stats;
        if (dataManager->loadPetStats(stats)) {
            hunger = stats.hunger;
            health = stats.health;
            happiness = stats.happiness;
            coins = stats.coins;
            birthdate = stats.birthdate;
            evolution = stats.evolution;
            alive = stats.alive;
        }

        // Reanudar la actualización de los stats
        paused = false;

        // Volver a la pantalla principal
        show_main_screen();
    }
}

static void back_button_event_handler(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        show_main_screen();
    }
}

void settings_screen_init() {
    settings_screen = lv_obj_create(NULL);

    // Add a label for the screen name
    lv_obj_t * label = lv_label_create(settings_screen);
    lv_label_set_text(label, "Settings Screen");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    // Add a reset button
    lv_obj_t * btn_reset = lv_btn_create(settings_screen);
    lv_obj_set_size(btn_reset, 150, 40);
    lv_obj_align(btn_reset, LV_ALIGN_CENTER, 0, -30);
    lv_obj_add_event_cb(btn_reset, reset_button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t * label_reset = lv_label_create(btn_reset);
    lv_label_set_text(label_reset, "Reset Data");
    lv_obj_center(label_reset);

    // Add a back button
    lv_obj_t * btn_back = lv_btn_create(settings_screen);
    lv_obj_set_size(btn_back, 100, 40);
    lv_obj_align(btn_back, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_add_event_cb(btn_back, back_button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t * label_back = lv_label_create(btn_back);
    lv_label_set_text(label_back, "Back");
    lv_obj_center(label_back);
}