#include <pebble.h>
#include "anim.h"
#include "../main.h"

// sets animate_scheduled boolean to false after the animation finishes
static void s_timer_callback(void *ctx) {
    is_animate_scheduled = false;
    layer_set_hidden(bat_layer, true);
}

// sets the properties of an animation
static void s_set_animation_things(Animation *anim, int delay, int duration) {
    animation_set_curve(anim, AnimationCurveEaseInOut);
    animation_set_delay(anim, delay);
    animation_set_duration(anim, duration);
}

// sets all animation variables and properties
void set_anim_props(GRect bounds_full, int delay_ms, int duration_ms, int onscreen_ms) {
    // makes the coordinates for the animation
    GRect date_start_rect = GRect(0, 50, bounds_full.size.w, bounds_full.size.h);
    GRect date_end_rect = GRect(0, 0, bounds_full.size.w, bounds_full.size.h);

    GRect time_start_rect = GRect(0, 0, bounds_full.size.w, bounds_full.size.h);
    GRect time_end_rect = GRect(0, -10, bounds_full.size.w, bounds_full.size.h);

    GRect bat_start_rect = GRect(0, 7, bounds_full.size.w, bounds_full.size.h);
    GRect bat_end_rect = GRect(0, 0, bounds_full.size.w, bounds_full.size.h);

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
    s_set_animation_things(date_anim_start, delay_ms, duration_ms);
    s_set_animation_things(date_anim_end, onscreen_ms, duration_ms);

    // time set things
    s_set_animation_things(time_anim_start, delay_ms, duration_ms);
    s_set_animation_things(time_anim_end, onscreen_ms, duration_ms);

    // bat bar set things
    s_set_animation_things(bat_anim_start, delay_ms, duration_ms);
    s_set_animation_things(bat_anim_end, onscreen_ms, duration_ms);
}

/*
// sets all animation variables and properties
void set_anim_props(Animation *anim_start, Layer *layer, GRect frame_start, GRect frame_end, GRect bounds_full, int delay_ms, int duration_ms, int onscreen_m) {
    // define property animations
    PropertyAnimation *prop_anim_start = property_animation_create_layer_frame(layer, &frame_start, &frame_end);
    PropertyAnimation *prop_anim_end = property_animation_create_layer_frame(layer, &frame_end, &frame_start);

    bat_anim_start = property_animation_get_animation(prop_anim_bat_start);
    bat_anim_end = property_animation_get_animation(prop_anim_bat_end);

    // date set things
    s_set_animation_things(date_anim_start, delay_ms, duration_ms);
    s_set_animation_things(date_anim_end, onscreen_ms, duration_ms);

    // time set things
    s_set_animation_things(time_anim_start, delay_ms, duration_ms);
    s_set_animation_things(time_anim_end, onscreen_ms, duration_ms);

    // bat bar set things
    s_set_animation_things(bat_anim_start, delay_ms, duration_ms);
    s_set_animation_things(bat_anim_end, onscreen_ms, duration_ms);
}
*/

// running animations if not scheduled ==============================
void run_anim(GRect bounds_full, GRect bounds_unobstructed) {
    // if an animation isn't scheduled, animate everything
    if (!is_animate_scheduled) {
        is_animate_scheduled = true;
        app_timer_register(3400, s_timer_callback, NULL);

        set_anim_props(bounds_full, settings.anim_delay, settings.anim_duration, settings.anim_onscreen);

        // if date is enabled then show the layer then animate it
        if (settings.do_date && bounds_full.size.h == bounds_unobstructed.size.h) {
            layer_set_hidden(date_layer, false);

            Animation *start = animation_spawn_create(time_anim_start, date_anim_start, NULL);
            Animation *end = animation_spawn_create(time_anim_end, date_anim_end, NULL);

            animation_schedule(start);
            animation_schedule(end);
        }

        // if battery bar is enabled then show the layer then animate it
        if (settings.do_bat && bounds_full.size.w != bounds_full.size.h) {
            layer_set_hidden(bat_layer, false);

            animation_schedule(bat_anim_start);
            animation_schedule(bat_anim_end);
        } else if (settings.do_bat) {
            layer_set_hidden(bat_layer, false);
        }
    }
}