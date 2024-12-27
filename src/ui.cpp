#include "ui.h"


// Declare UI objects
lv_obj_t * main_screen;
lv_obj_t * action_menu;
extern const lv_img_dsc_t pet;
extern const lv_img_dsc_t background;

// Function to handle touch events
static void main_screen_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    // Show the action menu when the screen is touched
    show_action_menu();
  }
}

// Function to handle action menu button clicks
static void action_menu_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e); // Cast to lv_obj_t*
    const char * btn_text = lv_label_get_text(lv_obj_get_child(btn, 0));

    // Handle button clicks
    if (strcmp(btn_text, "Feed") == 0) {
      Serial.println("Feed button clicked");
      // TODO: Navigate to Feed Screen
    } else if (strcmp(btn_text, "Play") == 0) {
      Serial.println("Play button clicked");
      // TODO: Navigate to Play Screen
    } else if (strcmp(btn_text, "Sleep") == 0) {
      Serial.println("Sleep button clicked");
      // TODO: Navigate to Sleep Screen
    } else if (strcmp(btn_text, "Clean") == 0) {
      Serial.println("Clean button clicked");
      // TODO: Navigate to Clean Screen
    } else if (strcmp(btn_text, "Status") == 0) {
      Serial.println("Status button clicked");
      // TODO: Navigate to Status Screen
    } else if (strcmp(btn_text, "Settings") == 0) {
      Serial.println("Settings button clicked");
      // TODO: Navigate to Settings Screen
    }

    // Hide the action menu after selecting an action
    hide_action_menu();
  }
}

void ui_init() {
  // Create the main screen
  main_screen = lv_obj_create(NULL);
  lv_scr_load(main_screen);

  // Add background image
  lv_obj_t * bg_img = lv_img_create(main_screen);
  lv_img_set_src(bg_img, &background);
  lv_obj_align(bg_img, LV_ALIGN_CENTER, 0, 0);

  // Add pet image
  lv_obj_t * pet_img = lv_img_create(main_screen);
  lv_img_set_src(pet_img, &pet);
  lv_obj_align(pet_img, LV_ALIGN_CENTER, 0, 0);

  // Add touch event handler to the main screen
  lv_obj_add_event_cb(main_screen, main_screen_event_handler, LV_EVENT_CLICKED, NULL);

  // Create the action menu (initially hidden)
  action_menu = lv_obj_create(main_screen);
  lv_obj_set_size(action_menu, 200, 150);
  lv_obj_align(action_menu, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_flag(action_menu, LV_OBJ_FLAG_HIDDEN); // Hide the menu initially

  // Add buttons to the action menu
  const char * actions[] = {"Feed", "Play", "Sleep", "Clean", "Status", "Settings"};
  for (int i = 0; i < 6; i++) {
    lv_obj_t * btn = lv_btn_create(action_menu);
    lv_obj_set_size(btn, 180, 30);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, 10 + i * 35);
    lv_obj_add_event_cb(btn, action_menu_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, actions[i]);
    lv_obj_center(label);
  }
}

void show_action_menu() {
  // Show the action menu
  lv_obj_clear_flag(action_menu, LV_OBJ_FLAG_HIDDEN);
}

void hide_action_menu() {
  // Hide the action menu
  lv_obj_add_flag(action_menu, LV_OBJ_FLAG_HIDDEN);
}