#include "lcd.h"
#include "system_init.h"

void LCD_init(void)
{                      
    Delay(100);
    bl_state = BL_ON;
    data_value = 0x04;
    PCF8574_write(data_value);
    Delay(10);
    LCD_send(0x33, COMMAND);
    LCD_send(0x32, COMMAND);
    LCD_send((_4_pin_interface | _2_row_display | _5x7_dots), COMMAND);        
    LCD_send((display_on | cursor_off | blink_off), COMMAND);    
    LCD_send((clear_display), COMMAND);        
    LCD_send((cursor_direction_inc | display_no_shift), COMMAND);       
}  
void LCD_toggle_EN(void)
{
    data_value |= 0x04;
    PCF8574_write(data_value);
    Delay(dly);
    data_value &= 0xF9;
    PCF8574_write(data_value);
    Delay(dly);
}
void LCD_send(unsigned char value, unsigned char mode)
{
    switch(mode)
    {
       case COMMAND:
       {
            data_value &= 0xF4;
            break;
       }
       case DATA:
       {
           data_value |= 0x01;
           break;
       }
    }
    switch(bl_state)
    {
       case BL_ON:
       {
          data_value |= 0x08;
          break;
       }
       case BL_OFF:
       {
          data_value &= 0xF7;
          break;
       }
    }
    PCF8574_write(data_value);
    LCD_4bit_send(value);
    Delay(dly);
}
void LCD_4bit_send(unsigned char lcd_data)      
{
    unsigned char temp = 0x00;
    temp = (lcd_data & 0xF0);
    data_value &= 0x0F;
    data_value |= temp;
    PCF8574_write(data_value);
    LCD_toggle_EN();
    temp = (lcd_data & 0x0F);
    temp <<= 0x04;
    data_value &= 0x0F;
    data_value |= temp;
    PCF8574_write(data_value);
    LCD_toggle_EN();
} 
void LCD_putstr(const char *lcd_string)
{
    do
    {
        LCD_putchar(*lcd_string++);
    }while(*lcd_string != '\0') ;
}
void LCD_putchar(char char_data)
{
    if((char_data >= 0x20) && (char_data <= 0x7F))
    {
       LCD_send(char_data, DATA);
    }
}
void LCD_clear_home(void)
{
    LCD_send(clear_display, COMMAND);
    LCD_send(goto_home, COMMAND);
}
void LCD_goto(unsigned char x_pos,unsigned char y_pos)
{                                                   
    if(y_pos == 0)   
    {                             
        LCD_send((0x80 | x_pos), COMMAND);
    }
    else
    {                                             
        LCD_send((0x80 | 0x40 | x_pos), COMMAND);
    }
}
