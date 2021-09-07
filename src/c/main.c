#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/config.h"
#include "messaging/messaging.h"

//main window and layer variable stuff
Window *main_window;
Layer *time_layer, *flag;

ClaySettings settings;

//bluetooth buzz function
static void bluetooth_callback(bool connected) {
  if(settings.do_bt_buzz == true && !connected) {
    vibes_short_pulse();
  }
}

//universal update and set the settings to everything
void update_stuff() {
  window_set_background_color(main_window, settings.bg_color);

  update_time();

  layer_mark_dirty(time_layer);
}

//actual app window loading functions
static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  window_set_background_color(main_window, settings.bg_color);

  //draw flag


  //draw time
  /*
  time_layer = layer_create(bounds);
  layer_set_update_proc(time_layer, time_draw_update_proc);
  layer_add_child(window_layer, time_layer);
  */
  
}

//unloading functions !!
static void main_window_unload() {
  layer_destroy(time_layer);
}

//app initialize function
static void init() {
  main_window = window_create();

  window_set_window_handlers(main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(main_window, true);
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