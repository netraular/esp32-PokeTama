#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include "ui.h"
#include "pet.h"

// Define the LVGL display buffer
static lv_color_t buf[240 * 10]; // Adjust size according to your display resolution
uint32_t lv_last_tick = 0; // Variable to track the last tick time

// Constants for frame rate control
const uint32_t FRAME_INTERVAL = 1000 / 30; // 30 FPS (33ms per frame)
uint32_t last_frame_time = 0; // Variable to track the last frame time

void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize the display
  smartdisplay_init();
  Serial.println("Display initialized.");

  // Initialize LVGL
  lv_init();
  Serial.println("LVGL initialized.");

  // Set up LVGL display buffer
  auto disp = lv_display_get_default();
  lv_display_set_buffers(disp, buf, NULL, sizeof(buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
  Serial.println("LVGL display buffer set.");

  // Initialize UI
  ui_init();
  Serial.println("UI initialized.");

  // Initialize pet
  pet_init();
  Serial.println("Pet initialized.");
}

void loop() {
  // Get the current time
  uint32_t current_time = millis();

  // Update LVGL tick
  lv_tick_inc(current_time - lv_last_tick);
  lv_last_tick = current_time;

  // Handle LVGL tasks
  lv_timer_handler();

  // Check if it's time to update (30 FPS)
  if (current_time - last_frame_time >= FRAME_INTERVAL) {
    last_frame_time = current_time;

    // Update pet state
    pet_update();

    // Update FPS counter
    update_fps();

    // Debugging: Print pet state and FPS periodically
    static uint32_t last_debug_time = 0;
    if (current_time - last_debug_time > 1000) { // Print every 1 second
      last_debug_time = current_time;
      Serial.print("Pet state - Hunger: ");
      Serial.print(hunger);
      Serial.print(", Happiness: ");
      Serial.println(happiness);

      // Get and display FPS
      uint32_t fps = get_fps();
      Serial.print("FPS: ");
      Serial.println(fps);
    }
  }
}