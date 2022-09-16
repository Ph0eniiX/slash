#include <pebble.h>
#include "anim.h"
#include "../main.h"

bool is_animate_scheduled;

// sets animate_scheduled boolean to false after the animation finishes
static void timer_callback(void *ctx) {
    is_animate_scheduled = false;
    layer_set_hidden(bat_layer, true);
}

// sets the properties of an animation with an easy function
static void set_animation_things(Animation *anim, int delay, int duration) {
    animation_set_curve(anim, AnimationCurveEaseInOut);
    animation_set_delay(anim, delay);
    animation_set_duration(anim, duration);
}

// sets all animation variables and properties
void set_anim_props() {
    GRect bounds = layer_get_bounds(window_get_root_layer(main_window));

    // animation global(ish) variables
    int delay_ms = 0;
    int duration_ms = 200;
    int onscreen_ms = 3000;

    // makes the coordinates for the animation
    GRect date_start_rect = GRect(0, 50, bounds.size.w, bounds.size.h);
    GRect date_end_rect = GRect(0, 0, bounds.size.w, bounds.size.h);

    GRect time_start_rect = GRect(0, 0, bounds.size.w, bounds.size.h);
    GRect time_end_rect = GRect(0, -10, bounds.size.w, bounds.size.h);

    GRect bat_start_rect = GRect(0, 7, bounds.size.w, bounds.size.h);
    GRect bat_end_rect = GRect(0, 0, bounds.size.w, bounds.size.h);

    // define property animations
    PropertyAnimation *prop_anim_date_start = property_animation_create_layer_frame(date_layer, &date_start_rect, &date_end_rect);
    PropertyAnimation *prop_anim_date_end = property_animation_create_layer_frame(date_layer, &date_end_rect, &date_start_rect);

    PropertyAnimation *prop_anim_time_start = property_animation_create_layer_frame(time_layer, &time_start_rect, &time_end_rect);
    PropertyAnimation *prop_anim_time_end = property_animation_create_layer_frame(time_layer, &time_end_rect, &time_start_rect);

    PropertyAnimation *prop_anim_bat_start = property_animation_create_layer_frame(bat_layer, &bat_start_rect, &bat_end_rect);
    PropertyAnimation *prop_anim_bat_end = property_animation_create_layer_frame(bat_layer, &bat_end_rect, &bat_start_rect);

    // sets the property animations to each animation variable
    date_anim_start = property_animation_get_animation(prop_anim_date_start);
    date_anim_end = property_animation_get_animation(prop_anim_date_end);

    time_anim_start = property_animation_get_animation(prop_anim_time_start);
    time_anim_end = property_animation_get_animation(prop_anim_time_end);

    bat_anim_start = property_animation_get_animation(prop_anim_bat_start);
    bat_anim_end = property_animation_get_animation(prop_anim_bat_end);

    // date set things
    set_animation_things(date_anim_start, delay_ms, duration_ms);
    set_animation_things(date_anim_end, onscreen_ms, duration_ms);

    // time set things
    set_animation_things(time_anim_start, delay_ms, duration_ms);
    set_animation_things(time_anim_end, onscreen_ms, duration_ms);

    // bat bar set things
    set_animation_things(bat_anim_start, delay_ms, duration_ms);
    set_animation_things(bat_anim_end, onscreen_ms, duration_ms);
}

// doing the actual animations and displaying them on screen
void do_anim_if_not_scheduled() {
    GRect bounds_real = layer_get_bounds(window_get_root_layer(main_window));
    GRect bounds_unobstructed = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    // if an animation isn't scheduled, animate everything
    if (!is_animate_scheduled) {
        is_animate_scheduled = true;
        app_timer_register(3400, timer_callback, NULL);

        animate_stuff();

        if (settings.do_date && bounds_real.size.h == bounds_unobstructed.size.h) {
            layer_set_hidden(date_layer, false);

            Animation *start = animation_spawn_create(time_anim_start, date_anim_start, NULL);
            Animation *end = animation_spawn_create(time_anim_end, date_anim_end, NULL);

            animation_schedule(start);
            animation_schedule(end);
        }

        if (settings.do_bat && bounds_real.size.w != bounds_real.size.h) {
            layer_set_hidden(bat_layer, false);

            animation_schedule(bat_anim_start);
            animation_schedule(bat_anim_end);
        } else if (settings.do_bat) {
            layer_set_hidden(bat_layer, false);
        }
    }
}