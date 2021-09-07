#include <pebble.h>
#include "drawing.h"
#include "../main.h"

extern Window *main_window;

extern ClaySettings settings;

static char hour_char[] = "hh";
static char min_char[] = "mm";

extern int *flag_colors[];
extern int num_stripes[];

static void draw_flag(int segments, int colors[], GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    int h = bounds.size.h;
    int w = bounds.size.w / segments + (bounds.size.w % segments != 0);

    for (int i = 0; i < segments; i++) {
        GRect flag_stripe = GRect(w * i, 0, w, h);

        graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
        graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
    }
}

static void draw_time(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    graphics_context_set_text_color(ctx, settings.main_color);
    graphics_draw_text(ctx, hour_char, settings.time_font, GRect(0, bounds.size.h / 2, bounds.size.w, 50), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
}

void flag_update_proc(Layer *layer, GContext *ctx) {
    draw_flag(num_stripes[settings.flag_number], flag_colors[settings.flag_number], ctx);
}

void time_draw_update_proc(Layer *layer, GContext *ctx) {
    draw_time(ctx);
}

void update_time() {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    strftime(hour_char, sizeof(hour_char), clock_is_24h_style() ? "%H" : "%I", tick_time);
    strftime(min_char, sizeof(min_char), "%M", tick_time);
}