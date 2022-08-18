#include "key.h"

void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOB_CLK_ENABLE();
	
	GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
 
} 

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;
	if(mode)key_up=1;  
	if(key_up&&(KEY0==0))
	{
		HAL_Delay(10);
		key_up=0;
		if(KEY0==0)return 1;
	}
 	return 0;
}




















