#pragma once
#include <pebble.h>

//main window and layers in header file so other files can access them
Window *main_window;
Layer *time_layer, *flag_layer, *bg_cover, *date_layer, *bat_layer;

typedef struct ClaySettings {
    GColor bg_color;
    GColor main_color;
    GColor slash_color;
    GFont time_font;
    bool do_bt_buzz;
    bool do_date;
    bool do_bat;
    int flag_number;
    int rot_flag;
} ClaySettings;

void update_stuff();