/* 
Arduino library for a 4x4 matrix keypad with keys 0-9 and A-F
Author:  Agner Fog
Date:    2014-08-17
License: LGPL

Description:
This library makes it possible to read from a 4x4 matrix keyboard 
connected directly to an Arduino without any other external components.
The functions will scan the rows one by one by setting one row low
and setting the other rows as input to avoid short circuit in case
two buttons are pushed at the same time in different rows. 
Negative logic is used in order to use the internal pull-up resistors 
instead of external pull-down resistors.

The functions readKeyHex() and readKeyASCII() will wait for any
previous key to be released and then wait for a key to be pressed.

The functions pollKeyHex() and pollKeyASCII() do not wait for any
key to be pressed. They tell whether a key is pressed or not and 
return the key value if a key is pressed.

readKeyHex() and pollKeyHex() return the hexadecimal key value 0x0 - 0xF.

readKeyASCII() and pollKeyASCII() return the ASCII character '0' - '9' or 'A' - 'F'.

If no key is pressed, pollKeyHex() returns -1 and pollKeyASCII() returns 0.

Function                          | when key pressed  | when no key pressed |
----------------------------------+-------------------+---------------------+
readKeyHex()                      | hexadecimal value |   wait              |
readKeyASCII()                    | ASCII value       |   wait              |
pollKeyHex()                      | hexadecimal value |   -1                |
pollKeyASCII()                    | ASCII value       |    0                |
----------------------------------+-------------------+---------------------+

*/

#include <Arduino.h>
#include <inttypes.h>           // Make sure int8_t is defined

// Class for reading from 8x8 matrix keypad
class Keypad4x4 {
public:
    // Constructor. Parameters are pin numbers for columns and rows
    Keypad4x4(int8_t col0, int8_t col1, int8_t col2, int8_t col3, 
              int8_t row0, int8_t row1, int8_t row2, int8_t row3);
    // Wait for a key to be pressed, and return the value as hexadecimal
    int8_t readKeyHex();
    // Wait for a key to be pressed, and return the value as ASCII
    char   readKeyASCII();
    // Ask if a key is pressed. Returns the hexadecimal value if a key is pressed, -1 if no key
    int8_t pollKeyHex();
    char   pollKeyASCII();
protected:
    // Check if a key is pressed
    bool isKeyPressed();
    // Pin numbers
    int8_t rowpins[4];  
    int8_t colpins[4];
    // Define timing constants
    enum Constants {
        hwPropagDelay_us = 20,  // Propagation delay in hardware and time for pull-up resistors to work, microseconds
        debounceDelay_ms = 30   // Delay for removing key-bounce noise, milliseconds
    };
};
