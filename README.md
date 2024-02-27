## Introduction

TinyScriptLang is an interpreted automation scripting language that enables users to execute mouse and keyboard functions with simple syntax for desktop automation. The interpreter is written in C and uses the Windows API to send input. This means that ONLY Windows is supported.

## Usage

In the releases you can find the compiled interpreter, or you can compile it from source. Once you have the interpreter, create a .tsl file and write some commands. Run the interpreter in the command line, and give it your .tsl file as the only argument.

## Compiling

I have included a makefile that I use to build for Windows using mingw. Run `make windows` from the root of the repo. There are presently no external libraries outside of the Windows API.

## Basic Documentation
### *Will be moved into separate file if it grows too large*

**Note**: Shift + F1 Is the current emergency stop key combination. This will be modifiable in the future. It is intended to break you out of any infinite loops you may accidentally create that cause you to lose control of your mouse / keyboard to stop it.

#### `HKEY` 

The `HKEY` method is used to set the hotkey that will be used to execute your script.
*IMPORTANT*: Hotkey MUST be called first, at the top of every .tsl file for it to be valid.

#### Parameters
- `keyCode` (string, int): Accepts both string and integer arguments, valid keycodes can be found at https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes and valid string representations can be found in keycodes.txt

#### `MCLK`

The `MCLK` (mouse click) method is used to execute a mouse click at specified screen coordinates.

#### Parameters
- `x` (integer): The x screen-coordinate where the click will occur.
- `y` (integer): The y screen-coordinate where the click will occur.
- `mouseButton` (optional, string): The mouse button to use for the click. Possible values are `LEFT` or `RIGHT`. Defaults to `LEFT` if not specified.

#### `MMOV`

The `MMOV` (mouse move) method is used to move the mouse to specified screen coordinates. (without clicking)

#### Parameters
- `x` (integer): The x screen-coordinate where the mouse will move to.
- `y` (integer): The y screen-coordinate where the mouse will move to.

#### `KPRS`

The `KPRS` (key press) method is used to execute a keystroke with a given keycode.

#### Parameters
- `keyCode` (string, int): Accepts both string and integer arguments, valid keycodes can be found at https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes and valid string representations can be found in keycodes.txt

#### `PAUS`
Pauses execution for a given amount of time

#### Parameters
- `ms` (int): How many milliseconds to pause execution for.


## TODO
- Add error checking in the interpreter (filetype, read errors, etc.)
- Add error checking for the .tsl file (syntax errors, formatting, etc.)
- ~~Add hotkey support to fire scripts~~ 
- Add toggle as an option to hotkeys for looping the file.
- Add support for basic arithmetic

### Maybes
- Add Loop functionality
- Add Labels / Variables 
