#include <pebble.h>
#include "messaging.h"
#include "../main.h"
#include "../config/config.h"

extern ClaySettings settings;

static void inbox_recieved_handler(DictionaryIterator *iter, void *ctx) {
    Tuple *bg_color_t = dict_find(iter, MESSAGE_KEY_bg_color_key);
    if(bg_color_t) {
        settings.bg_color = GColorFromHEX(bg_color_t->value->int32);
    }

    Tuple *main_color_t = dict_find(iter, MESSAGE_KEY_main_color_key);
    if(main_color_t) {
        settings.main_color = GColorFromHEX(main_color_t->value->int32);
    }

    Tuple *accent_color_t = dict_find(iter, MESSAGE_KEY_slash_color_key);
    if(accent_color_t) {
        settings.slash_color = GColorFromHEX(accent_color_t->value->int32);
    }

    Tuple *bt_buzz_t = dict_find(iter, MESSAGE_KEY_do_bt_buzz_key);
    if(bt_buzz_t) {
        settings.do_bt_buzz = bt_buzz_t->value->int32 == 1;
    }

    Tuple *flag_t = dict_find(iter, MESSAGE_KEY_flag_number_key);
    if(flag_t) {
        settings.flag_number = atoi(flag_t->value->cstring);
    }

    Tuple *rot_flag_t = dict_find(iter, MESSAGE_KEY_rotate_flag_key);
    if(rot_flag_t) {
        settings.rot_flag = atoi(rot_flag_t->value->cstring);
    }

    save_settings();
}

void init_msg() {
    app_message_register_inbox_received(inbox_recieved_handler);
    app_message_open(256, 256);
}