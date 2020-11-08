#include<pic.h>
#include "includes.h"
__CONFIG(HS&WDTDIS&BORDIS&LVPDIS);
void main()
{
	double pre;						//to accomodate 10 bit adc result
	unsigned long int result;
	unsigned long int ones,tens,hundreds;	//ones,tens and hundreds position
	TRISB=0X00;	//PORTB output
	TRISD=0x00;	//PORTD as output to connect lcd
	//----------- ADC Initialisation-------------
	//right justified; Tad = Tosc/32,channel set as RA0, VDD as Vref+ and VSS as Vref-
	ADCON0 = 0X81; 
	ADCON1 = 0X80;
	TRISA = 0XFF;
	/*-----------------------------------------*/

	
	lcd_init();   //Initialises lcd module as 16x2 cursor off
	
	__delay_ms(1);
	lcd_write_word("  THERMOMETER");
	__delay_ms(10);  	// to give time for ADC setup
	
	while(1)			//body of the progam
	{
		GODONE = 1;		//to start ADC conversion 
		__delay_ms(1);
		while(GODONE == 1);  //wait for conversion to finish 
		//----------caliberation---------------------//	
		pre = ADRESH * 0x100; //Dont read ADRESH and ADRESL in same line
		__delay_ms(1);
		pre = result + ADRESL;
		__delay_ms(1);
		pre = pre*(500/1024.0); 
		result = (int)pre;
		//----------hex to ascii conversion -----------//
		ones = (result % 10)+0x30; 
		result = result/10;
		tens = (result%10+0x30);
		result = result/10;
		hundreds = (result%10+0x30);
		//-------------------------------------------//
		lcd_write_command(0xC2);
		lcd_write_byte(hundreds);
		lcd_write_byte(tens);
		lcd_write_byte(ones);
		__delay_ms(20);		
		 }
}
