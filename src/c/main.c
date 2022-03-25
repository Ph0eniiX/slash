#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/config.h"
#include "messaging/messaging.h"
#include "animation/anim.h"

//main window and layer variable stuff
Window *main_window;
Layer *time_layer, *flag_layer, *bg_cover, *date_layer, *bat_layer;

ClaySettings settings;

bool animate_scheduled = false;

//bluetooth buzz function
static void bluetooth_callback(bool connected) {
  if(settings.do_bt_buzz == true && !connected) {
    vibes_short_pulse();
  }
}

//sets animate_scheduled boolean to false after the animation finishes 
static void timer_callback(void *ctx) {
  animate_scheduled = false;
  layer_set_hidden(bat_layer, true);
}

static void battery_callback(BatteryChargeState state) {
  battery_level = state.charge_percent;
  layer_mark_dirty(bat_layer);
}

static void accel_tap_handler(AccelAxisType axis, int32_t direction) {
  GRect bounds_real = layer_get_bounds(window_get_root_layer(main_window));
  GRect bounds_unobstructed = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

  if(animate_scheduled == false && settings.do_date == true && bounds_real.size.h == bounds_unobstructed.size.h) {
    animate_scheduled = true;
    app_timer_register(3400, timer_callback, NULL);

    animate_stuff();

    layer_set_hidden(date_layer, false);
    layer_set_hidden(bat_layer, false);

    animation_schedule(start_spawn);
    animation_schedule(end_spawn);
  }
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  layer_mark_dirty(time_layer);
}

//universal update and set the settings to everything
void update_stuff() {
  update_time();

  window_set_background_color(main_window, settings.slash_color);

  layer_mark_dirty(time_layer);
  layer_mark_dirty(flag_layer);
  layer_mark_dirty(bg_cover);
  layer_mark_dirty(date_layer);
  layer_mark_dirty(bat_layer);
}

//actual app window loading functions
static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  window_set_background_color(main_window, settings.slash_color);

  //draw flag
  flag_layer = layer_create(bounds);
  layer_set_update_proc(flag_layer, flag_update_proc);
  layer_add_child(window_layer, flag_layer);

  //draw bg over flag
  bg_cover = layer_create(bounds);
  layer_set_update_proc(bg_cover, bg_update_proc);
  layer_add_child(window_layer, bg_cover);

  //draw time
  time_layer = layer_create(bounds);
  layer_set_update_proc(time_layer, time_draw_update_proc);
  layer_add_child(window_layer, time_layer);

  date_layer = layer_create(bounds);
  layer_set_update_proc(date_layer, date_update_proc);
  layer_add_child(window_layer, date_layer);
  layer_set_hidden(date_layer, true);

  bat_layer = layer_create(bounds);
  layer_set_update_proc(bat_layer, bat_update_proc);
  layer_add_child(window_layer, bat_layer);
  layer_set_hidden(bat_layer, true);

  animate_stuff();

  update_stuff();
}

//unloading functions !!
static void main_window_unload() {
  layer_destroy(time_layer);
  layer_destroy(flag_layer);
  layer_destroy(bg_cover);
  layer_destroy(date_layer);
}

//app initialize function
static void init() {
  main_window = window_create();

  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  battery_state_service_subscribe(battery_callback);

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  init_msg();
  load_settings();

  window_stack_push(main_window, true);

  accel_tap_service_subscribe(accel_tap_handler);
  bluetooth_callback(connection_service_peek_pebble_app_connection());  
  battery_callback(battery_state_service_peek());
}

static void deinit() {
  window_destroy(main_window);
  tick_timer_service_unsubscribe();
  accel_data_service_unsubscribe();
  battery_state_service_unsubscribe();
}

//master chief? you mind telling me what you are doing at mcdonalds?
int main() {
  init();
  app_event_loop();
  deinit();
}

//sir, finishing this big mac

//https://www.youtube.com/watch?v=tCUJ8JqiyZc