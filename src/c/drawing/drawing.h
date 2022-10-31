#pragma once

static char hour_char[] = "hh";
static char min_char[] = "mm";
static char date_char[] = "day mm/dd";
static int battery_level;
static int edge_size;

void time_draw_update_proc(Layer *layer, GContext *ctx);
void date_update_proc(Layer *layer, GContext *ctx);
void bat_update_proc(Layer *layer, GContext *ctx);
void bg_update_proc(Layer *layer, GContext *ctx);
void draw_flag_update_proc(Layer *layer, GContext *ctx);

void update_time();