//======================================================
//LCD prototype
//======================================================

//Type definitions
typedef signed char int8;
typedef signed int  int16;
typedef signed long int32;
typedef unsigned short uint16;
typedef unsigned char uint8;

//Display Config
#define MAX_DISPLAY_CHAR 15

//LCD Registers addresses (PORT B)
#define LCD_CMD_WR	   0x00
#define LCD_DATA_WR	   0x01
#define LCD_BUSY_RD	   0x02
#define LCD_DATA_RD	   0x03

//LCD Commands
#define LCD_CLS		       0x01
#define LCD_HOME	       0x02
#define LCD_SETMODE	       0x04
#define LCD_SETVISIBLE	   0x08
#define LCD_SHIFT	   	   0x10
#define LCD_SETFUNCTION	   0x20
#define LCD_SETDDADDR	   0x80

#define E_PIN_MASK         0x04

#define FALSE 0
#define TRUE  1

//Error handling status.
enum ERROR     { OK = 0, SLEEP = 1, ERROR = 2};

//Function prototypes
void lcd_init();
void lcd_wait();
void clearscreen();
void wrcmd(char data);
void wrdata(char data);
void wrstring(char *str);
