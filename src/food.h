#ifndef FOOD_H
#define FOOD_H

// Estructura para representar la comida
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

#endif