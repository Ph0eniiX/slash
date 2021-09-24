#pragma once
#include <pebble.h>

typedef struct ClaySettings {
    GColor bg_color;
    GColor main_color;
    GColor slash_color;
    GFont time_font;
    bool do_bt_buzz;
    bool do_date;
    int flag_number;
    int rot_flag;
} ClaySettings;

void update_stuff();