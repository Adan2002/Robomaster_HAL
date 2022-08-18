#ifndef __TRACK_H__
#define __TRACK_H__
#include "stm32f4xx_hal.h"
#include <math.h>
#include "motor.h"
#include "delay.h"

#define SEARCH_GPIO_1 GPIOF
#define SEARCH_PIN_1 GPIO_PIN_1
#define SEARCH_OUT_1 HAL_GPIO_ReadPin(SEARCH_GPIO_1, SEARCH_PIN_1)

#define SEARCH_GPIO_2 GPIOE
#define SEARCH_PIN_2 GPIO_PIN_5
#define SEARCH_OUT_2 HAL_GPIO_ReadPin(SEARCH_GPIO_2, SEARCH_PIN_2)

#define SEARCH_GPIO_3 GPIOE
#define SEARCH_PIN_3 GPIO_PIN_6
#define SEARCH_OUT_3 HAL_GPIO_ReadPin(SEARCH_GPIO_3, SEARCH_PIN_3)

#define SEARCH_GPIO_4 GPIOC
#define SEARCH_PIN_4 GPIO_PIN_2
#define SEARCH_OUT_4 HAL_GPIO_ReadPin(SEARCH_GPIO_4, SEARCH_PIN_4)

#define SEARCH_GPIO_5 GPIOC
#define SEARCH_PIN_5 GPIO_PIN_3
#define SEARCH_OUT_5 HAL_GPIO_ReadPin(SEARCH_GPIO_5, SEARCH_PIN_5)

#define SEARCH_GPIO_6 GPIOC
#define SEARCH_PIN_6 GPIO_PIN_4
#define SEARCH_OUT_6 HAL_GPIO_ReadPin(SEARCH_GPIO_6, SEARCH_PIN_6)

#define SEARCH_GPIO_7 GPIOC
#define SEARCH_PIN_7 GPIO_PIN_5
#define SEARCH_OUT_7 HAL_GPIO_ReadPin(SEARCH_GPIO_7, SEARCH_PIN_7)

#define WHITE_AREA 0
#define BLACK_AREA 1

#define COMM_STOP 0
#define COMM_FORWARD 1
#define COMM_LEFT 2
#define COMM_RIGHT 3

extern u8 lastRobotState;
extern u8 currentRobotState;

void searchInit(void);

u8 wayAllBlack(void); 
u8 wayAllWhite(void); 
u8 needLeft(void);
u8 needRight(void);
u8 needForward(void);
u8 reachTarget(u8 target);

void runFront(void);
void runBack(void);
void runLeft(void);
void runRight(void);
void runStop(void);

void redRayDebug(void);

void stateInit(void);
u8 startTrack(void);

#endif /* __TRACK_H__ */

