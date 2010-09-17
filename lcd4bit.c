//Main program

#include "pic.h"
#include "lcd4bit.h"

#define _XTAL_FREQ 1000000  //processor frequency

//LCD functions
/*
void lcd_init();
void lcd_wait();
void clearscreen();
void wrcmd (char data);
void wrdata(char data);
void wrstring(char *str);
*/

// Program Control Function.
void main(void)
{
   lcd_init();   // Initialise the LCD Display

   for (;;)
   {
   }
}
