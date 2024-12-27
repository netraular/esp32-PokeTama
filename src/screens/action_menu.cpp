#include "action_menu.h"
#include "ui.h"

lv_obj_t * action_menu;

static void action_menu_event_handler(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if (code == LV_EVENT_CLICKED) {
    lv_obj_t * btn = (lv_obj_t *)lv_event_get_target(e);
    const char * btn_text = lv_label_get_text(lv_obj_get_child(btn, 0));

    if (strcmp(btn_text, "Status") == 0) {
      show_status_screen();
    } else if (strcmp(btn_text, "Feed") == 0) {
      show_feed_screen();
    } else if (strcmp(btn_text, "Play") == 0) {
      show_play_screen();
    } else if (strcmp(btn_text, "Shop") == 0) {
      show_shop_screen();
    } else if (strcmp(btn_text, "Sleep") == 0) {
      show_sleep_screen();
    } else if (strcmp(btn_text, "Clean") == 0) {
      show_clean_screen();
    } else if (strcmp(btn_text, "Heal") == 0) {
      show_heal_screen();
    } else if (strcmp(btn_text, "Style") == 0) {
      show_style_screen();
    } else if (strcmp(btn_text, "Connect") == 0) {
      show_connect_screen();
    } else if (strcmp(btn_text, "Settings") == 0) {
      show_settings_screen();
    } else if (strcmp(btn_text, "Back") == 0) {
      show_main_screen();
    }
  }
}

void action_menu_init() {
  action_menu = lv_obj_create(NULL);

  // Add buttons to the action menu
  const char * actions[] = {"Status", "Feed", "Play", "Shop", "Sleep", "Clean", "Heal", "Style", "Connect", "Settings", "Back"};
  for (int i = 0; i < 11; i++) {
    lv_obj_t * btn = lv_btn_create(action_menu);
    lv_obj_set_size(btn, 180, 30);
    lv_obj_align(btn, LV_ALIGN_TOP_MID, 0, 10 + i * 35);
    lv_obj_add_event_cb(btn, action_menu_event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t * label = lv_label_create(btn);
    lv_label_set_text(label, actions[i]);
    lv_obj_center(label);
  }
}