#ifndef FEED_SCREEN_H
#define FEED_SCREEN_H

#include <lvgl.h>

void food_button_event_handler(lv_event_t * e);

// Structure to represent food
typedef struct {
    int id;
    const char* name;
    int hunger;
    int health;
    int happiness;
    int quantity;
    int price;
    const char* image;
} Food;

extern lv_obj_t * feed_screen;
extern Food foods[]; // Array to store food data
extern int food_count; // Number of foods available

void feed_screen_init();
void load_food_data(); // Function to load food data from JSON

#endif