#include <pebble.h>
#include "config.h"
#include "../main.h"

extern ClaySettings settings;

static void set_defaults() {
    settings.bg_color = GColorBlack;
    settings.main_color = GColorWhite;
    settings.slash_color = GColorMagenta;
    settings.time_font = fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS);
}

void load_settings() {
    set_defaults();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}