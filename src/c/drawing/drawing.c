#include <pebble.h>
#include "drawing.h"
#include "../main.h"

extern Window *main_window;

extern ClaySettings settings;

static char hour_char[] = "hh";
static char min_char[] = "mm";
static char date_char[] = "DAY MM/DD";

static int edge_size = 7;

extern int *flag_colors[];
extern int num_stripes[];

static void draw_flag(int segments, int colors[], GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    if(settings.rot_flag == 3) {
        int h = bounds.size.h;
        int w = bounds.size.w / segments + (bounds.size.w % segments != 0);

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(w * i, 0, w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    } else if(settings.rot_flag == 2) {
        int h = -1 * bounds.size.h / segments - (-1 * bounds.size.h % segments != 0);
        int w = bounds.size.w;

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(0, bounds.size.h + (h * i), w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    } else if(settings.rot_flag == 1) {
        int h = bounds.size.h;
        int w = -1 * bounds.size.w / segments - (bounds.size.w % segments != 0);

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(bounds.size.w + (w * i), 0, w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    } else {
        int h = bounds.size.h / segments + (bounds.size.h % segments != 0);
        int w = bounds.size.w;

        for (int i = 0; i < segments; i++) {
            GRect flag_stripe = GRect(0, h * i, w, h);

            graphics_context_set_fill_color(ctx, GColorFromHEX(colors[i]));
            graphics_fill_rect(ctx, flag_stripe, 0, GCornerNone);
        }
    }
}

static void draw_bg_rect(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    graphics_context_set_fill_color(ctx, settings.bg_color);
    
    graphics_fill_rect(ctx, GRect(edge_size, edge_size, bounds.size.w - 2 * edge_size, bounds.size.h - 2 * edge_size), 0, 0);
}

static void draw_bg_circle(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    int edge_size = 7;

    graphics_fill_circle(ctx, GPoint(bounds.size.w / 2, bounds.size.h / 2), bounds.size.h / 2 - edge_size);
}

static void draw_time(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
    
    int y_offset = 25;
    int x_offset = 25;

    int line_y_shift = 0;
    int line_y_offset = 40;
    int line_x_offset = 30;

    //drawing the time things
    graphics_context_set_text_color(ctx, settings.main_color);
    graphics_draw_text(ctx, hour_char, settings.time_font, GRect(0 - x_offset, bounds.size.h / 2 - 26 - y_offset, bounds.size.w, 50), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
    graphics_draw_text(ctx, min_char, settings.time_font, GRect(0 + x_offset, bounds.size.h / 2 - 26 + y_offset, bounds.size.w, 50), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);

    graphics_context_set_stroke_color(ctx, settings.slash_color);
    graphics_context_set_stroke_width(ctx, 5);
    graphics_draw_line(ctx, GPoint(bounds.size.w / 2 - line_x_offset, bounds.size.h / 2 + line_y_offset + line_y_shift), GPoint(bounds.size.w / 2 + line_x_offset, bounds.size.h / 2 - line_y_offset + line_y_shift));
}

static void draw_date(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));
    
    graphics_context_set_text_color(ctx, settings.main_color);
    graphics_draw_text(ctx, date_char, FONT_KEY_GOTHIC_24_BOLD, GRect(0, bounds.size.h - 60, bounds.size.w, bounds.size.h), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
}

void bg_update_proc(Layer *layer, GContext *ctx) {
    PBL_IF_ROUND_ELSE(draw_bg_circle(ctx), draw_bg_rect(ctx));
}

void flag_update_proc(Layer *layer, GContext *ctx) {
    draw_flag(num_stripes[settings.flag_number], flag_colors[settings.flag_number], ctx);
}

void time_draw_update_proc(Layer *layer, GContext *ctx) {
    draw_time(ctx);
}

void date_update_proc(Layer *layer, GContext *ctx) {
    draw_date(ctx);
}

void update_time() {
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    strftime(hour_char, sizeof(hour_char), clock_is_24h_style() ? "%H" : "%I", tick_time);
    strftime(min_char, sizeof(min_char), "%M", tick_time);
    strftime(date_char, sizeof(date_char), "%a %m/%d", tick_time);
}