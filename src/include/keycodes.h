#ifndef KEYCODES_H
#define KEYCODES_H

typedef struct KeyMapping
{
    const char *keyName;
    int keyCode;
} KeyMapping_t;

int getKeyCode(const char *keyName);

#endif // KEYCODES_H
