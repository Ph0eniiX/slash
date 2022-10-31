#pragma once
#include <pebble.h>

// struct that contains all settings in program
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
    int border_size;
} ClaySettings;

Window *main_window;
Layer *time_layer;
Layer *flag_layer;
Layer *bg_cover;
Layer *date_layer;
Layer *bat_layer;
ClaySettings settings;

// updates and redraws all layers
void update_stuff();