//Main program

#include <stdio.h>
#include "pic.h"
#include "lcd4bit.h"

#define _XTAL_FREQ 4000000  //processor frequency
#define MAX_COUNTER 10

uint8 counter;

void display_data(void)
{
    char buf[3];
    wrcmd(0x8A); //Set DDRAM address to 10

    sprintf(buf, "%.2X", ADRESH);
    wrstring(buf);
    sprintf(buf, "%.2X", ADRESL);
    wrstring(buf);
}

void main(void)
{
    counter = 0;

    lcd_init(); //initialize lcd display
    wrstring("  ADC = 0x0000");

    /* ADC */
    TRISA = 0xFF; //set TRISA register as inputs
    ADCON1 = 0x80; //ADFM=1, all inputs analogue, VREF(+) = VDD
    ADCON0 = 0xC1; //clock, channel and enable

    __delay_ms(1);

    /* TIMER0 + interrupt */
    OPTION = 0x05; //TIMER0, prescaler on, internal clocking, divide by 64
    T0IE = 1; //enable TIMER0 overflow interrupt
    PEIE = 1; //enable peripheral interrupt
    ei(); //enable global interrupts

    for (;;)
    {
    }
}

void interrupt the_timer(void)
{
    if (T0IE && T0IF)
    {
        T0IF = 0;
        counter++;

        if (counter == MAX_COUNTER / 2)
            GODONE = 1; //start AD conversion

        if (counter == MAX_COUNTER)
        {
            counter = 0;
            if (GODONE == 0) //if AD conversion is done
                display_data();
        }
        return;
    }
}
