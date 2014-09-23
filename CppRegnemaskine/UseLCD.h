// UseLCD.h

#ifndef _USELCD_h
#define _USELCD_h
#include <LiquidCrystal/LiquidCrystal.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


extern void lcdStart (void);
//void lcdPrintChar (char ch);
//void useLcd (uint8_t useItem, String str);
//extern LiquidCrystal* getLcd (void);
//void lcdPrintCppString (String str);
//void lcdShowWach (String watchString);
//void lcdPlacePrintStr (uint8_t x, uint8_t y,String str);

extern void lcdRun (void);
extern void lcdTopRowFlush (void);
extern void lcdAddStrTopRow (uint8_t position, char* str);
extern void lcdAddCharTopRow (uint8_t position, char ch);
extern void lcdButRowFlush (void);
extern void lcdAddStrButRow (uint8_t position, char* str);
extern void lcdAddCharButRow (uint8_t position, char ch);



#endif

