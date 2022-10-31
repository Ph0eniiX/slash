#include <pebble.h>
#include "config.h"
#include "../main.h"

// loading these settings when nothing is configured
static void set_defaults() {
    settings.bg_color = GColorBlack;
    settings.main_color = GColorWhite;
    settings.slash_color = GColorRed;
    settings.time_font = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
    settings.do_bt_buzz = true;
    settings.do_date = true;
    settings.do_bat = true;
    settings.num_flag = 0;
    settings.rot_flag = 0;

    settings.anim_delay = 0;
    settings.anim_duration = 200;
    settings.anim_onscreen = 3000;
}

// loading settings from persistent storage
void load_settings() {
    set_defaults();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

// writing to persistent storage
void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}