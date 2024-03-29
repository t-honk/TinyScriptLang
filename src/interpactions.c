#include "interpactions.h"
#include <windows.h>
#include <winuser.h>

void sleep(int *data)
{
    Sleep(data[0]);
}

void click(int *data)
{
    int mouseButton = data[2];

    int winMouseDown = (mouseButton == 0) ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN;
    int winMouseUp = (mouseButton == 0) ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP;

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.mouseData = 0;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;

    input.mi.dwFlags = winMouseDown;
    hover(data);
    SendInput(1, &input, sizeof(input));

    input.mi.dwFlags = winMouseUp;
    SendInput(1, &input, sizeof(input));
}

void hover(int *data)
{
    int x = data[0];
    int y = data[1];
    SetCursorPos(x, y);
}

void key(int *data)
{
    int keyCode = data[0];

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = keyCode;
    input.ki.dwFlags = 0;

    SendInput(1, &input, sizeof(input));
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(input));
}
