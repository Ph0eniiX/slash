#include <pebble.h>
#include "drawing.h"
#include "../main.h"

void update_time() {
    // makes a temp time variable and sets the current time stuff to it
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // string from time
    strftime(hour_char, sizeof(hour_char), clock_is_24h_style() ? "%H" : "%I", tick_time);
    strftime(min_char, sizeof(min_char), "%M", tick_time);
    strftime(date_char, sizeof(date_char), "%a %m/%d", tick_time);
}

// drawing functions ================================================

static void draw_bg_rect(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    graphics_context_set_fill_color(ctx, settings.bg_color);

    graphics_fill_rect(ctx, GRect(settings.edge_size, settings.edge_size, bounds.size.w - 2 * settings.edge_size, bounds.size.h - 2 * settings.edge_size), 0, 0);
}

static void draw_bg_circle(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    graphics_fill_circle(ctx, GPoint(bounds.size.w / 2, bounds.size.h / 2), bounds.size.h / 2 - settings.edge_size);
}

static void draw_time(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    int y_offset = 25;
    int x_offset = 25;

    int line_y_shift = 0;
    int line_y_offset = 40;
    int line_x_offset = 30;

    graphics_context_set_text_color(ctx, settings.main_color);

    // draw hour number
    GRect hour_textbox = GRect(0 - x_offset, bounds.size.h / 2 - 26 - y_offset, bounds.size.w, 50);
    graphics_draw_text(ctx,
        hour_char,
        settings.time_font,
        hour_textbox,
        GTextOverflowModeTrailingEllipsis,
        GTextAlignmentCenter,
        0
    );
    
    // draw minute number
    GRect min_textbox = GRect(0 + x_offset, bounds.size.h / 2 - 26 + y_offset, bounds.size.w, 50);
    graphics_draw_text(ctx,
        min_char, 
        settings.time_font, 
        min_textbox,
        GTextOverflowModeTrailingEllipsis,
        GTextAlignmentCenter,
        0
    );

    // draw the slash
    GPoint slash_point1 = GPoint(bounds.size.w / 2 - line_x_offset, bounds.size.h / 2 + line_y_offset + line_y_shift);
    GPoint slash_point2 = GPoint(bounds.size.w / 2 + line_x_offset, bounds.size.h / 2 - line_y_offset + line_y_shift);
    graphics_context_set_stroke_color(ctx, settings.slash_color);
    graphics_context_set_stroke_width(ctx, 5);
    graphics_draw_line(ctx, slash_point1, slash_point2);
}

static void draw_date(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    graphics_context_set_text_color(ctx, settings.main_color);
    graphics_draw_text(ctx, date_char, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD), GRect(0, bounds.size.h - 50, bounds.size.w, bounds.size.h), GTextOverflowModeTrailingEllipsis, GTextAlignmentCenter, 0);
}

static void draw_bat(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    int bat_bar_height = 7;

    GRect bat_rect = GRect((bounds.size.w * (100 - battery_level)) / 100 / 2, bounds.size.h - bat_bar_height, (bounds.size.w * battery_level) / 100, bat_bar_height);

    graphics_context_set_fill_color(ctx, settings.main_color);
    graphics_fill_rect(ctx, bat_rect, 0, GCornerNone);
}

static void draw_bat_chalk(GContext *ctx) {
    GRect bounds = layer_get_unobstructed_bounds(window_get_root_layer(main_window));

    int bat_bar_height = bounds.size.h;
    int bat_bar_width = (bounds.size.w * battery_level) / 100;

    GRect bat_rect = GRect((bounds.size.w - bat_bar_width) / 2, 0, bat_bar_width, bat_bar_height);

    graphics_context_set_fill_color(ctx, settings.main_color);
    graphics_fill_rect(ctx, bat_rect, 0, GCornerNone);
}

// update procs =====================================================

void bg_update_proc(Layer *layer, GContext *ctx) {
    PBL_IF_ROUND_ELSE(draw_bg_circle(ctx), draw_bg_rect(ctx));
}

void time_draw_update_proc(Layer *layer, GContext *ctx) {
    draw_time(ctx);
}

void date_update_proc(Layer *layer, GContext *ctx) {
    draw_date(ctx);
}

void bat_update_proc(Layer *layer, GContext *ctx) {
    PBL_IF_ROUND_ELSE(draw_bat_chalk(ctx), draw_bat(ctx));
}
