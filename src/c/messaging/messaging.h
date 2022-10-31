#pragma once

// initializes messaging configuration
void init_msg();

// bluetooth callback function, buzzes when BT disconnects
void bluetooth_callback(bool connected);