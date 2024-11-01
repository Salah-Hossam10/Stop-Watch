/*
 * TIMER0_program.c
 *
 *  Created on: Mar 13, 2024
 *      Author: DELL
 */

#include"../include/LIB/STD_TYPES_GCC.h"
#include"../include/LIB/BIT_MATH_GCC.h"

#include "../include/MCAL/TIMER0/TIMER0_interface.h"
#include "../include/MCAL/TIMER0/TIMER0_private.h"
#include "../include/MCAL/TIMER0/TIMER0_configuration.h"

#define TCCR0_WGM01 3
#define TCCR0_WGM00 6

#define TIMSK_OCIE0 1
#define TIMSK_TOIE0 0

#define TCCR0_CS00  0
#define TCCR0_CS01  1
#define TCCR0_CS02  2


#define NULL 0

void (*TIMER0_OVF_CALLBACK) (void) = NULL;
void (*TIMER0_CTC_CALLBACK) (void) = NULL;

void MTIMER0_voidInit (void)
{
#if TIMER0_MODE==NORMAL_MODE

	//Waveform Generation Mode Bit
	CLR_BIT(TCCR0,TCCR0_WGM01);
	CLR_BIT(TCCR0,TCCR0_WGM00);
	//Output Compare Match Interrupt Enable
	CLR_BIT(TIMSK,TIMSK_OCIE0);
	//Overflow Interrupt Enable
    SET_BIT(TIMSK,TIMSK_TOIE0);
    //Clock Select
    TCCR0&=0b11111000;
    TCCR0|=CLK_CONFIGURATION;

#elif TIMER0_MODE == CTC_MODE
	//Waveform Generation Mode Bit
	SET_BIT(TCCR0, TCCR0_WGM01);
	CLR_BIT(TCCR0, TCCR0_WGM00);
	//Output Compare Match Interrupt Enable
	SET_BIT(TIMSK, TIMSK_OCIE0);
	//Overflow Interrupt Enable
	CLR_BIT(TIMSK, TIMSK_TOIE0);
	// Set Compare Match Unit Value
	OCR0 = OCR_VALUE;
	//Clock Select
	TCCR0 &= 0b11001000;
	TCCR0 |= (CLK_CONFIGURATION | (CTC_OC0_PIN_ACTION << 4));


#elif TIMER0_MODE == FAST_PWM_MODE
	//Waveform Generation Mode Bit
	SET_BIT(TCCR0, TCCR0_WGM01);
	SET_BIT(TCCR0, TCCR0_WGM00);
	// Set Compare Match Unit Value
	OCR0 = OCR_VALUE;
	//Clock Select
	TCCR0 &= 0b11001000;
	TCCR0 |= (CLK_CONFIGURATION | (FAST_PWM_OC0_PIn_ACTION << 4));



#else
#error WRONG TIMER0 CONFIGURATION
#endif

}

void MTIMER0_voidStopTimer(void)
{

	//TO STOP TIMER CLEAR THE THREE BITS
	CLR_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	CLR_BIT(TCCR0,TCCR0_CS02);

}

void MTIMER0_voidSetPreLoadValue (u8 A_u8PreLoadValue)
{

	TCNT0=A_u8PreLoadValue;
}

void MTIMER0_voidSetOCR0Value(u8 A_u8Value)
{

	OCR0=A_u8Value;
}

void MTIMER0_voidSetCallBackOVF (void (*PtrToFunc) (void))
{

	if(PtrToFunc!=NULL)
	{
		TIMER0_OVF_CALLBACK=PtrToFunc;
	}
}

void MTIMER0_voidSetCallBackCTC (void (*PtrToFunc) (void))
{

	if(PtrToFunc!=NULL)
	{
		TIMER0_CTC_CALLBACK=PtrToFunc;
	}
}

void __vector_10(void)  __attribute__((signal));
void __vector_10(void)
{
	if(TIMER0_CTC_CALLBACK!=NULL)
	{
		TIMER0_CTC_CALLBACK();
	}
}

void __vector_11(void)  __attribute__((signal));
void __vector_11(void)
{
	if(TIMER0_OVF_CALLBACK!=NULL)
	{
		TIMER0_OVF_CALLBACK();
	}
}





























//    //Compare Flag 2
//    CLR_BIT(TIFR,TIFR_OCF2);
//    //Overflow Flag
//    SET_BIT(TIFR,TIFR_TOV2);
//    //Clock Select
