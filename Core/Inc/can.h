/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.h
  * @brief   This file contains all the function prototypes for
  *          the can.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "motor.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern CAN_HandleTypeDef hcan1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_CAN1_Init(void);

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle);

void HAL_CAN_Filter_Config(void);

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle);

void CAN_Init(void);

void Motor_Set_Current(signed short int i1, signed short int i2, signed short int i3, signed short int i4);

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *canHandle);

void Lift_Motor_Set_Current(signed short int i5);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

typedef struct
{
	uint32_t DesDEVICE_ID   	:8;     //Դ�豸ID
	uint32_t Property		      :8;		  //ָ������ֵ����
	uint32_t SrcDEVICE_ID   	:8;     //Ŀ���豸ID	
	uint32_t Priority				  :4;			//���ȼ�
	uint32_t Permit           :1;
}EXT_ID_Typedef;								  //����29λ��չID
typedef union
{
	uint32_t	all;
	uint32_t	StdID		:11;		//��׼ID
	EXT_ID_Typedef	  ExtID;		//��չID
}ID;

typedef union
{
	int8_t			chars[8];			  //8��char
	int16_t			shorts[4];			//4��short
	int32_t			ints[2];			  //2��int
	int64_t			longs[1];			  //1��Long
	uint8_t			uchars[8];			//8���޷���char
	uint16_t		ushorts[4];			//4���޷���short
	uint32_t		uints[2];			  //2���޷���int
	uint64_t		ulongs[1];			//1���޷���Long
	float       floats[2];
}CAN_Data;								//����CAN��֡�ڵ���������

typedef struct
{
	ID 			id;						//ID
	char		isRemote;			//�Ƿ���Զ��֡
	char 		length;				//���ݳ���
	CAN_Data	data;				//����
}Frame;

#ifdef __cplusplus
}
#endif

#endif /* __CAN_H__ */

