#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <Arduino.h>

// Function declarations
void ui_init();
void show_main_screen();
void show_action_menu();
void show_status_screen();
void show_feed_screen();
void show_play_screen();
void show_shop_screen();
void show_sleep_screen();
void show_clean_screen();
void show_heal_screen();
void show_style_screen();
void show_connect_screen();
void show_settings_screen();

// FPS functions
void update_fps();
uint32_t get_fps();

#endif