#include "ui.h"
#include "pet.h"
#include "images.h"

// Define the button event handler
static void btn_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    Serial.println("Button clicked: Showing image.");
    // Example action: Display an image
    lv_obj_t * img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, &imagen_ejemplo);
    lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);
  }
}

void ui_init() {
  // Create main screen elements
  lv_obj_t * btn = lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn, 100, 50);
  lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btn, btn_event_handler, LV_EVENT_ALL, NULL);

  lv_obj_t * label = lv_label_create(btn);
  lv_label_set_text(label, "Feed");
  lv_obj_center(label);

  Serial.println("UI initialized with button.");
}

void ui_update() {
  // Update UI based on pet state
}