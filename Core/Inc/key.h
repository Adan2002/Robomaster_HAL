#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f4xx_hal.h"
#include "stdint.h"

typedef uint8_t u8;

#define KEY0 		HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) //PB2

#define KEY0_PRES 	1

void KEY_Init(void);	
u8 KEY_Scan(u8);  	

#endif
