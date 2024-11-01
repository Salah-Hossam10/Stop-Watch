/*
 * TIMER0_private.h
 *
 *  Created on: Mar 13, 2024
 *      Author: DELL
 */

#ifndef INCLUDE_MCAL_TIMER0_TIMER0_PRIVATE_H_
#define INCLUDE_MCAL_TIMER0_TIMER0_PRIVATE_H_

#define TCCR0  (*(volatile u8*)0x53)
#define TCNT0  (*(volatile u8*)0x52)
#define OCR0   (*(volatile u8*)0x5C)
#define TIMSK  (*(volatile u8*)0x59)
#define TIFR   (*(volatile u8*)0x58)
//NORMAL_DIO
//TOGGLE_CTC
//CLEAR_CTC
//SET_CTC

#define NORMAL_MODE        0
#define PHASE_CORRECT_MODE 1
#define CTC_MODE           2
#define FAST_PWM_MODE      3

#define NORMAL_DIO 0b00
#define TOGGLE_CTC 0b01
#define CLEAR_CTC  0b10
#define SET_CTC    0b11

#define NORMAL_MODE 0
#define CTC_MODE    1
#define PWM_MODE    2

#define NORMAL_DIO    0
#define NON_INVERTING 2
#define INVERTING     3

#endif /* INCLUDE_MCAL_TIMER0_TIMER0_PRIVATE_H_ */
