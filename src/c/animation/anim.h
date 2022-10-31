#pragma once

// various variable declarations
Animation *time_anim_start, *time_anim_end; 
Animation *date_anim_start, *date_anim_end;
Animation *bat_anim_start, *bat_anim_end;
bool is_animate_scheduled;

// various function declarations
//void set_anim_props(GRect bounds_full, int delay_ms, int duration_ms, int onscreen_m, Animation *anim_start, Animation *anim_end);
void set_anim_props(GRect bounds_full, int delay_ms, int duration_ms, int onscreen_ms);
void run_anim(GRect bounds_full, GRect bounds_unobstructed);