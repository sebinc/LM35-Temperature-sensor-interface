#include "includes.h"
#include<pic.h>
void lcd_init(void)
{
	E=0;
	__delay_us(15);//check by reducing the delay
	//-----------initialise lcd in 4 bit-----------
	lcd_write_command(0x03);
	lcd_write_command(0x03);
	lcd_write_command(0x03);
	lcd_write_command(0x02);
	lcd_write_command(0x28);
	//-----------------------------------------
	lcd_write_command(0x0C);	//lcd on cursor off;
	lcd_write_command(0x06);	//cursor increment
	return;
}
void lcd_write_command(unsigned char command)
{
	
	unsigned char temp_data;
	E=0;
	temp=command;
	__delay_us(1);
	RS=0;
	RW=0;
	__delay_us(1);
	E=1;
	__delay_us(1);
	temp&=0xF0;			//to take msb of command
	/*--------value in PORTD lower nibble remains the same--------
	upper nibble = upper nibble of command---------*/
	temp_data = PORTD;		
	temp_data& = 0x0F;
	PORTD=temp_data|temp;
	__delay_us(1);
	E=0;
	__delay_us(1);
	/*--------value in PORTD lower nibble remains the same--------
	upper nibble = lower nibble of command---------*/
	temp=command;
	__delay_us(1);
	E=1;
	__delay_us(1);
	temp<<=4;
	temp&=0xF0;
	PORTD&=0x0F;
	PORTD|=temp;
	__delay_us(1);
	E=0;
	__delay_us(2);
	return;

}
void lcd_write_byte(unsigned char byte)
{

	E=0;
	temp=byte;
	__delay_us(1);
	RS=1;
	RW=0;
	__delay_us(1);
	E=1;
	__delay_us(1);
	temp&=0xF0;
	PORTD & =0x0F;
	PORTD|=temp;
	__delay_us(1);
	E=0;
	__delay_us(1);

	temp=byte;
	__delay_us(1);
	E=1;
	__delay_us(1);
	temp<<=4;
	temp&=0xF0;
	PORTD &=0x0F;
	PORTD|=temp;
	__delay_us(1);
	E=0;
	__delay_us(2);
	return;

}
void lcd_write_word(char word[])
{
	int i = 0;
	
	while(word[i]!= '\0')
	{
		lcd_write_byte(word[i]);
		i++;
	}	
	return;
}		