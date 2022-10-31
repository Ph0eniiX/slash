#pragma once

Animation *time_anim_start, *time_anim_end; 
Animation *date_anim_start, *date_anim_end;
Animation *bat_anim_start, *bat_anim_end;
bool is_animate_scheduled;

// sets properties and returns created animation
Animation *anim_set_props(GRect frame_start, GRect frame_end, Layer *layer, int delay_ms, int duration_ms);

// creates all animations in the program
void anim_create(GRect bounds_full, int delay, int duration, int onscreen);

// runs all animations in the program
void anim_run(GRect bounds_full, GRect bounds_unobstructed);