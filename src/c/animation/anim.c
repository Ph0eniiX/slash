#include <pebble.h>
#include "anim.h"

extern Window *main_window;
extern Layer *time_layer, *date_layer;
extern Animation *time_anim_start, *time_anim_end, *date_anim_start, *date_anim_end;

void set_animation(Layer *layer, int delay, int duration, GRect *from_rect, GRect *to_rect, Animation *anim) {
    PropertyAnimation *prop_anim = property_animation_create_layer_frame(layer, from_rect, to_rect);
    
    anim = property_animation_get_animation(prop_anim);

    animation_set_curve(anim, AnimationCurveEaseInOut);
    animation_set_delay(anim, delay);
    animation_set_duration(anim, duration);
}

void animate_stuff() {
    GRect bounds = layer_get_bounds(window_get_root_layer(main_window));

    //variabls
    int delay_ms = 0;
    int duration_ms = 200;
    int onscreen_ms = 3000;

    //makes the coordinates for the animation
    GRect date_start_rect = GRect(0, 50, bounds.size.w, bounds.size.h);
    GRect date_end_rect = GRect(0, 0, bounds.size.w, bounds.size.h);

    GRect time_start_rect = GRect(0, 0, bounds.size.w, bounds.size.h);
    GRect time_end_rect = GRect(0, -10, bounds.size.w, bounds.size.h);

    //set_animation(date_layer, delay_ms, duration_ms, &anim_date_start_rect, &anim_date_end_rect, date_anim_start);
    //set_animation(date_layer, onscreen_ms, duration_ms, &anim_date_end_rect, &anim_date_start_rect, date_anim_end);

    //define property animations
    PropertyAnimation *prop_anim_date_start = property_animation_create_layer_frame(date_layer, &date_start_rect, &date_end_rect);
    PropertyAnimation *prop_anim_date_end = property_animation_create_layer_frame(date_layer, &date_end_rect, &date_start_rect);

    PropertyAnimation *prop_anim_time_start = property_animation_create_layer_frame(time_layer, &time_start_rect, &time_end_rect);
    PropertyAnimation *prop_anim_time_end = property_animation_create_layer_frame(time_layer, &time_end_rect, &time_start_rect);

    //sets the property animations to each animation variable
    date_anim_start = property_animation_get_animation(prop_anim_date_start);
    date_anim_end = property_animation_get_animation(prop_anim_date_end);

    time_anim_start = property_animation_get_animation(prop_anim_time_start);
    time_anim_end = property_animation_get_animation(prop_anim_time_end);

    //date set properties
    animation_set_curve(date_anim_start, AnimationCurveEaseInOut);
    animation_set_delay(date_anim_start, delay_ms);
    animation_set_duration(date_anim_start, duration_ms);

    animation_set_curve(date_anim_end, AnimationCurveEaseInOut);
    animation_set_delay(date_anim_end, onscreen_ms);
    animation_set_duration(date_anim_end, duration_ms);

    //time set properties
    animation_set_curve(time_anim_start, AnimationCurveEaseInOut);
    animation_set_delay(time_anim_start, delay_ms);
    animation_set_duration(time_anim_start, duration_ms);

    animation_set_curve(time_anim_end, AnimationCurveEaseInOut);
    animation_set_delay(time_anim_end, onscreen_ms);
    animation_set_duration(time_anim_end, duration_ms);

    start_spawn = animation_spawn_create(time_anim_start, date_anim_start, NULL);
    end_spawn = animation_spawn_create(time_anim_end, date_anim_end, NULL);
}