#include <pebble.h>
#include "drawing.h"
#include "../main.h"

extern Window *main_window;

extern ClaySettings settings;

char hour_char[] = "hh";
char min_char[] = "mm";

static void draw_time(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    graphics_context_set_text_color(ctx, settings.main_color);
    graphics_draw_text(ctx, hour_char, settings.time_font, GRect(0, bounds.size.h / 2, bounds.size.w, 50), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
}

void update_time() {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    strftime(hour_char, sizeof(hour_char), clock_is_24h_style() ? "%H" : "%I", tick_time);
    strftime(min_char, sizeof(min_char), "%M", tick_time);
}