#ifndef __LED_H__
#define __LED_H__
#include "stm32f4xx_hal.h"


#define LED_GPIO GPIOG
#define LED_PIN_8 GPIO_PIN_8
#define LED_PIN_1 GPIO_PIN_1
#define LED_PIN_2 GPIO_PIN_2
#define LED_PIN_3 GPIO_PIN_3
#define LED_PIN_4 GPIO_PIN_4
#define LED_PIN_5 GPIO_PIN_5
#define LED_PIN_6 GPIO_PIN_6
#define LED_PIN_7 GPIO_PIN_7


void ledInit(void);
void ledAllOff(void);
void ledAllOn(void);

#endif /* __LED_H__ */

