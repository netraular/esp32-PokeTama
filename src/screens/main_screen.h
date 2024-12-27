#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <lvgl.h>

// Declare the main screen object
extern lv_obj_t * main_screen;

// Declare the background image object
extern lv_obj_t * bg_img;

// Declare the pet image object
extern lv_obj_t * pet_img;

// Declare the room enumeration
enum Room {
  ROOM_LIVINGROOM,
  ROOM_KITCHEN,
  ROOM_BATHROOM,
  ROOM_GARDEN
};

// Declare the current room variable
extern Room room;

// Function declarations
void main_screen_init();
void change_room(Room new_room);

#endif