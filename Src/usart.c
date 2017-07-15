

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif
#include "inc.h"

//////////////////////////////////////////////////////////////////////////////////	 
	  

unsigned char USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
unsigned int USART1_P_Rx, USART1_P_Use;
unsigned char USART6_RX_BUF[USART6_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
unsigned int USART6_P_Rx, USART6_P_Use;


UART_HandleTypeDef huart1,huart6;

void UartConfig_Init(UART_HandleTypeDef* huart);
//void HAL_UART_MspInit(UART_HandleTypeDef* huart);

void Uart1_Init(void)
{    
	
	
	   huart1.Instance=USART1;	
     UartConfig_Init(&huart1);

	
    //   HAL_UART_MspInit(&huart1);
	   USART1_P_Rx=0;//串口缓存器指针初始化
	   USART1_P_Use=0;

}

void Uart6_Init(void)
{    
	
	

	   huart6.Instance=USART6;	
     UartConfig_Init(&huart6);	
	
    //   HAL_UART_MspInit(&huart1);
	   USART6_P_Rx=0;//串口缓存器指针初始化
	   USART6_P_Use=0;
}


//UART底层初始化，时钟使能，引脚配置，中断配置
//此函数会被HAL_UART_Init()调用
//huart:串口句柄
void UartConfig_Init(UART_HandleTypeDef* huart)
//void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

     GPIO_InitTypeDef GPIO_InitStruct;
     if(huart->Instance==USART1)
    {
						/* USER CODE BEGIN USART1_MspInit 0 */

						/* USER CODE END USART1_MspInit 0 */
							/* Peripheral clock enable */
							__HAL_RCC_USART1_CLK_ENABLE();
						
							/**USART1 GPIO Configuration    
							PA9     ------> USART1_TX
							PA10     ------> USART1_RX 
							*/
							GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
							GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
							GPIO_InitStruct.Pull = GPIO_PULLUP;
							GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
							GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
							HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
							
							__HAL_RCC_GPIOA_CLK_ENABLE();
					 
								huart1.Instance = USART1;
								huart1.Init.BaudRate = 115200;
								huart1.Init.WordLength = UART_WORDLENGTH_8B;
								huart1.Init.StopBits = UART_STOPBITS_1;
								huart1.Init.Parity = UART_PARITY_NONE;
								huart1.Init.Mode = UART_MODE_TX_RX;
								huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
								huart1.Init.OverSampling = UART_OVERSAMPLING_16;
								HAL_UART_Init(&huart1);
								
								__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);//使能中断
								HAL_NVIC_SetPriority(USART1_IRQn,3,3); //设置优先级
								HAL_NVIC_EnableIRQ(USART1_IRQn); //使能中断

       }

     if(huart->Instance==USART6)
    {
						/* USER CODE BEGIN USART1_MspInit 0 */

						/* USER CODE END USART1_MspInit 0 */
							/* Peripheral clock enable */
							__HAL_RCC_USART6_CLK_ENABLE();
						
							/**USART1 GPIO Configuration    
							PA9     ------> USART1_TX
							PA10     ------> USART1_RX 
							*/
							GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
							GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
							GPIO_InitStruct.Pull = GPIO_PULLUP;
							GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
							GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
							HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
							
							__HAL_RCC_GPIOC_CLK_ENABLE();
					 

								
								  huart6.Instance = USART6;
									huart6.Init.BaudRate = 115200;
									huart6.Init.WordLength = UART_WORDLENGTH_8B;
									huart6.Init.StopBits = UART_STOPBITS_1;
									huart6.Init.Parity = UART_PARITY_NONE;
									huart6.Init.Mode = UART_MODE_TX_RX;
									huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
									huart6.Init.OverSampling = UART_OVERSAMPLING_16;
									HAL_UART_Init(&huart6);
								
								__HAL_UART_ENABLE_IT(&huart6,UART_IT_RXNE);//使能中断
								HAL_NVIC_SetPriority(USART6_IRQn,2,3); //设置优先级
								HAL_NVIC_EnableIRQ(USART6_IRQn); //使能中断

       }

}



//开启一次DMA传输
//huart:串口句柄
//pData：传输的数据指针
//Size:传输的数据量
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
    HAL_DMA_Start(huart->hdmatx, (uint32_t)pData, (uint32_t)&huart->Instance->DR, Size);//开启DMA传输
    
    huart->Instance->CR3 |= USART_CR3_DMAT;//使能串口DMA发送
}	

 

//串口1中断服务程序
void USART1_IRQHandler(void)                	
{ 

#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART1->SR&(1<<5))//接收到数据
	{	 
		USART1_RX_BUF[USART1_P_Rx&0XFFF]=USART1->DR; 
	  USART1_P_Rx++;	
		
		
					     
	} 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 


void USART6_IRQHandler(void)
{
	
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART6->SR&(1<<5))//接收到数据
	{	 
		USART6_RX_BUF[USART6_P_Rx&0XFFF]=USART6->DR; 
	  USART6_P_Rx++;	
		
		
					     
	} 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
	
}


