/*==============================================================================
|  Assignment:  Bugler Alarm
|      Author:  Thor Mortensen
|    Language:  Arduino C
|    Compiler:  AVR-Studio 6 AVR-GCC
|      Course:  62505 Introduktion til indlejrede systemer
|     Teacher:  Kurt Jeritslev
|    Due Date:  Week 38
+-------------------------------------------------------------------------------
|       Class: BuglerAlarmMain
| Description: Handle simple scheduler to run the tasks at predefined intervals
|
|   Functions: void setup()
|				extern void burnPromPass (char *promPass)
|				extern void loadPromPass (void)
|              void scheduler (void)
|				void loop()
+-------------------------------------------------------------------------------
|		  MEMO: C strings must be initialized with char's before manipulation
|				to move terminator 0 to end of string. Else Arduino's string
|				functions will misbehave!!!!
*=============================================================================*/
#include "LiquidCrystal.h"
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
    lcd.begin(16,2);
    claerNumbers();
}

void startScreen (void)
{
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Skriv et tal");
}

void claerNumbers (void)
{
    for (int i=0;i < NUMBER_SIZE;i++)//Init strings for Arduino functions
    {
        firstNumber[i] = ' ';
        secondNumber[i] = ' ';
        result[i] = ' ';
    }
    
}

void showOpereator (char op)
{
    lcd.setCursor(15,0);
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


void calc(char input)
{
    int32_t nr1,nr2; //long
    
    nr1 = atoi(firstNumber);//Convert string to nr
    nr2 = atoi(secondNumber);
    
    switch (op)
    {
        case 'F':
        sprintf(result,"%ld",nr1+nr2);
        break;
        case 'E':
        sprintf(result,"%ld",nr1-nr2);
        break;
        case 'D':
        sprintf(result,"%ld",nr1*nr2);
        break;
        case 'C':
        sprintf(result,"%ld",nr1/nr2);
        break;
    }
    lcd.clear();
    lcd.print(result);
}

void getFistNumber (char firstInput)
{
    uint8_t index = 1;
    char input = firstInput;
    
    if (input <= '9' && input > 0)//Only numbers
    {
        claerNumbers();
        firstNumber[0]=input;
        lcd.clear();
        lcd.print(firstNumber);
        while (index <= NUMBER_SIZE)
        {
            input = pad.readKeyASCII();
            if (input <= '9' && input > 0)
            {
                firstNumber[index++]=input;
                Serial.println("n1:");
                Serial.println((firstNumber));
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
            secondNumber[index++]=input;
            lcd.setCursor(0,1);
            lcd.println(secondNumber);
            Serial.println("2n:");
            Serial.println((secondNumber));
            while (index <= NUMBER_SIZE)
            {
                Serial.println("here");
                input = pad.readKeyASCII();
                if (input <= '9' && input > 0)
                {
                    secondNumber[index++]=input;
                    Serial.println("222n:");
                    Serial.println((secondNumber));
                    lcd.setCursor(0,1);
                    lcd.print(secondNumber);
                }
                else if (input == 'A')
                {
                    calc(input);
                    break;
                }
            }
        }
    }

}


void loop()
{
    
    startScreen();
    while (1)
    {
        getFistNumber(pad.readKeyASCII());
    }
}

