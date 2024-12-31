#include "ui.h"
#include "screens/main_screen/main_screen.h"
#include "screens/action_menu/action_menu.h"
#include "screens/status_screen/status_screen.h"
#include "screens/feed_screen/feed_screen.h"
#include "screens/play_screen/play_screen.h"
#include "screens/shop_screen/shop_screen.h"
#include "screens/sleep_screen/sleep_screen.h"
#include "screens/clean_screen/clean_screen.h"
#include "screens/heal_screen/heal_screen.h"
#include "screens/style_screen/style_screen.h"
#include "screens/connect_screen/connect_screen.h"
#include "screens/settings_screen/settings_screen.h"
#include "pet.h" // Include pet.h to access hunger, health, and happiness

void ui_init() {
    // Initialize all screens
    main_screen_init();
    action_menu_init();
    status_screen_init();
    feed_screen_init();
    play_screen_init();
    shop_screen_init();
    sleep_screen_init();
    clean_screen_init();
    heal_screen_init();
    style_screen_init();
    connect_screen_init();
    settings_screen_init();

    // Show the main screen by default
    show_main_screen();
}


void update_fps() {
    static uint32_t frame_count = 0; // Contador de fotogramas
    static uint32_t last_fps_time = millis(); // Tiempo de la última actualización de FPS
    uint32_t current_time = millis();

    // Incrementar el contador de fotogramas
    frame_count++;

    // Calcular FPS cada segundo
    if ((current_time - last_fps_time) >= 1000) {
        uint32_t current_fps = frame_count; // Almacenar el valor actual de FPS
        frame_count = 0; // Reiniciar el contador de fotogramas
        last_fps_time = current_time; // Reiniciar el tiempo de la última actualización

        // Mostrar FPS por serial
        Serial.print("FPS: ");
        Serial.println(current_fps);
    }
}

void show_main_screen() {
    lv_scr_load(main_screen);
}

void show_action_menu() {
    lv_scr_load(action_menu);
}

void show_status_screen() {
  lv_scr_load(status_screen);
}

void show_feed_screen() {
  lv_scr_load(feed_screen);
}

void show_play_screen() {
  lv_scr_load(play_screen);
}

void show_shop_screen() {
  lv_scr_load(shop_screen);
}

void show_sleep_screen() {
  lv_scr_load(sleep_screen);
}

void show_clean_screen() {
  lv_scr_load(clean_screen);
}

void show_heal_screen() {
  lv_scr_load(heal_screen);
}

void show_style_screen() {
  lv_scr_load(style_screen);
}

void show_connect_screen() {
  lv_scr_load(connect_screen);
}

void show_settings_screen() {
  lv_scr_load(settings_screen);
}