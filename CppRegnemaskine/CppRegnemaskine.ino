#include "RegneLogik.h"
#include "LiquidCrystal.h"
#include "UseLCD.h"
#include "keypad4x4.h"

#define NUMBER_SIZE 15

#include <LiquidCrystal.h>

/*________ LCD pins ________*/
#define LCD_R	52
#define LCD_E	53
#define	LCD_D0	50
#define	LCD_D1	51
#define	LCD_D2	49
#define	LCD_D3	47

static LiquidCrystal lcd(LCD_R, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3);//Instantiate a LCD object

Keypad4x4 pad(/*col*/22,24,26,28,/*row*/29,27,25,23);//Set keypad pins
char firstNumber[NUMBER_SIZE+1];
char secondNumber[NUMBER_SIZE+1];
char result[100];
char op = 0;


void setup()
{
    Serial.begin(9600);
    lcdStart();
    for (int i=0;i < NUMBER_SIZE;i++)//Init strings for Arduino functions
    {
        firstNumber[i] = ' ';
        secondNumber[i] = ' ';
        result[i] = ' ';
    }
}

void getInput (void)
{
    char input = pad.readKeyASCII();
    
    
}

void startScreen (void)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Skriv et tal");
}

void showOpereator (char op)
{
    lcd.setCursor(0,16);
    switch (op)
    {
        case 'F':
        lcd.print('+');
        break;
        case 'E':
        lcd.print('-');
        break;
        case 'D':
        lcd.print('*');
        break;
        case 'C':
        lcd.print('/');
        break;
    }
}


void getFistNumber (char firstInput)
{
    uint8_t index = 1;
    char input = firstInput;
    
    if (input <= '9' && input > 0)//Only numbers
    {
        firstNumber[0]=input;
        lcd.clear();
        lcd.print(firstNumber);
        while (index <= NUMBER_SIZE)
        {
            input = pad.readKeyASCII();
            if (input <= '9' && input > 0)
            {
                firstNumber[index++]=input;
                Serial.print(strlen(firstNumber));
                lcd.clear();
                lcd.print(firstNumber);
            }
            else
            {
                op = input;
                break;
            }
        }
        
        index = 0;
        showOpereator(op);
        input = pad.readKeyASCII();
        
        if (input <= '9' && input > 0)//Only numbers
        {
            firstNumber[0]=input;
            lcd.clear();
            lcd.print(firstNumber);
            while (index <= NUMBER_SIZE)
            {
                input = pad.readKeyASCII();
                if (input <= '9' && input > 0)
                {
                    firstNumber[index++]=input;
                    Serial.print(strlen(firstNumber));
                    lcd.clear();
                    lcd.print(firstNumber);
                }
                else
                {
                    op = input;
                    break;
                }
            }
        }
    }

}


//
    void loop()
    {
        startScreen();
        getFistNumber(pad.readKeyASCII());
        Serial.print("back");
    }

    void loop()
    {
        startScreen();
        getFistNumber(pad.readKeyASCII());
        Serial.print("back");
    }
        void loop()
        {
            startScreen();
            getFistNumber(pad.readKeyASCII());
            Serial.print("back");
        }
            void loop()
            {
                startScreen();
                getFistNumber(pad.readKeyASCII());
                Serial.print("back");
            }
                void loop()
                {
                    startScreen();
                    getFistNumber(pad.readKeyASCII());
                    Serial.print("back");
                }
                    void loop()
                    {
                        startScreen();
                        getFistNumber(pad.readKeyASCII());
                        Serial.print("back");
                    }
                    