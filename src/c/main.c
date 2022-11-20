#include <pebble.h>
#include "main.h"
#include "animation/anim.h"
#include "config/config.h"
#include "drawing/drawing.h"
#include "drawing/pride.h"
#include "messaging/messaging.h"

// universal update function ========================================
void update_stuff() {
    window_set_background_color(main_window, settings.slash_color);

    // redraw all layers
    layer_mark_dirty(time_layer);
    layer_mark_dirty(flag_layer);
    layer_mark_dirty(bg_cover);
    layer_mark_dirty(date_layer);
    layer_mark_dirty(bat_layer);
}

// handlers =========================================================

static void battery_callback(BatteryChargeState state) {
    battery_level = state.charge_percent;
    layer_mark_dirty(bat_layer);
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
    anim_run(layer_get_bounds(window_get_root_layer(main_window)), layer_get_unobstructed_bounds(window_get_root_layer(main_window)));
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
    layer_mark_dirty(time_layer);
}

// window load and unload ===========================================

static void main_window_load(Window *window) {
    // initalizing window layer and main window bounds rect
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    update_time();

    window_set_background_color(main_window, settings.slash_color);

    // draw flag
    flag_layer = layer_create(bounds);
    layer_set_update_proc(flag_layer, pride_update_proc);
    layer_add_child(window_layer, flag_layer);

    // draw battery bar
    bat_layer = layer_create(bounds);
    layer_set_update_proc(bat_layer, bat_update_proc);
    layer_add_child(window_layer, bat_layer);
    layer_set_hidden(bat_layer, true);

    // draw bg over flag and background to make a ring effect
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

    anim_create(bounds, settings.anim_delay, settings.anim_duration, settings.anim_onscreen);

    update_stuff();
}

static void main_window_unload() {
    layer_destroy(time_layer);
    layer_destroy(flag_layer);
    layer_destroy(bg_cover);
    layer_destroy(date_layer);
    layer_destroy(bat_layer);
}

// init and deinit ==========================================

static void init() {
    main_window = window_create();

    // subscribing to watch services
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    battery_state_service_subscribe(battery_callback);
    accel_tap_service_subscribe(accel_tap_handler);
    connection_service_subscribe((ConnectionHandlers) {
        .pebble_app_connection_handler = bluetooth_callback
    });

    // setting the functions when the window loads and unloads
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

static void deinit() {
    tick_timer_service_unsubscribe();
    accel_data_service_unsubscribe();
    battery_state_service_unsubscribe();
    connection_service_unsubscribe();
    window_destroy(main_window);
}

// MAIN =============================================================
int main() {
    init();
    app_event_loop();
    deinit();
}

// master chief? you mind telling me what you are doing at mcdonalds?

// sir, finishing this big mac

// https://www.youtube.com/watch?v=tCUJ8JqiyZc