#include "clean_screen.h"
#include "ui.h"

lv_obj_t * clean_screen;

static void back_button_event_handler(lv_event_t * e) {
  if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
    show_main_screen();
  }
}

void clean_screen_init() {
  clean_screen = lv_obj_create(NULL);

  // Add a label for the screen name
  lv_obj_t * label = lv_label_create(clean_screen);
  lv_label_set_text(label, "clean Screen");
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

  // Add a back button
  lv_obj_t * btn_back = lv_btn_create(clean_screen);
  lv_obj_set_size(btn_back, 100, 40);
  lv_obj_align(btn_back, LV_ALIGN_BOTTOM_MID, 0, -10);
  lv_obj_add_event_cb(btn_back, back_button_event_handler, LV_EVENT_CLICKED, NULL);
  lv_obj_t * label_back = lv_label_create(btn_back);
  lv_label_set_text(label_back, "Back");
  lv_obj_center(label_back);
}