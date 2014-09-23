// RegneLogik.h

#ifndef _REGNELOGIK_h
#define _REGNELOGIK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class RegneLogik
{
 protected:


 public:
	void init();
};

extern RegneLogik RegneLogik;

#endif

