#include <util/delay.h>
#include"../include/LIB/STD_TYPES_GCC.h"
#include"../include/LIB/BIT_MATH_GCC.h"

#include "../include/MCAL/DIO/DIO_interface.h"
#include "../include/HAL/LCD/LCD_interface.h"
#include "../include/HAL/KEYPAD/KEYPAD_interface.h"
#include "../include/MCAL/GI/GI_interface.h"
#include "../include/MCAL/EXTI/EXTI_interface.h"
#include "../include/MCAL/ADC/ADC_interface.h"
#include "../include/MCAL/DIO/DIO_private.h"

#define F_CPU 8000000UL

#define KEY_PRESSED DIO_LOW

#define ZERO   0b0111111
#define ONE    0b0000110
#define TWO    0b1011011
#define THREE  0b1001111
#define FOUR   0b1100110
#define FIVE   0b1101101
#define SIX    0b1111101
#define SEVEN  0b0000111
#define EIGHT  0b1111111
#define NINE   0b1101111

	 u8 global_u8Second=0;
	 u8 global_u8Minute=0;
	 u8 global_u8Hour=0;

	u8 SEG[] = {ZERO,ONE,TWO,THREE,FOUR,
			    FIVE,SIX,SEVEN,EIGHT,NINE};
	static u8 Sec_Dig1 ,Sec_Dig2 ,Min_Dig1 ,Min_Dig2 ,Hr_Dig1 ,Hr_Dig2;

void Func(void);

int main (void)
{
	u8 local_u8Reading1=255;
	u8 local_u8Reading2=255;
	u8 local_u8Reading3=255;
	u8 local_u8Reading4=255;
	u8 local_u8Reading5=255;
	u8 local_u8Reading6=255;
	u8 local_u8Reading7=255;
	u8 local_u8Flag=0;



	MDIO_voidInit();
	MTIMER0_voidInit();
	MGI_voidEnable();
	MTIMER0_voidSetCallBackOVF(Func);
	while(1)
	{
		local_u8Reading1=MDIO_voidGetPinValue(DIO_PORTA,PIN0);
		local_u8Reading2=MDIO_voidGetPinValue(DIO_PORTA,PIN1);
		local_u8Reading3=MDIO_voidGetPinValue(DIO_PORTA,PIN2);
		local_u8Reading4=MDIO_voidGetPinValue(DIO_PORTA,PIN3);
		local_u8Reading5=MDIO_voidGetPinValue(DIO_PORTA,PIN4);
		local_u8Reading6=MDIO_voidGetPinValue(DIO_PORTA,PIN5);
		local_u8Reading7=MDIO_voidGetPinValue(DIO_PORTA,PIN6);
		if(local_u8Reading1==DIO_LOW)
		{
			global_u8Minute++;
			while(local_u8Reading1==DIO_LOW)
			{
				local_u8Reading1=MDIO_voidGetPinValue(DIO_PORTA,PIN0);
			}
		}
		else if(local_u8Reading2==DIO_LOW)
		{
			global_u8Hour++;
			while(local_u8Reading2==DIO_LOW)
			{
				local_u8Reading2=MDIO_voidGetPinValue(DIO_PORTA,PIN1);
			}
		}
		else if(local_u8Reading3==DIO_LOW)
		{
			global_u8Minute--;
			while(local_u8Reading3==DIO_LOW)
			{
				local_u8Reading3=MDIO_voidGetPinValue(DIO_PORTA,PIN2);
			}
		}
		else if(local_u8Reading4==DIO_LOW)
		{
			global_u8Hour--;
			while(local_u8Reading4==DIO_LOW)
			{
				local_u8Reading4=MDIO_voidGetPinValue(DIO_PORTA,PIN3);
			}
		}
		else if(local_u8Reading5==DIO_LOW)
		{
			if(local_u8Flag==0)
			{
			MGI_voidDisable();
			local_u8Flag=1;
			}
			else if(local_u8Flag==1)
			{
				MGI_voidEnable();
				local_u8Flag=0;
			}


			while(local_u8Reading5==DIO_LOW)
			{
				local_u8Reading5=MDIO_voidGetPinValue(DIO_PORTA,PIN4);
			}
		}
//		else if(local_u8Reading6==DIO_LOW)
//		{
//			MGI_voidEnable();
//			while(local_u8Reading6==DIO_LOW)
//			{
//				local_u8Reading6=MDIO_voidGetPinValue(DIO_PORTA,PIN5);
//			}
//		}
		else if(local_u8Reading7==DIO_LOW)
		{
			global_u8Second=0;
			global_u8Minute=0;
			global_u8Hour=0;
			while(local_u8Reading7==DIO_LOW)
			{
				local_u8Reading7=MDIO_voidGetPinValue(DIO_PORTA,PIN6);
			}
		}

		PORTD_REG=0b11111110;
		PORTC_REG=SEG[Sec_Dig1];
		_delay_us(200);

		PORTD_REG=0b11111101;
		PORTC_REG=SEG[Sec_Dig2];
		_delay_us(200);

		PORTD_REG=0b11111011;
		PORTC_REG=SEG[Min_Dig1];
		_delay_us(200);

		PORTD_REG=0b11110111;
		PORTC_REG=SEG[Min_Dig2];
		_delay_us(200);

		PORTD_REG=0b11101111;
		PORTC_REG=SEG[Hr_Dig1];
		_delay_us(200);

		PORTD_REG=0b11011111;
		PORTC_REG=SEG[Hr_Dig2];
		_delay_us(200);


	}


}



void Func(void)
{
	static u16 global_u16Counter=0;
	global_u16Counter++;

	if (global_u16Counter == 3907)
	{
		global_u16Counter=0;
		global_u8Second++;
		if(global_u8Second==60)
		{
			global_u8Second=0;
			global_u8Minute++;
		}
		if(global_u8Minute==60)
		{
			global_u8Minute=0;
			global_u8Hour++;
		}
		if(global_u8Hour==24)
		{
			global_u8Hour=0;
		}

		Sec_Dig2=global_u8Second/10;
		Sec_Dig1=global_u8Second - Sec_Dig2*10;

		Min_Dig2=global_u8Minute/10;
		Min_Dig1=global_u8Minute - Min_Dig2*10;

		Hr_Dig2=global_u8Hour/10;
		Hr_Dig1=global_u8Hour - Hr_Dig2*10;
	}
}
