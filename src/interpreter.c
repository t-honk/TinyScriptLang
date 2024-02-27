#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include "keycodes.h"
#include "interpactions.h"

#define USER_HOTKEY 1
#define EXIT_HOTKEY 2
#define OPCODE_LENGTH sizeof(int)
#define OP_HKEY *((int *)"HKEY")

typedef void (*OpcodeFp)(int[]);

typedef struct
{
    OpcodeFp fp;
    int data[5];
    int dataLen;
} Instruction_t;

static const long hextable[] = {
    [0 ... 255] = -1,
    ['0'] = 0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    ['A'] = 10,
    11,
    12,
    13,
    14,
    15,
    ['a'] = 10,
    11,
    12,
    13,
    14,
    15,
};

/**
 * @brief convert a hexidecimal string to a signed long
 * will not produce or process negative numbers except
 * to signal error.
 *
 * @param hex without decoration, case insensitive.
 *
 * @return -1 on error, or result (max (sizeof(long)*8)-1 bits)
 */
long hexdec(unsigned const char *hex)
{
    long ret = 0;
    while (*hex && ret >= 0)
    {
        ret = (ret << 4) | hextable[*hex++];
    }
    return ret;
}

int main(int argc, char *argv[])
{
    // Tokenize
    FILE *fptr = fopen(argv[1], "r");
    char lineBuffer[256] = {0};
    Instruction_t instructions[32] = {0};
    int instructionCounter = 0;
    int lineCounter = 0;
    int hotKeyCode = 0;
    while (fgets(lineBuffer, sizeof(lineBuffer), fptr))
    {
        int opcode = *((int *)lineBuffer);
        int linePos = OPCODE_LENGTH + 1;
        char argBuffer[64] = {0};
        int argLength = 0;
        int dataCounter = 0;
        Instruction_t instruction;

        // Special Case to handle first line (hotkey setup)

        if (lineCounter == 0 && opcode != *((int *)"HKEY"))
        {
            printf("TSLError: No Hotkey Specified.\n");
            return -1;
        }
        else if (lineCounter == 0 && opcode == *((int *)"HKEY"))
        {
            while (lineBuffer[linePos] != ')')
            {
                if (lineBuffer[linePos] == '0' && (lineBuffer[linePos + 1] == 'x' || lineBuffer[linePos + 1] == 'X'))
                {
                    linePos += 2;
                    continue;
                }
                if (lineBuffer[linePos] != ',' && lineBuffer[linePos] != ' ')
                {
                    argBuffer[argLength] = lineBuffer[linePos];
                    argLength++;
                }
                linePos++;
            }
            int testCode = getKeyCode(argBuffer);
            if (testCode)
            {
                hotKeyCode = testCode;
            }
            else
            {
                hotKeyCode = hexdec(argBuffer);
            }
            lineCounter++;
        }

        if (opcode == *((int *)"MMOV"))
        {
            instruction.fp = hover;
        }
        else if (opcode == *((int *)"MCLK"))
        {
            instruction.fp = click;
        }
        else if (opcode == *((int *)"PAUS"))
        {
            instruction.fp = sleep;
        }
        else if (opcode == *((int *)"KPRS"))
        {
            instruction.fp = key;
        }
        else
        {
            continue;
        }
        while (lineBuffer[linePos] != ')')
        {
            int hexFound = 0;
            if (lineBuffer[linePos] == '0' && (lineBuffer[linePos + 1] == 'x' || lineBuffer[linePos + 1] == 'X'))
            {
                hexFound = 1;
                linePos += 2;
                continue;
            }
            if (lineBuffer[linePos] != ',' && lineBuffer[linePos] != ' ')
            {
                argBuffer[argLength] = lineBuffer[linePos];
                argLength++;
            }
            if (lineBuffer[linePos + 1] == ',' || lineBuffer[linePos + 1] == ')')
            {
                printf("current argBuffer: %s\n", argBuffer);
                int testKeyCode = getKeyCode(argBuffer);
                int testHexDec = hexdec(argBuffer);
                int testAtoi = atoi(argBuffer);
                int testStrcmp = strcmp(argBuffer, "RIGHT");
                if (testKeyCode)
                {
                    instruction.data[dataCounter] = testKeyCode;
                    dataCounter++;
                }
                else if (testAtoi)
                {
                    instruction.data[dataCounter] = testAtoi;
                    dataCounter++;
                }
                else if (!testAtoi && argBuffer[0] == 48)
                {
                    instruction.data[dataCounter] = testAtoi;
                    dataCounter++;
                }
                else if (hexFound && testHexDec != -1)
                {
                    instruction.data[dataCounter] = testHexDec;
                    dataCounter++;
                }
                else if (!testStrcmp)
                {
                    instruction.data[dataCounter] = (!testStrcmp) ? 1 : 0;
                    dataCounter++;
                }

                argLength = 0;
            }
            linePos++;
        }
        printf("added instruction with dataLen: %d\n", dataCounter);
        instruction.dataLen = dataCounter;
        instructions[instructionCounter] = instruction;
        instructionCounter++;
        lineCounter++;
    }
    fclose(fptr);

    for (int i = 0; i < instructionCounter; i++)
    {
        printf("instruction %d with dataLen %d\n", i, instructions[i].dataLen);
        for (int x = 0; x < instructions[i].dataLen; x++)
        {
            printf("%d\n", instructions[i].data[x]);
        }
    }

    if (RegisterHotKey(NULL, USER_HOTKEY, 0, hotKeyCode) && RegisterHotKey(NULL, EXIT_HOTKEY, MOD_SHIFT, VK_F1))
    {
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            if (msg.message == WM_HOTKEY)
            {
                if (msg.wParam == 1)
                {
                    for (int i = 0; i < instructionCounter; i++)
                    {
                        instructions[i].fp(instructions[i].data);
                    }
                }
                else if (msg.wParam == 2)
                {
                    UnregisterHotKey(NULL, USER_HOTKEY);
                    UnregisterHotKey(NULL, EXIT_HOTKEY);
                    return 0;
                }
            }
        }
    }

    UnregisterHotKey(NULL, USER_HOTKEY);
    UnregisterHotKey(NULL, EXIT_HOTKEY);
    return 0;
}
