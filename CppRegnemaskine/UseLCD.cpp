// 
// 
// 




#include "UseLCD.h"
#include <string.h>
#include <LiquidCrystal.h>

/*________ LCD pins ________*/
#define LCD_R	52
#define LCD_E	53
#define	LCD_D0	50
#define	LCD_D1	51
#define	LCD_D2	49
#define	LCD_D3	47

#define LCD_ROW_SIZE 0x10

uint8_t curser = 0;	// Position on display
uint8_t lcdCol = 0;	//Column on display
char topRow[LCD_ROW_SIZE+1];
char butRow[LCD_ROW_SIZE+1];

static LiquidCrystal lcd(LCD_R, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3);//Instantiate a LCD object


/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdStart (void)
{
	lcd.begin(16,2);
	lcd.clear();
	//Strings must be initialized with whitespaces!!
	for (int i = 0; i < LCD_ROW_SIZE;i++)
	{
		topRow[i] = ' ';
		butRow[i] = ' ';
	}
	Serial.print((butRow)); //debug
}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdAddCharButRow (uint8_t position, char ch)
{
	if (position > LCD_ROW_SIZE)
	{
		lcd.clear();
		lcd.print("OVERFLOW");
	}
	butRow[position] = ch;
}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdAddStrButRow (uint8_t position, char* str)
{
	uint8_t strLength = strlen(str);
	
	if (position > LCD_ROW_SIZE || position+strLength > LCD_ROW_SIZE)
	{
		lcd.clear();
		lcd.print("OVERFLOW");
	}
	else
	{
		for (int i=0; i < strLength; i++)
		{
			butRow[position+i]=str[i];
		}
	}

}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdButRowFlush (void)
{
	for(int i=0; i < LCD_ROW_SIZE ;i++)
	{
		butRow[i] = 0;
	}
}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdAddCharTopRow (uint8_t position, char ch)
{
	if (position > LCD_ROW_SIZE)
	{
		lcd.clear();
		lcd.print("OVERFLOW");
	}
	topRow[position] = ch;
}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdAddStrTopRow (uint8_t position, char* str)
{
	uint8_t strLength = strlen(str);
	
	if (position > LCD_ROW_SIZE || position+strLength > LCD_ROW_SIZE)
	{
		lcd.clear();
		lcd.print("OVERFLOW");
	}
	else 
	{
		for (int i=0; i < strLength; i++)
		{
			topRow[position+i]=str[i];
		}
	}
}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdTopRowFlush (void)
{
	for(int i=0; i < LCD_ROW_SIZE ;i++)
	{
		topRow[i] = 0;
	}
}

/*==============================================================================
 | Function Name: 
 |   Description: 
 |         Input: -
 |        Return: -
 *=============================================================================*/
extern void lcdRun (void)
{
	//Serial.println((butRow)); //debug
	//Serial.println((topRow)); //debug
	
	lcd.setCursor(0,0);
	lcd.print(topRow);
	lcd.setCursor(0,1);
	lcd.print(butRow);
}
