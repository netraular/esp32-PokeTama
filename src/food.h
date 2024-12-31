#ifndef FOOD_H
#define FOOD_H

#include <Arduino.h> // Incluir Arduino.h para usar String
#include <lvgl.h>

// Estructura para representar la comida
typedef struct {
    int id;
    String name; // Usar String
    int hunger;
    int health;
    int happiness;
    int quantity;
    int price;
    String image; // Usar String
} Food;

#endif