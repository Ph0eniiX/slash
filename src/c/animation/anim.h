#pragma once

// creates all animations in the program
void anim_create(GRect bounds_full, int delay, int duration, int onscreen);

// runs all animations in the program
void anim_run(GRect bounds_full, GRect bounds_unobstructed);