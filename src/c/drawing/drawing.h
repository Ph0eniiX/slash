#pragma once

// various variable declarations
int battery_level;

// various function declarations
void time_draw_update_proc(Layer *layer, GContext *ctx);
void date_update_proc(Layer *layer, GContext *ctx);
void bat_update_proc(Layer *layer, GContext *ctx);
void bg_update_proc(Layer *layer, GContext *ctx);
void draw_flag_update_proc(Layer *layer, GContext *ctx);

void update_time();