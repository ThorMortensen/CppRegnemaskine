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

#include "keypad4x4.h"                       // Header with class definition

// Constructor
Keypad4x4::Keypad4x4(int8_t col0, int8_t col1, int8_t col2, int8_t col3, 
                     int8_t row0, int8_t row1, int8_t row2, int8_t row3) 
{
    // Save pin numbers
    rowpins[0] = row0;  rowpins[1] = row1;  rowpins[2] = row2;  rowpins[3] = row3;
    colpins[0] = col0;  colpins[1] = col1;  colpins[2] = col2;  colpins[3] = col3;
    int i;                                   // Loop counter
    for (i = 0; i < 4; i++) 
    {    
        pinMode(rowpins[i], INPUT);          // Set row pins as input to avoid short circuit
        pinMode(colpins[i], INPUT_PULLUP);   // Use internal pullup resistors on column pins
    }
}

// Ask if a key is pressed. Returns the hexadecimal value if the key is pressed, -1 if no key pressed
int8_t Keypad4x4::pollKeyHex() 
{
    int row, column;                         // Row and column number

    // Table of key values
    static const int8_t keyValues[4][4] = 
    {
        {0x1, 0x2, 0x3, 0xF},
        {0x4, 0x5, 0x6, 0xE},
        {0x7, 0x8, 0x9, 0xD},
        {0xA, 0x0, 0xB, 0xC}
    };

    // Check if a key is pressed
    if (!isKeyPressed()) return -1;          // Return -1 if no key pressed

    // A key is pressed. Search for the key  
    // Deactivate all rows
    for (row = 0; row < 4; row++) 
    {
        pinMode(rowpins[row], INPUT);
    }

    // Scan rows, one by one
    for (row = 0; row < 4; row++) 
    {
        // Set current row low
        pinMode(rowpins[row], OUTPUT);
        digitalWrite(rowpins[row], LOW);
        // Give the pullup resistors time to work
        delayMicroseconds(hwPropagDelay_us);
        // Check if any column is low
        for (column = 0; column < 4; column++) 
        {
            if (digitalRead(colpins[column]) == LOW) 
            {
                // Key found
                // Wait to check for bounce noise
                delay (debounceDelay_ms);
                // Check if the key is still pressed
                if (digitalRead(colpins[column]) == LOW) 
                {
                    // Key accepted. Return value
                    return keyValues[row][column];
                }
            }
        }
        // Deactivate this row before going to the next row
        pinMode(rowpins[row], INPUT);
    }
    // Row scan finished without success. Apparently, this was only keybounce noise
    return -1;
}

// Ask if a key is pressed. Returns the ASCII value if the key is pressed, 0 if no key pressed
char Keypad4x4::pollKeyASCII()
{
    // Read key as hexadecimal
	int8_t hex = pollKeyHex();
	// Return 0 if not pressed
	if (hex == -1) return 0;
    // Convert to ASCII
    if (hex > 9) return hex + 'A' - 10;
    return hex + '0';
}

// Wait for a key to be pressed and return the hexadecimal key value as 4 bits
int8_t Keypad4x4::readKeyHex() 
{
    // Key number
    int8_t key;

    // Wait for previous key to be released
    while (isKeyPressed()) {}

    // Wait for noise to disappear (noise period when key released is shorter than when pressed)
    delay (debounceDelay_ms / 2);

    // Wait indefinitely for a valid key
    while (true) 
    {
        // Wait for new key to be pressed
        while (!isKeyPressed()) {}
        // Get key
        key = pollKeyHex();
        // Return key number if valid
        if (key >= 0) return key;
        // This was only noise, keep waiting in loop
    }
    // We will never get here
    return 0;
}

// Wait for a key to be pressed and return the ASCII key value
char Keypad4x4::readKeyASCII() 
{
    // Read key as hexadecimal
    int8_t hex = readKeyHex();
    // Convert to ASCII
    if (hex > 9) return hex + 'A' - 10;
    return hex + '0';
}

// Return true if any key is pressed
bool Keypad4x4::isKeyPressed() 
{
    int i;                                   // Loop counter
    for (i = 0; i < 4; i++) 
    {    
        pinMode(rowpins[i], OUTPUT);         // Set all rows low
        digitalWrite(rowpins[i], LOW);
    }
    delayMicroseconds(hwPropagDelay_us);     // Give the pullup resistors time to work
    for (i = 0; i < 4; i++) 
    {
        // Return true if any column input is low
        if (digitalRead(colpins[i]) == LOW) return true;
    }
    return false;
}
