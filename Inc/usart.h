#ifndef _USART_H
#define _USART_H
#include "stdio.h"	
//////////////////////////////////////////////////////////////////////////////////	 

//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 

//#include "type.h"
#include "stm32f4xx_hal.h"


#define  USART1_REC_LEN  0x1000
#define  USART6_REC_LEN  0x1000
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define RXBUFFERSIZE   1 //�����С


extern UART_HandleTypeDef huart1,huart6; //UART���

extern unsigned char USART1_RX_BUF[USART1_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern unsigned int USART1_P_Rx, USART1_P_Use;
extern unsigned char USART6_RX_BUF[USART6_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern unsigned int USART6_P_Rx, USART6_P_Use;


//����봮���жϽ��գ��벻Ҫע�����º궨��
extern void Uart1_Init(void);
extern void Uart6_Init(void);
extern void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

#endif
