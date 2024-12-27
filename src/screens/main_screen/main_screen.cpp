#include "main_screen.h"
#include "ui.h"
#include "screens/main_screen/main_screen.h"

// Include the image assets
extern const lv_img_dsc_t livingroom;
extern const lv_img_dsc_t kitchen;
extern const lv_img_dsc_t bathroom;
extern const lv_img_dsc_t garden;
extern const lv_img_dsc_t pet;

// Define the main screen object
lv_obj_t * main_screen;

// Define the background image object
lv_obj_t * bg_img;

// Define the pet image object
lv_obj_t * pet_img;

// Define the current room variable
Room room = ROOM_LIVINGROOM; // Default room

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

void main_screen_init() {
  // Create the main screen
  main_screen = lv_obj_create(NULL);
  lv_scr_load(main_screen);

  // Add initial background image (living room)
  bg_img = lv_img_create(main_screen);
  lv_img_set_src(bg_img, &livingroom);
  lv_obj_align(bg_img, LV_ALIGN_CENTER, 0, 0);

  // Add pet image
  pet_img = lv_img_create(main_screen);
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