#ifndef UI_H
#define UI_H

#include <lvgl.h>
#include <Arduino.h>

// Room enumeration
enum Room {
  ROOM_LIVINGROOM,
  ROOM_KITCHEN,
  ROOM_BATHROOM,
  ROOM_GARDEN
};

// Declare FPS variables as extern
extern uint32_t frame_count;
extern uint32_t last_fps_time;
extern uint32_t current_fps; // Variable to share the current FPS value

void ui_init();
void show_action_menu();
void hide_action_menu();
void change_room(Room new_room);
void update_fps();
uint32_t get_fps(); // Function to get the current FPS

#endif