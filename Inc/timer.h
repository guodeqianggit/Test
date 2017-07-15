#ifndef __PWM_H
#define __PWM_H

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32429������
//��ʱ����������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:201/1/6
//�汾��V1.2
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
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
	                 u32  Type;//���ͱ�ʶ
	                 u32  Cur_Value;//
	                 u32  Second_Value;//
	                 u32  dat[CAP_NUM];
	                 u8   flg;//������ʶ�ǲ��ǵ�һ�ν��н������ݲɼ�
	                 u8   P_Write;//������ʶ���������ָ��
	                 u8   Gather_Num;//������ʶ���������ָ��
                   u32  Fre_Value;	                 
}	CAP_STURCT;



extern  CAP_STURCT   Fre_Gather,Dc1_Gather; 
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
extern void TIM2_CH3_Cap_Init(void);
extern void TIM3_Init(u16 arr,u16 psc);
extern void TIM4_Init(u16 arr,u16 psc);
extern void TIM13_CH1_Cap_Init(u32 arr,u16 psc);
extern void Fre_Gather_Init(void);
extern void Dc1_Gather_Init(void);
//extern void Dc1_Gather_Deal(void);
#endif

