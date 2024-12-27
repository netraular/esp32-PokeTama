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

// FPS variables
uint32_t frame_count = 0; // Frame counter
uint32_t last_fps_time = 0; // Last time FPS was calculated
uint32_t current_fps = 0; // Current FPS value

// FPS label
lv_obj_t * fps_label;

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

  // Create the FPS label
  fps_label = lv_label_create(lv_scr_act());
  lv_label_set_text(fps_label, "0"); // Initialize with "0"
  lv_obj_align(fps_label, LV_ALIGN_TOP_MID, 0, 0);

  // Show the main screen by default
  show_main_screen();
}

void update_fps() {
  // Increment frame counter
  frame_count++;

  // Calculate FPS every second
  uint32_t current_time = millis();
  if (current_time - last_fps_time >= 1000) {
    current_fps = frame_count; // Store the current FPS value
    frame_count = 0;
    last_fps_time = current_time;

    // Limit FPS to 30
    if (current_fps > 30) current_fps = 30;

    // Update FPS label (show only the number)
    char fps_text[16];
    snprintf(fps_text, sizeof(fps_text), "%lu", current_fps);
    lv_label_set_text(fps_label, fps_text);
  }
}

uint32_t get_fps() {
  // Return the current FPS value
  return current_fps;
}

void show_main_screen() {
  lv_scr_load(main_screen);
  lv_obj_set_parent(fps_label, main_screen); // Move FPS label to main screen
}

void show_action_menu() {
  lv_scr_load(action_menu);
  lv_obj_set_parent(fps_label, action_menu); // Move FPS label to action menu
}

void show_status_screen() {
  lv_scr_load(status_screen);
  lv_obj_set_parent(fps_label, status_screen); // Move FPS label to status screen
}

void show_feed_screen() {
  lv_scr_load(feed_screen);
  lv_obj_set_parent(fps_label, feed_screen); // Move FPS label to feed screen
}

void show_play_screen() {
  lv_scr_load(play_screen);
  lv_obj_set_parent(fps_label, play_screen); // Move FPS label to play screen
}

void show_shop_screen() {
  lv_scr_load(shop_screen);
  lv_obj_set_parent(fps_label, shop_screen); // Move FPS label to shop screen
}

void show_sleep_screen() {
  lv_scr_load(sleep_screen);
  lv_obj_set_parent(fps_label, sleep_screen); // Move FPS label to sleep screen
}

void show_clean_screen() {
  lv_scr_load(clean_screen);
  lv_obj_set_parent(fps_label, clean_screen); // Move FPS label to clean screen
}

void show_heal_screen() {
  lv_scr_load(heal_screen);
  lv_obj_set_parent(fps_label, heal_screen); // Move FPS label to heal screen
}

void show_style_screen() {
  lv_scr_load(style_screen);
  lv_obj_set_parent(fps_label, style_screen); // Move FPS label to style screen
}

void show_connect_screen() {
  lv_scr_load(connect_screen);
  lv_obj_set_parent(fps_label, connect_screen); // Move FPS label to connect screen
}

void show_settings_screen() {
  lv_scr_load(settings_screen);
  lv_obj_set_parent(fps_label, settings_screen); // Move FPS label to settings screen
}