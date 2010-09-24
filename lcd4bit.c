//Main program

#include "pic.h"
#include "lcd4bit.h"

#define _XTAL_FREQ 4000000  //processor frequency

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
    lcd_init(); //initialize lcd display

    TRISA = 0xFF; //set TRISA register as inputs
    ADCON1 = 0x80; //ADFM=1, all inputs analogue, VREF(+) = VDD
    ADCON0 = 0xC1; //clock, channel and enable

    for (;;)
    {
    }
}
