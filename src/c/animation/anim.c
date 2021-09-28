#include <pebble.h>

extern Window *main_window;
extern Layer *time_layer, *flag_layer, *bg_cover, *date_layer;
extern Animation *time_anim_start, *time_anim_end, *date_anim_start, *date_anim_end;

void animate_stuff() {
    GRect bounds = layer_get_bounds(window_get_root_layer(main_window));

    //makes the coordinates for the animation
    GRect anim_date_start = GRect(0, 50, bounds.size.w, bounds.size.h);
    GRect anim_date_end = GRect(0, 0, bounds.size.w, bounds.size.h);

    GRect anim_time_start = GRect(0, 0, bounds.size.w, bounds.size.h);
    GRect anim_time_end = GRect(0, -10, bounds.size.w, bounds.size.h);

    //sets the coordinate GRect's to a temporary property animation
    PropertyAnimation *prop_anim_date_start = property_animation_create_layer_frame(date_layer, &anim_date_start, &anim_date_end);
    PropertyAnimation *prop_anim_time_start = property_animation_create_layer_frame(time_layer, &anim_time_start, &anim_time_end);

    PropertyAnimation *prop_anim_date_end = property_animation_create_layer_frame(date_layer, &anim_date_end, &anim_date_start);
    PropertyAnimation *prop_anim_time_end = property_animation_create_layer_frame(time_layer, &anim_time_end, &anim_time_start);

    //sets the property animations to each animation variable
    date_anim_start = property_animation_get_animation(prop_anim_date_start);
    date_anim_end = property_animation_get_animation(prop_anim_date_end);

    time_anim_start = property_animation_get_animation(prop_anim_time_start);
    time_anim_end = property_animation_get_animation(prop_anim_time_end);

    //variabls
    int delay_ms = 0;
    int duration_ms = 200;
    int onscreen_ms = 3000;

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
    
}