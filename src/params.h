#pragma once

#include <cstdint>

static unsigned const PARAM_IDS[] = {
    1,  2,  3,  4,  5,  6,  7,

    11, 12, 13, 14, 15, 16, 17,

    21, 22, 23, 24, 25, 26,

    31, 32, 33, 34, 35,

    41, 42, 43,

    51, 54,

    61, 64,

    81, 82,

    83, 84, 91, 92, 93,
};

static constexpr unsigned const MESSAGES_LEN = sizeof(PARAM_IDS) / sizeof(int);

static char const *MESSAGES[MESSAGES_LEN] = {
    "Enable Serial Header",
    "Enable Serial Logging",
    "Enable Serial Debugging",
    "Enable Serial Raw",
    "Enable Serial Chord",
    "Enable Serial Keyboard",
    "Enable Serial Mouse",

    "Enable Usb Hid Keyboard",
    "Enable Character Entry",
    "Gui Ctrl Swap Mode (CCL Only)",
    "Key Scan Duration",
    "Key Debounce Press Duration",
    "Key Debounce Release Duration",
    "Keyboard Output Character Microseconds Delays",

    "Enable Usb HID Mouse",
    "Slow Mouse Speed",
    "Fast Mouse Speed",
    "Enable ActiveMs",
    "Mouse Scroll Speed",
    "Mouse Poll Duration",

    "Enable Chording",
    "Enable Chording Character Counter Timeout",
    "Chording Character Counter Timeout Timer",
    "Chord Detection Press Tolerance",
    "Chord Detection Release Tolerance",

    "Enable Spurring",
    "Enable Spurring Character Counter Timeout",
    "Spurring Character Counter Timeout Timer",

    "Enable Arpeggiates",
    "Arpeggiate Tolerance",

    "Enable Compound Chording (WIP)",
    "Compound Tolerance",

    "LED Brightness",
    "LED ColorCode (CCL Only)",

    "Enable Key Highlight (WIP, CCL Only)",
    "Enable Leds (CCL Only)",
    "Operating System",
    "Enable Realtime Feedback",
    "Enable CharaChorder Ready On Startup",
};

struct Parameters {
  uint16_t parameters[MESSAGES_LEN] = {0};
  uint16_t parameters_modified[MESSAGES_LEN] = {0};
};

void get_diff(Parameters &params, bool *output_diff[MESSAGES_LEN]);
