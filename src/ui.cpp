#include "ui.h"

// Declare UI objects
lv_obj_t * main_screen;
lv_obj_t * action_menu;
lv_obj_t * fps_label; // Label to display FPS
extern const lv_img_dsc_t pet;
extern const lv_img_dsc_t livingroom;
extern const lv_img_dsc_t kitchen;
extern const lv_img_dsc_t bathroom;
extern const lv_img_dsc_t garden;

// Current room variable
Room room = ROOM_LIVINGROOM; // Default room
lv_obj_t * bg_img; // Background image object

// FPS variables
uint32_t frame_count = 0; // Frame counter
uint32_t last_fps_time = 0; // Last time FPS was calculated
uint32_t current_fps = 0; // Current FPS value

// Function to handle touch events
static void main_screen_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e); // Cast to lv_obj_t*
    const char * btn_text = lv_label_get_text(lv_obj_get_child(btn, 0));

    // Handle button clicks
    if (strcmp(btn_text, "<") == 0) {
      Serial.println("Left arrow clicked");
      // Cycle to the previous room
      Room new_room = (Room)((room - 1 + 4) % 4); // Wrap around if necessary
      change_room(new_room);
    } else if (strcmp(btn_text, ">") == 0) {
      Serial.println("Right arrow clicked");
      // Cycle to the next room
      Room new_room = (Room)((room + 1) % 4); // Wrap around if necessary
      change_room(new_room);
    } else if (strcmp(btn_text, "+") == 0) {
      Serial.println("Plus button clicked");
      show_action_menu(); // Show the action menu
    } else if (strcmp(btn_text, "pet") == 0) {
      Serial.println("Pet clicked");
      // TODO: Handle pet action
    }
  }
}

// Function to handle action menu button clicks
static void action_menu_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e); // Cast to lv_obj_t*
    const char * btn_text = lv_label_get_text(lv_obj_get_child(btn, 0));

    // Handle button clicks
    if (strcmp(btn_text, "Status") == 0) {
      Serial.println("Status button clicked");
      // TODO: Navigate to Status Screen
    } else if (strcmp(btn_text, "Feed") == 0) {
      Serial.println("Feed button clicked");
      // TODO: Navigate to Feed Screen
    } else if (strcmp(btn_text, "Play") == 0) {
      Serial.println("Play button clicked");
      // TODO: Navigate to Play Screen
    } else if (strcmp(btn_text, "Shop") == 0) {
      Serial.println("Shop button clicked");
      // TODO: Navigate to Shop Screen
    } else if (strcmp(btn_text, "Sleep") == 0) {
      Serial.println("Sleep button clicked");
      // TODO: Navigate to Sleep Screen
    } else if (strcmp(btn_text, "Clean") == 0) {
      Serial.println("Clean button clicked");
      // TODO: Navigate to Clean Screen
    } else if (strcmp(btn_text, "Heal") == 0) {
      Serial.println("Heal button clicked");
      // TODO: Navigate to Heal Screen
    } else if (strcmp(btn_text, "Style") == 0) {
      Serial.println("Style button clicked");
      // TODO: Navigate to Style Screen
    } else if (strcmp(btn_text, "Connect") == 0) {
      Serial.println("Connect button clicked");
      // TODO: Navigate to Connect Screen
    } else if (strcmp(btn_text, "Settings") == 0) {
      Serial.println("Settings button clicked");
      // TODO: Navigate to Settings Screen
    } else if (strcmp(btn_text, "Back") == 0) {
      Serial.println("Back button clicked");
      hide_action_menu(); // Hide the action menu
    }
  }
}

void ui_init() {
  // Create the main screen
  main_screen = lv_obj_create(NULL);
  lv_scr_load(main_screen);

  // Add initial background image (living room)
  bg_img = lv_img_create(main_screen);
  lv_img_set_src(bg_img, &livingroom);
  lv_obj_align(bg_img, LV_ALIGN_CENTER, 0, 0);

  // Add pet image
  lv_obj_t * pet_img = lv_img_create(main_screen);
  lv_img_set_src(pet_img, &pet);
  lv_obj_align(pet_img, LV_ALIGN_CENTER, 0, 0);

  // Add left arrow button
  lv_obj_t * btn_left = lv_btn_create(main_screen);
  lv_obj_set_size(btn_left, 50, 50);
  lv_obj_align(btn_left, LV_ALIGN_LEFT_MID, 10, 0);
  lv_obj_add_event_cb(btn_left, main_screen_event_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_t * label_left = lv_label_create(btn_left);
  lv_label_set_text(label_left, "<");
  lv_obj_center(label_left);

  // Add right arrow button
  lv_obj_t * btn_right = lv_btn_create(main_screen);
  lv_obj_set_size(btn_right, 50, 50);
  lv_obj_align(btn_right, LV_ALIGN_RIGHT_MID, -10, 0);
  lv_obj_add_event_cb(btn_right, main_screen_event_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_t * label_right = lv_label_create(btn_right);
  lv_label_set_text(label_right, ">");
  lv_obj_center(label_right);

  // Add plus button
  lv_obj_t * btn_plus = lv_btn_create(main_screen);
  lv_obj_set_size(btn_plus, 50, 50);
  lv_obj_align(btn_plus, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_obj_add_event_cb(btn_plus, main_screen_event_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_t * label_plus = lv_label_create(btn_plus);
  lv_label_set_text(label_plus, "+");
  lv_obj_center(label_plus);

  // Add transparent pet button in the center
  lv_obj_t * btn_pet = lv_btn_create(main_screen);
  lv_obj_set_size(btn_pet, 100, 100); // Adjust size as needed
  lv_obj_align(btn_pet, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btn_pet, main_screen_event_handler, LV_EVENT_CLICKED, NULL);

  // Make the button transparent
  lv_obj_set_style_bg_opa(btn_pet, LV_OPA_TRANSP, LV_PART_MAIN); // Transparent background
  lv_obj_set_style_border_opa(btn_pet, LV_OPA_TRANSP, LV_PART_MAIN); // Transparent border

  // Add a label to the button (optional, for debugging)
  lv_obj_t * label_pet = lv_label_create(btn_pet);
  lv_label_set_text(label_pet, "pet");
  lv_obj_center(label_pet);

  // Create the action menu (initially hidden)
  action_menu = lv_obj_create(main_screen);
  lv_obj_set_size(action_menu, 200, 250); // Increased height to fit more buttons
  lv_obj_align(action_menu, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_flag(action_menu, LV_OBJ_FLAG_HIDDEN); // Hide the menu initially

  // Add buttons to the action menu
  const char * actions[] = {"Status", "Feed", "Play", "Shop", "Sleep", "Clean", "Heal", "Style", "Connect", "Settings", "Back"};
  for (int i = 0; i < 11; i++) {
    lv_obj_t * btn = lv_btn_create(action_menu);
    lv_obj_set_size(btn, 180, 30);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, 10 + i * 35);
    lv_obj_add_event_cb(btn, action_menu_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, actions[i]);
    lv_obj_center(label);
  }

  // Add FPS label at the top of the screen
  fps_label = lv_label_create(main_screen);
  lv_label_set_text(fps_label, "FPS: 0");
  lv_obj_align(fps_label, LV_ALIGN_TOP_MID, 0, 10);
}

void show_action_menu() {
  // Show the action menu
  lv_obj_clear_flag(action_menu, LV_OBJ_FLAG_HIDDEN);
}

void hide_action_menu() {
  // Hide the action menu
  lv_obj_add_flag(action_menu, LV_OBJ_FLAG_HIDDEN);
}

void change_room(Room new_room) {
  // Update the room variable
  room = new_room;

  // Update the background image based on the new room
  switch (room) {
    case ROOM_LIVINGROOM:
      lv_img_set_src(bg_img, &livingroom);
      Serial.println("Switched to Living Room");
      break;
    case ROOM_KITCHEN:
      lv_img_set_src(bg_img, &kitchen);
      Serial.println("Switched to Kitchen");
      break;
    case ROOM_BATHROOM:
      lv_img_set_src(bg_img, &bathroom);
      Serial.println("Switched to Bathroom");
      break;
    case ROOM_GARDEN:
      lv_img_set_src(bg_img, &garden);
      Serial.println("Switched to Garden");
      break;
  }
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

    // Update FPS label
    char fps_text[16];
    snprintf(fps_text, sizeof(fps_text), "FPS: %lu", current_fps);
    lv_label_set_text(fps_label, fps_text);
  }
}

uint32_t get_fps() {
  // Return the current FPS value
  return current_fps;
}