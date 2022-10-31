#pragma once
#include <pebble.h>

// defining all variables/settings in a struct for the entire program
typedef struct ClaySettings {
    GColor bg_color;
    GColor main_color;
    GColor slash_color;
    GFont time_font;
    bool do_bt_buzz;
    bool do_date;
    bool do_bat;
    int num_flag;
    int rot_flag;

    int anim_delay;
    int anim_duration;
    int anim_onscreen;
} ClaySettings;

// variable declarations
Window *main_window;
Layer *time_layer;
Layer *flag_layer;
Layer *bg_cover;
Layer *date_layer;
Layer *bat_layer;
ClaySettings settings;

// function declarations
void update_stuff();