//These driver routines implement the functionality necessary to drive
//a HD44780 controlled Alphameric LCD in 4-bit mode.
//PORT C pins 4-7 are used for data transmission and PORT B pins 0-2 are used 
//for command control.

#include "lcd4bit.h"
#include "pic.h"

//Initialise the LCD Display.
void lcd_init()
{ 
   TRISC = PORTC = 0xFF;
   wrcmd(LCD_SETFUNCTION);                    //4-bit mode - 1 line - 5x7 font. 
   wrcmd(LCD_SETVISIBLE+0x04);                //Display no cursor - no blink.
   wrcmd(LCD_SETMODE+0x02);                   //Automatic Increment - No Display shift.
   wrcmd(LCD_SETDDADDR);                      //Address DDRAM with 0 offset 80h.
}

//Clear the LCD Screen and reset
//initial position.
void clearscreen()
{ 
   wrcmd(LCD_CLS);
   wrcmd(LCD_SETDDADDR+0x00);
}

//Write a command to the LCD display.
//In 4-bit mode we send the MSN first and then
//the LSN. We then call the wait routine to hold
//until the busy flag is cleared.
void wrcmd(char cmdcode)
{ 
   TRISC = 0;
   PORTC = (cmdcode & 0xF0);                  //Get the most significant nibble first.
   PORTB = TRISB = 0; 
   PORTB  = LCD_CMD_WR;                       //Specify a command write operation.
   PORTB |= E_PIN_MASK;                       //Toggle the 'E' pin to send the command.
   asm("NOP");
   PORTB &= ~E_PIN_MASK;
 
   TRISC = 0;
   PORTC = (cmdcode << 4);                     //Repeat for least significant nibble.
   PORTB  = LCD_CMD_WR;
   PORTB |= E_PIN_MASK;
   asm("NOP");
   PORTB &= ~E_PIN_MASK;
  
   lcd_wait();                                 //Call the wait routine.
}

//Write a character to the LCD Display. 
//In 4-bit mode we send the MSN first and then
//the LSN. We then call the wait routine to hold
//until the busy flag is cleared.
void wrdata(char data)
{ 
   TRISC = 0;
   PORTC = data & 0xF0;                         //Get the most significant nibble first. 
   PORTB = LCD_DATA_WR;                         //Specify a data write operation.
   PORTB |= E_PIN_MASK;                         //Toggle the 'E' pin to send the command.
   asm("NOP");
   PORTB &= ~E_PIN_MASK;
   
   TRISC = 0;
   PORTC = (data << 4);                         //Repeat for least significant nibble.
   PORTB = LCD_DATA_WR;
   PORTB |= E_PIN_MASK;
   asm("NOP");
   PORTB &= ~E_PIN_MASK;
  
   lcd_wait();                                  //Call the wait routine.
}

//Write a string to the LCD Display.
//Using the previous function.
void wrstring(char *str)
{
	char *ptr = str;

	while (*ptr != '\0' && *ptr != '\n')
	{
		wrdata(*(ptr++));
	}
}

//Wait for the LCD busy flag to clear. 
//Crucially in 4-bit mode we must perform 2 read operations
//to retrieve both the high and the low nibble of the return
//uint8. We then amalgamate the two nibbles and test the busy flag.
void lcd_wait()
{ 
   uint8 lownibble = 0, highnibble = 0, status = 0;
   do
    { TRISC = 0xFF;                 
      PORTB = LCD_BUSY_RD;              
      PORTB |= E_PIN_MASK;
      asm("NOP");
      highnibble = PORTC & 0xF0;                //read the high nibble.
      PORTB &= ~E_PIN_MASK;

      PORTB = TRISB = 0;                        //reset.
      TRISC = 0xFF; 
      PORTB = LCD_BUSY_RD;          
      PORTB |= E_PIN_MASK;
      asm("NOP");
      lownibble = (PORTC & 0xF0) >> 4;          //read the low nibble. 
      PORTB &= ~E_PIN_MASK;
      status = highnibble + lownibble;          //combine to form busy status and ddaddress.
    } while (status & 0x80);                    //test busy flag.
}
