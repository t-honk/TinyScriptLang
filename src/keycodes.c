#include "keycodes.h"
#include <string.h>

KeyMapping_t keyMappings[] = {
    {"LeftMouse", 0x01},
    {"RightMouse", 0x02},
    {"MiddleMouse", 0x04},
    {"X1Mouse", 0x05},
    {"X2Mouse", 0x06},
    {"BACKSPACE", 0x08},
    {"TAB", 0x09},
    {"ENTER", 0x0D},
    {"SHIFT", 0x10},
    {"CTRL", 0x11},
    {"ALT", 0x12},
    {"PAUSE", 0x13},
    {"CAPSLOCK", 0x14},
    {"ESC", 0x1B},
    {"SPACEBAR", 0x20},
    {"PAGEUP", 0x21},
    {"PAGEDOWN", 0x22},
    {"END", 0x23},
    {"HOME", 0x24},
    {"LEFTARROW", 0x25},
    {"UPARROW", 0x26},
    {"RIGHTARROW", 0x27},
    {"DOWNARROW", 0x28},
    {"PRINTSCREEN", 0x2C},
    {"INS", 0x2D},
    {"DEL", 0x2E},
    {"0", 0x30},
    {"1", 0x31},
    {"2", 0x32},
    {"3", 0x33},
    {"4", 0x34},
    {"5", 0x35},
    {"6", 0x36},
    {"7", 0x37},
    {"8", 0x38},
    {"9", 0x39},
    {"A", 0x41},
    {"B", 0x42},
    {"C", 0x43},
    {"D", 0x44},
    {"E", 0x45},
    {"F", 0x46},
    {"G", 0x47},
    {"H", 0x48},
    {"I", 0x49},
    {"J", 0x4A},
    {"K", 0x4B},
    {"L", 0x4C},
    {"M", 0x4D},
    {"N", 0x4E},
    {"O", 0x4F},
    {"P", 0x50},
    {"Q", 0x51},
    {"R", 0x52},
    {"S", 0x53},
    {"T", 0x54},
    {"U", 0x55},
    {"V", 0x56},
    {"W", 0x57},
    {"X", 0x58},
    {"Y", 0x59},
    {"Z", 0x5A},
    {"WIN_KEY", 0x5B},
    {"NUMPAD0", 0x60},
    {"NUMPAD1", 0x61},
    {"NUMPAD2", 0x62},
    {"NUMPAD3", 0x63},
    {"NUMPAD4", 0x64},
    {"NUMPAD5", 0x65},
    {"NUMPAD6", 0x66},
    {"NUMPAD7", 0x67},
    {"NUMPAD8", 0x68},
    {"NUMPAD9", 0x69},
    {"NUM_MULT", 0x6A},
    {"NUM_ADD", 0x6B},
    {"NUM_SUBTRACT", 0x6D},
    {"NUM_DECIMAL", 0x6E},
    {"NUM_DIVIDE", 0x6F},
    {"F1", 0x70},
    {"F2", 0x71},
    {"F3", 0x72},
    {"F4", 0x73},
    {"F5", 0x74},
    {"F6", 0x75},
    {"F7", 0x76},
    {"F8", 0x77},
    {"F9", 0x78},
    {"F10", 0x79},
    {"F11", 0x7A},
    {"F12", 0x7B},
    {"NUMLOCK", 0x90},
    {"SCROLLLOCK", 0x91},
    {"LeftSHIFT", 0xA0},
    {"RightSHIFT", 0xA1},
    {"LeftCONTROL", 0xA2},
    {"RightCONTROL", 0xA3},
    {"LeftALT", 0xA4},
    {"RightALT", 0xA5}

};

int getKeyCode(const char *keyName)
{
    int keyMappingLength = sizeof(keyMappings) / sizeof(keyMappings[0]);
    for (int i = 0; i < keyMappingLength; i++)
    {
        if (!strcmp(keyMappings[i].keyName, keyName))
        {
            return keyMappings[i].keyCode;
        }
    }

    return -1;
}