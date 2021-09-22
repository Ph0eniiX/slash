#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/config.h"
#include "messaging/messaging.h"

//main window and layer variable stuff
Window *main_window;
Layer *time_layer, *flag, *bg_cover;

ClaySettings settings;

//bluetooth buzz function
static void bluetooth_callback(bool connected) {
  if(settings.do_bt_buzz == true && !connected) {
    vibes_short_pulse();
  }
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
  layer_mark_dirty(time_layer);
}

//universal update and set the settings to everything
void update_stuff() {
  window_set_background_color(main_window, settings.slash_color);

  update_time();

  layer_mark_dirty(time_layer);
  layer_mark_dirty(flag);
}

//actual app window loading functions
static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  window_set_background_color(main_window, settings.slash_color);

  //draw flag
  flag = layer_create(bounds);
  layer_set_update_proc(flag, flag_update_proc);
  layer_add_child(window_layer, flag);

  //draw bg over flag
  bg_cover = layer_create(bounds);
  layer_set_update_proc(bg_cover, bg_update_proc);
  layer_add_child(window_layer, bg_cover);

  //draw time
  time_layer = layer_create(bounds);
  layer_set_update_proc(time_layer, time_draw_update_proc);
  layer_add_child(window_layer, time_layer);
}

//unloading functions !!
static void main_window_unload() {
  layer_destroy(time_layer);
}

//app initialize function
static void init() {
  main_window = window_create();

  //there's some sort of error in here, i'll fix later
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  init_msg();
  load_settings();

  window_stack_push(main_window, true);
  
  //bluetooth_callback(connection_service_peek_pebble_app_connection());
  
  update_stuff();
}

static void deinit() {
  window_destroy(main_window);
  tick_timer_service_unsubscribe();
}

//master chief? you mind telling me what you are doing at mcdonalds?
int main(void) {
  init();
  app_event_loop();
  deinit();
}

//sir, finishing this big mac

//https://www.youtube.com/watch?v=tCUJ8JqiyZc