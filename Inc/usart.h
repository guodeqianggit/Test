#ifndef _USART_H
#define _USART_H
#include "stdio.h"	
//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************
//V1.0修改说明 
////////////////////////////////////////////////////////////////////////////////// 

//#include "type.h"
#include "stm32f4xx_hal.h"


#define  USART1_REC_LEN  0x1000
#define  USART6_REC_LEN  0x1000
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define RXBUFFERSIZE   1 //缓存大小


extern UART_HandleTypeDef huart1,huart6; //UART句柄

extern unsigned char USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern unsigned int USART1_P_Rx, USART1_P_Use;
extern unsigned char USART6_RX_BUF[USART6_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern unsigned int USART6_P_Rx, USART6_P_Use;


//如果想串口中断接收，请不要注释以下宏定义
extern void Uart1_Init(void);
extern void Uart6_Init(void);
extern void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#endif
