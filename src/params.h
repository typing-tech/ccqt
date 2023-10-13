#pragma once

#include <cstdint>

static char const *MESSAGES[] = {
    "Enable Serial Header",
    "Enable Serial Logging",
    "Enable Serial Debugging",
    "Enable Serial Raw",
    "Enable Serial Chord",
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
    "Chord Detection Press Tolerance",
    "Chord Detection Release Tolerance",

    "Enable Spurring",
    "Enable Spurring Character Counter Timeout",

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

static constexpr unsigned const MESSAGES_LEN = 36;

struct Parameters {
  uint16_t parameters[MESSAGES_LEN] = {0};
  uint16_t parameters_modified[MESSAGES_LEN] = {0};
};

void get_diff(Parameters &params, bool *output_diff[MESSAGES_LEN]);
