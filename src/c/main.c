#include <pebble.h>
#include "main.h"
#include "drawing/drawing.h"
#include "config/config.h"
#include "messaging/messaging.h"

//main window and layer variable stuff
Window *main_window;
Layer *time_layer, *flag;

ClaySettings settings;

//actual app window loading functions
static void main_window_load(Window *window) {
  
}

//unloading functions !!
static void main_window_unload() {

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