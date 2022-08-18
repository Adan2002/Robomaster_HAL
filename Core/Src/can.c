/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

extern volatile MotorTypeDef Motor_1, Motor_2,Motor_3, Motor_4;
extern volatile MotorTypeDef Motor_5;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_9TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_4TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
//    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
//    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
//    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
		
		GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN1_MspInit 1 */
		HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
		HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
  /* USER CODE END CAN1_MspInit 1 */
		
  }
}

void HAL_CAN_Filter_Config(void){
	CAN_FilterTypeDef FilterConfig;
	
	FilterConfig.FilterIdHigh = 0x0000;
	FilterConfig.FilterIdLow = 0x0000;
	FilterConfig.FilterMaskIdHigh = 0x0000;
	FilterConfig.FilterMaskIdLow = 0x0000;
	FilterConfig.FilterFIFOAssignment = CAN_FilterFIFO0;
	FilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	FilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	FilterConfig.FilterActivation = ENABLE;
	FilterConfig.FilterBank = 0;

	if(HAL_CAN_ConfigFilter(&hcan1, &FilterConfig)!=HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *canHandle){
	uint8_t aRxData[8], i;
	CAN_RxHeaderTypeDef RxMessage;
		if (HAL_CAN_GetRxMessage(canHandle, CAN_RX_FIFO0, &RxMessage, aRxData) == HAL_OK)
		{
			if(RxMessage.StdId == Motor_1_ID)
			{    
				Motor_1.CurrentMeasure=(float)(short)(aRxData[4]<<8 | aRxData[5]);
				Motor_1.SpeedMeasure =((float)(short)(aRxData[2]<<8 | aRxData[3]))/19.0;//*187.0/3591;   
				if(Motor_1.PosPre == 0 && Motor_1.PosNow == 0 )
					Motor_1.PosPre = Motor_1.PosNow = (short)(aRxData[0]<<8 | aRxData[1]);
				else
				{
					Motor_1.PosPre = Motor_1.PosNow;
					Motor_1.PosNow =  (short)(aRxData[0]<<8 | aRxData[1]);
				}
				Motor_1.PositionMeasure += Get_RM3508_Distance(Motor_1);
			}
			else if(RxMessage.StdId == Motor_2_ID)
			{
				Motor_2.CurrentMeasure=(float)(short)(aRxData[4]<<8 | aRxData[5]);
				Motor_2.SpeedMeasure =((float)(short)(aRxData[2]<<8 | aRxData[3]))/19.0;//*187.0/3591;   
				if(Motor_2.PosPre == 0 && Motor_2.PosNow == 0 )
					Motor_2.PosPre = Motor_2.PosNow = (short)(aRxData[0]<<8 | aRxData[1]);
				else
				{
					Motor_2.PosPre = Motor_2.PosNow;
					Motor_2.PosNow =  (short)(aRxData[0]<<8 | aRxData[1]);
				}
				Motor_2.PositionMeasure += Get_RM3508_Distance(Motor_2);
			}
			else if(RxMessage.StdId == Motor_3_ID)
			{
						
				Motor_3.CurrentMeasure=(float)(short)(aRxData[4]<<8 | aRxData[5]);
				Motor_3.SpeedMeasure =((float)(short)(aRxData[2]<<8 | aRxData[3]))/19.0;//*187.0/3591;   
				if(Motor_3.PosPre == 0 && Motor_3.PosNow == 0 )
					Motor_3.PosPre = Motor_3.PosNow = (short)(aRxData[0]<<8 | aRxData[1]);
				else
				{
					Motor_3.PosPre = Motor_3.PosNow;
					Motor_3.PosNow =  (short)(aRxData[0]<<8 | aRxData[1]);
				}
				Motor_3.PositionMeasure += Get_RM3508_Distance(Motor_3);
			}
			
				else if(RxMessage.StdId == Motor_4_ID)
			{
						
				Motor_4.CurrentMeasure=(float)(short)(aRxData[4]<<8 | aRxData[5]);
				Motor_4.SpeedMeasure =((float)(short)(aRxData[2]<<8 | aRxData[3]))/19.0;//*187.0/3591;   
				if(Motor_4.PosPre == 0 && Motor_4.PosNow == 0 )
					Motor_4.PosPre = Motor_4.PosNow = (short)(aRxData[0]<<8 | aRxData[1]);
				else
				{
					Motor_4.PosPre = Motor_4.PosNow;
					Motor_4.PosNow =  (short)(aRxData[0]<<8 | aRxData[1]);
				}
				Motor_4.PositionMeasure += Get_RM3508_Distance(Motor_4);
			}
				else if(RxMessage.StdId == Motor_5_ID)
			{ 
						
				Motor_5.CurrentMeasure=(float)(short)(aRxData[4]<<8 | aRxData[5]);
				Motor_5.SpeedMeasure =((float)(short)(aRxData[2]<<8 | aRxData[3]))/19.0;//*187.0/3591;   
				if(Motor_5.PosPre == 0 && Motor_5.PosNow == 0 )
					Motor_5.PosPre = Motor_5.PosNow = (short)(aRxData[0]<<8 | aRxData[1]);
				else
				{
					Motor_5.PosPre = Motor_5.PosNow;
					Motor_5.PosNow =  (short)(aRxData[0]<<8 | aRxData[1]);
				}
				Motor_5.PositionMeasure += Get_RM3508_Distance(Motor_5);
			}
		}
}

void Motor_Set_Current(signed short int i1, signed short int i2, signed short int i3, signed short int i4)
{
	CAN_TxHeaderTypeDef TxMessage;
	uint8_t aTxData[8];
	uint32_t TxMailbox;
	
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 0x08;
	TxMessage.StdId = 0x200;
	
	aTxData[0] = i1 >> 8;
	aTxData[1] = i1;
	aTxData[2] = i2 >> 8;
	aTxData[3] = i2;
	aTxData[4] = i3 >> 8;
	aTxData[5] = i3;
	aTxData[6] = i4 >> 8;
	aTxData[7] = i4;
	
	HAL_CAN_AddTxMessage(&hcan1, &TxMessage, aTxData, &TxMailbox);
}

void Lift_Motor_Set_Current(signed short int i5)
{
	CAN_TxHeaderTypeDef TxMessage;
	uint8_t aTxData[8];
	uint32_t TxMailbox;
	
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 0x02;
	TxMessage.StdId = 0x1FF;
	
	aTxData[0] = i5 >> 8;
	aTxData[1] = i5;
	
	HAL_CAN_AddTxMessage(&hcan1, &TxMessage, aTxData, &TxMailbox);
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle){

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

  /* USER CODE BEGIN CAN1_MspDeInit 1 */
		HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
void CAN_Init(void){
	MX_CAN1_Init();
	HAL_CAN_Filter_Config();
	HAL_CAN_MspInit(&hcan1);
	HAL_CAN_Start(&hcan1);
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
//		HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
//		HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
//		HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
//		HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
}

/* USER CODE END 1 */
