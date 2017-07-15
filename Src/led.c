#include "inc.h"

void Led_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  
  HAL_GPIO_WritePin(ZK_RUN_GPIO_Port, ZK_RUN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : ZK_RUN_Pin */
  GPIO_InitStruct.Pin = ZK_RUN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(ZK_RUN_GPIO_Port, &GPIO_InitStruct);
	
}


