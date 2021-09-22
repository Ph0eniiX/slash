#include <pebble.h>
#include "config.h"
#include "../main.h"

extern ClaySettings settings;

static void set_defaults() {
    settings.bg_color = GColorBlack;
    settings.main_color = GColorWhite;
    settings.slash_color = GColorRed;
    settings.time_font = fonts_get_system_font(FONT_KEY_BITHAM_42_MEDIUM_NUMBERS);
    settings.do_bt_buzz = true;
    settings.flag_number = 0;
    settings.rot_flag = 0;
}

void load_settings() {
    set_defaults();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}