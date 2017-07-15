#ifndef __PWM_H
#define __PWM_H

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32429开发板
//定时器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:201/1/6
//版本：V1.2
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#include "type.h"
#include "stm32f4xx_hal.h"

#define CF1_Pin GPIO_PIN_10
#define CF1_GPIO_Port GPIOB

#define  FRE_CAP  1
#define  DC1_CAP  2
#define  CAP_NUM  8

typedef  struct {
	                 u32  Type;//类型标识
	                 u32  Cur_Value;//
	                 u32  Second_Value;//
	                 u32  dat[CAP_NUM];
	                 u8   flg;//用来标识是不是第一次进行进行数据采集
	                 u8   P_Write;//用来标识数组的数据指针
	                 u8   Gather_Num;//用来标识数组的数据指针
                   u32  Fre_Value;	                 
}	CAP_STURCT;



extern  CAP_STURCT   Fre_Gather,Dc1_Gather; 
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
extern void TIM2_CH3_Cap_Init(void);
extern void TIM3_Init(u16 arr,u16 psc);
extern void TIM4_Init(u16 arr,u16 psc);
extern void TIM13_CH1_Cap_Init(u32 arr,u16 psc);
extern void Fre_Gather_Init(void);
extern void Dc1_Gather_Init(void);
//extern void Dc1_Gather_Deal(void);
#endif

