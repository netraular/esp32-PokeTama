#include "screens/initial_screen/initial_screen.h"
#include "ui.h"
#include "globals.h" // Incluir globals.h para acceder a dataManager y petStatsExists

lv_obj_t * initial_screen;

static void set_data_button_event_handler(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        // Crear archivos con valores predeterminados
        if (dataManager->initializeDefaultFiles()) {
            Serial.println("Default files created successfully.");

            // Actualizar petStatsExists a true
            petStatsExists = true;
            Serial.println("petStatsExists set to true.");
        } else {
            Serial.println("Failed to create default files.");
        }

        // Cargar la UI principal
        ui_init();
        show_main_screen();
    }
}

void initial_screen_init() {
    initial_screen = lv_obj_create(NULL);

    // Add a label for the screen name
    lv_obj_t * label = lv_label_create(initial_screen);
    lv_label_set_text(label, "Welcome to Tamagotchi!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -30);

    // Add a "Set Data" button
    lv_obj_t * btn_set_data = lv_btn_create(initial_screen);
    lv_obj_set_size(btn_set_data, 150, 40);
    lv_obj_align(btn_set_data, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btn_set_data, set_data_button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t * label_set_data = lv_label_create(btn_set_data);
    lv_label_set_text(label_set_data, "Set Data");
    lv_obj_center(label_set_data);
}

void initial_screen_show() {
    lv_scr_load(initial_screen);
}