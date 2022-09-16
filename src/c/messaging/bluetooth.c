#include <pebble.h>
#include "../main.h"

// bluetooth callback function, buzzes when BT disconnects
void bluetooth_callback(bool connected) {
    if(settings.do_bt_buzz == true && !connected) {
        vibes_short_pulse();
    }
}