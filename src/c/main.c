#include <pebble.h>
#include "main.h"
#include "animation/anim.h"
#include "config/config.h"
#include "drawing/drawing.h"
#include "messaging/messaging.h"

// looking back... damn, my code is messy
// i gotta do this better next time

// I'm gonna go clean this stuff up now :]

// universal update and set the settings to everything
void update_stuff() {
    // redraw background with correct color
    window_set_background_color(main_window, settings.slash_color);

    // redraw all layers
    layer_mark_dirty(time_layer);
    layer_mark_dirty(flag_layer);
    layer_mark_dirty(bg_cover);
    layer_mark_dirty(date_layer);
    layer_mark_dirty(bat_layer);
}

// what to do when battery changes
static void battery_callback(BatteryChargeState state) {
    battery_level = state.charge_percent;
    layer_mark_dirty(bat_layer);
}

// what to do when watch is "tapped" (shake)
static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
    do_anim_if_not_scheduled();
}

// updates and draws time
void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
    layer_mark_dirty(time_layer);
}

// actual app window loading functions
static void main_window_load(Window *window) {
    // initalizing window layer and main window bounds rect
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    window_set_background_color(main_window, settings.slash_color);

    // draw flag
    flag_layer = layer_create(bounds);
    layer_set_update_proc(flag_layer, draw_flag_update_proc);
    layer_add_child(window_layer, flag_layer);

    // draw battery bar
    bat_layer = layer_create(bounds);
    layer_set_update_proc(bat_layer, bat_update_proc);
    layer_add_child(window_layer, bat_layer);
    layer_set_hidden(bat_layer, true);

    // draw bg over flag
    bg_cover = layer_create(bounds);
    layer_set_update_proc(bg_cover, bg_update_proc);
    layer_add_child(window_layer, bg_cover);

    // draw time
    time_layer = layer_create(bounds);
    layer_set_update_proc(time_layer, time_draw_update_proc);
    layer_add_child(window_layer, time_layer);

    // draw date
    date_layer = layer_create(bounds);
    layer_set_update_proc(date_layer, date_update_proc);
    layer_add_child(window_layer, date_layer);
    layer_set_hidden(date_layer, true);

    set_anim_props();

    update_stuff();
}

// unloading functions !!
static void main_window_unload() {
    layer_destroy(time_layer);
    layer_destroy(flag_layer);
    layer_destroy(bg_cover);
    layer_destroy(date_layer);
    layer_destroy(bat_layer);
}

// app initialize function
static void init() {
    main_window = window_create();

    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    battery_state_service_subscribe(battery_callback);
    accel_tap_service_subscribe(accel_tap_handler);
    connection_service_subscribe((ConnectionHandlers) {
        .pebble_app_connection_handler = bluetooth_callback
    });

    window_set_window_handlers(main_window, (WindowHandlers){
        .load = main_window_load,
        .unload = main_window_unload}
    );

    init_msg();
    load_settings();

    window_stack_push(main_window, true);

    bluetooth_callback(connection_service_peek_pebble_app_connection());
    battery_callback(battery_state_service_peek());
}

// app deinitialize function
static void deinit() {
    tick_timer_service_unsubscribe();
    accel_data_service_unsubscribe();
    battery_state_service_unsubscribe();
    connection_service_unsubscribe();
    window_destroy(main_window);
}

// main program, does literally EVERYTHING
int main() {
    init();
    app_event_loop();
    deinit();
}

// master chief? you mind telling me what you are doing at mcdonalds?

// sir, finishing this big mac

// https://www.youtube.com/watch?v=tCUJ8JqiyZc