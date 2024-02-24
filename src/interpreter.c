#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "keycodes.h"
#include "scriptactions.h"

int main(int argc, char *argv[])
{
    // Tokenize
    FILE *fptr = fopen(argv[1], "r");

    char lineBuffer[256];
    char tokenBuffer[64][64];
    int tokenCounter = 0;
    while (fgets(lineBuffer, sizeof(lineBuffer), fptr))
    {
        char *token = strtok(lineBuffer, " (,)\n");

        while (token != NULL)
        {
            strcpy(tokenBuffer[tokenCounter], token);
            tokenCounter++;
            token = strtok(NULL, " (,)\n");
        }
    }

    // Interpret
    for (int i = 0; i < tokenCounter; i++)
    {
        char *opcode = tokenBuffer[i];
        if (!strcmp(opcode, "sleep"))
        {
            int ms = atoi(tokenBuffer[i + 1]);
            sleep(ms);
        }
        else if (!strcmp(opcode, "key"))
        {
            int keyCode = getKeyCode(tokenBuffer[i + 1]);
            key(keyCode);
        }
        else if (!strcmp(opcode, "hover"))
        {
            int x = atoi(tokenBuffer[i + 1]);
            int y = atoi(tokenBuffer[i + 2]);
            hover(x, y);
        }
        else if (!strcmp(opcode, "click"))
        {
            int x = atoi(tokenBuffer[i + 1]);
            int y = atoi(tokenBuffer[i + 2]);
            if (!strcmp(tokenBuffer[i + 3], "RIGHT"))
            {
                click(x, y, 1);
            }
            else
            {
                click(x, y, 0);
            }
        }
    }

    return 0;
}
