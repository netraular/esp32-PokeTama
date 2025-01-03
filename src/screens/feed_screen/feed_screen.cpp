#include "screens/feed_screen/feed_screen.h"
#include "ui.h"
#include "pet.h" // Include pet.h to access hunger and happiness
#include "feed_screen.h"
#include <ArduinoJson.h>
#include <LittleFS.h> // Include LittleFS library

lv_obj_t * feed_screen;
Food foods[10]; // Adjust size based on the number of foods
int food_count = 0;

// Function to handle back button click
static void back_button_event_handler(lv_event_t * e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        show_main_screen();
    }
}

// Function to handle food button click
// Function to handle food button click
void food_button_event_handler(lv_event_t * e) {
    int food_id = (int)lv_event_get_user_data(e) - 1; // Ajustar el índice
    Serial.print("Selected food ID: ");
    Serial.println(food_id + 1); // Mostrar el ID correcto en el terminal

    // Mostrar todos los datos de la comida seleccionada por serial
    Serial.println("Food Details:");
    Serial.print("ID: ");
    Serial.println(foods[food_id].id);
    Serial.print("Name: ");
    Serial.println(foods[food_id].name);
    Serial.print("Hunger: ");
    Serial.println(foods[food_id].hunger);
    Serial.print("Health: ");
    Serial.println(foods[food_id].health);
    Serial.print("Happiness: ");
    Serial.println(foods[food_id].happiness);
    Serial.print("Quantity: ");
    Serial.println(foods[food_id].quantity);
    Serial.print("Price: ");
    Serial.println(foods[food_id].price);
    Serial.print("Image: ");
    Serial.println(foods[food_id].image);

    // Update pet's state based on the selected food
    hunger += foods[food_id].hunger;
    health += foods[food_id].health;
    happiness += foods[food_id].happiness;

    // Decrease the quantity of the selected food
    foods[food_id].quantity--;

    // Update the button label to reflect the new quantity
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e); // Cast to lv_obj_t*
    lv_obj_t * btn_label = lv_obj_get_child(btn, 0); // Get the label inside the button
    lv_label_set_text_fmt(btn_label, "%s (%d)", foods[food_id].name.c_str(), foods[food_id].quantity);

    // Disable or hide the button if the quantity is zero
    if (foods[food_id].quantity <= 0) {
        lv_obj_add_flag(btn, LV_OBJ_FLAG_HIDDEN); // Hide the button
    }

    // Update the food.json file
    File file = LittleFS.open("/data/food.json", "w");
    if (!file) {
        Serial.println("Failed to update food.json!");
        return;
    }

    // Create a JSON document with the updated food data
    JsonDocument doc;
    for (int i = 0; i < food_count; i++) {
        JsonObject food = doc.add<JsonObject>();
        food["id"] = foods[i].id;
        food["name"] = foods[i].name; // Usar String
        food["hunger"] = foods[i].hunger;
        food["health"] = foods[i].health;
        food["happiness"] = foods[i].happiness;
        food["quantity"] = foods[i].quantity;
        food["price"] = foods[i].price;
        food["image"] = foods[i].image; // Usar String
    }

    // Write the updated data to the file
    file.seek(0); // Asegúrate de que el archivo esté en la posición inicial
    serializeJson(doc, file);
    file.close();
    Serial.println("food.json updated.");

    // Return to the main screen
    show_main_screen();
}

void load_food_data() {
    // Open the food.json file
    File file = LittleFS.open("/data/food.json", "r");
    if (!file) {
        Serial.println("Failed to open food.json!");
        return;
    }

    // Parse JSON data
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    file.close();

    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    // Load food data into the array
    food_count = doc.size();
    for (int i = 0; i < food_count; i++) {
        foods[i].id = doc[i]["id"];
        foods[i].name = doc[i]["name"].as<String>(); // Convertir a String
        foods[i].hunger = doc[i]["hunger"];
        foods[i].health = doc[i]["health"];
        foods[i].happiness = doc[i]["happiness"];
        foods[i].quantity = doc[i]["quantity"];
        foods[i].price = doc[i]["price"];
        foods[i].image = doc[i]["image"].as<String>(); // Convertir a String

        // Debug: Print loaded food data
        Serial.print("Loaded food: ");
        Serial.print(foods[i].id);
        Serial.print(", ");
        Serial.print(foods[i].name);
        Serial.print(", Quantity: ");
        Serial.println(foods[i].quantity);
    }
}

void create_food_buttons() {
    // Clear existing buttons
    lv_obj_clean(feed_screen);

    // Add a label for the screen name
    lv_obj_t * label = lv_label_create(feed_screen);
    lv_label_set_text(label, "Feed Screen");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    int y_offset = 50; // Initial Y position for the first button

    // Create buttons for each food item
    for (int i = 0; i < food_count; i++) {
        // Skip if the quantity is zero
        if (foods[i].quantity <= 0) {
            continue;
        }

        // Create a button for the food item
        lv_obj_t * btn = lv_btn_create(feed_screen);
        lv_obj_set_size(btn, 200, 40); // Wider button to accommodate text
        lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, y_offset); // Centered horizontally
        lv_obj_add_event_cb(btn, food_button_event_handler, LV_EVENT_CLICKED, (void*)(i + 1)); // Pasar el ID correcto

        // Add the food name and quantity as a label
        lv_obj_t * btn_label = lv_label_create(btn);
        lv_label_set_text_fmt(btn_label, "%s (%d)", foods[i].name.c_str(), foods[i].quantity);
        lv_obj_center(btn_label); // Center the label inside the button

        y_offset += 50; // Increment Y position for the next button
    }

    // Add a back button at the end of the list
    lv_obj_t * btn_back = lv_btn_create(feed_screen);
    lv_obj_set_size(btn_back, 200, 40);
    lv_obj_align(btn_back, LV_ALIGN_TOP_MID, 0, y_offset); // Centered horizontally
    lv_obj_add_event_cb(btn_back, back_button_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t * label_back = lv_label_create(btn_back);
    lv_label_set_text(label_back, "Back");
    lv_obj_center(label_back);
}

void feed_screen_init() {
    feed_screen = lv_obj_create(NULL);
    load_food_data();
    create_food_buttons();
}

void show_feed_screen() {
    load_food_data();
    create_food_buttons();
    lv_scr_load(feed_screen);
}