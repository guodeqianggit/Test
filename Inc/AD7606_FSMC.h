/*
*********************************************************************************************************
*
*	模块名称 : AD7606数据采集模块
*	文件名称 : bsp_ad7606.h
*	版    本 : V1.0

*
*********************************************************************************************************
*/

#ifndef _AD7606_FSMC_H
#define _AD7606_FSMC_H


#include "type.h"

#define  AD7606_ADDRBASE   0x64000000
#define  AD7606_CHANNELNUM   0x8



//-----------------------------M新动力-----------------------------------------------------------

#define AD_RESET_Pin GPIO_PIN_12
#define AD_RESET_GPIO_Port GPIOB
#define AD_CONVST_Pin GPIO_PIN_13
#define AD_CONVST_GPIO_Port GPIOB
#define AD_BUSY_Pin GPIO_PIN_11
#define AD_BUSY_GPIO_Port GPIOA



#define BUSY_IRQn          EXTI0_IRQn 
#define BUSY_READ()        HAL_GPIO_ReadPin(AD_BUSY_GPIO_Port,  AD_BUSY_Pin)




#define AD_RESET_H()   	HAL_GPIO_WritePin(GPIOB, AD_RESET_Pin, GPIO_PIN_SET);
#define AD_RESET_L()   	HAL_GPIO_WritePin(GPIOB, AD_RESET_Pin, GPIO_PIN_RESET);

#define AD_CONVST_H()   	HAL_GPIO_WritePin(GPIOB, AD_CONVST_Pin, GPIO_PIN_SET);
#define AD_CONVST_L()   	HAL_GPIO_WritePin(GPIOB, AD_CONVST_Pin, GPIO_PIN_RESET);








//------------------------------------------------------------------------->
#define DATA_LEN 128  //数组深度
typedef struct
{
	u16  CHn[8][DATA_LEN];//8个通道，每个深度 DATA_LEN
	u16  R_index;   //写入CHn 数组的 索引
	u16  W_index;   //读出CHn 数组的 索引
	u8   DMASend ;
	u8   Dat_Flg;
	
}AD7606PARA_STRUCT;

extern AD7606PARA_STRUCT AD7606;


//定义FSMC访问地址 AD7606
#define AD7606_CS0_Base   ((uint32_t)(0x60000000 | 0x00000000))
#define AD7606_CS0_FSMC   ((AD7606_TypeDef *) AD7606_CS0_Base)




//定义FSMC访问地址 FT
#define AD7606_FT_Base    ((uint32_t)(0x60000000 | 0x00300000))//16bit模式
//#define AD7606_FT_Base    ((uint32_t)(0x60000000 | 0x00180000))//8bit模式
#define AD7606_FT_FSMC   ((AD7606_TypeDef *) AD7606_FT_Base)

extern void AD7606_Init(void);

#endif
