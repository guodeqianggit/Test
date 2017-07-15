#ifndef __LED_H
#define __LED_H
#include "stm32f4xx_hal.h"
#include "type.h"
 
 
#define ZK_RUN_Pin GPIO_PIN_12
#define ZK_RUN_GPIO_Port GPIOC
#define ZK_RUN_ON()     HAL_GPIO_WritePin(ZK_RUN_GPIO_Port, ZK_RUN_Pin, GPIO_PIN_RESET)
#define ZK_RUN_OFF()     HAL_GPIO_WritePin(ZK_RUN_GPIO_Port, ZK_RUN_Pin, GPIO_PIN_SET)

extern void Led_Init(void);
#endif


