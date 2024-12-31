#ifndef FEED_SCREEN_H
#define FEED_SCREEN_H

#include <lvgl.h>
#include "food.h" // Incluir la definición de Food

void food_button_event_handler(lv_event_t * e);

// Declarar las variables externas
extern lv_obj_t * feed_screen;
extern Food foods[]; // Array para almacenar los datos de comida
extern int food_count; // Número de alimentos disponibles

void feed_screen_init();
void load_food_data(); // Función para cargar los datos de comida desde JSON
void show_feed_screen(); // Declaración de la función

#endif