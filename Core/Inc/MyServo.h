#ifndef _MYSERVO_H
#define _MYSERVO_H
#include "sys.h"
#include "tim.h"

#define Center_Angle 18670
#define Right_Angle 18000 //  +90
#define Left_Angle 19340  //  -90
#define Servo_PSC 83
#define Servo_arr 19999

#define USE_PD14_PIN
//#define USE_PD15_PIN

extern TIM_HandleTypeDef htim4;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_TIM4_Init(void);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void HAL_Servo_Init(void);

void Servo_Init(void );
void Servo_Angle_Set(int angle );
#endif
