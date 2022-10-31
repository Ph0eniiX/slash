#pragma once

int battery_level;

void time_draw_update_proc(Layer *layer, GContext *ctx);
void date_update_proc(Layer *layer, GContext *ctx);
void bat_update_proc(Layer *layer, GContext *ctx);
void bg_update_proc(Layer *layer, GContext *ctx);

// updates time and sets each string to current value
void update_time();