/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "inc.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/




/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/




void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
//void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
void MX_FMC_Init(void);
void MX_I2C1_Init(void);
u8 turntime(u8 time);
extern void Read_FramId (void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
unsigned char test2[20]={0x10,0x8b,0x01,0x00,0x8c,0x16,0x67,0x75,0x6f,0x20,0x64,0x65,0x20,0x71,0x69,0x61,0x6e,0x67,0x0d,0x0a};
//unsigned char test2[20];
unsigned char test3[20];
//unsigned char test2[16]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0d,0x0a};
//unsigned char test2[]={"hello guo de qiang\n\n"};
unsigned char led_flg;
int main(void)
{
   unsigned int temp,num;
	 unsigned char flg;
	 unsigned char Rtc_MemoryAddr,Rtc_Data;
	unsigned int test;
	 unsigned short Ad_Value;
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
  delay_init(180);//根据主频设置
	
	
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
 // MX_DMA_Init( ); 
	
	//HAL_UART_MspInit(&huart1);
	
	MYDMA_Config();////////////////////////////////////
	
	//MX_USART1_UART_Init();
	Uart1_Init( ); //////////////////////////////////
	Uart6_Init( ); ////////////////////////////////// 
	SPI1_Init( );
//	MX_FMC_Init();
//	HAL_SRAM_MspInit(&hsram3);
	Sram_Init( );
	
	// MX_I2C1_Init( );
	// HAL_I2C_MspInit(&hi2c1);
	 I2C1_Init( );
	// AD7606_Init();
  // TIM3_Init(45000-1,2-1);	//定时器时钟45M，分频系数1，所以45M/1=45Mhz的计数频率，计数45000次为1ms 	 3级
	//TIM4_Init(45000-1,2-1);	//定时器时钟45M，分频系数1，所以45M/1=45Mhz的计数频率，计数45000次为1ms 	 3级
	 Led_Init( );
   led_flg=0;
	 //flg=0xaa;
	// HAL_UART_Transmit(&huart1, &flg, 1, 1000);	 
	 
	 DS18B20_Init();
   MY_ADC_Init( ); 
	 TIM13_CH1_Cap_Init(0xFFFFFFFF,90-1); //以1Mhz的频率计数	频率采样0XFFFF  采集中断优先级 2,0
	 Dc1_Gather_Init( );
   Read_FramId ( );	
   HAL_UART_Transmit(&huart1, Spi1_Rxdata, 10, 1000);	
	 while(1);
	 while(1)
	 {
		 
		 
		   delay_ms(1000);
		   ZK_RUN_ON();
		   delay_ms(1000);
		   ZK_RUN_OFF();
		   
		  // if(Dc1_Gather.Gather_Num>=CAP_NUM)
			// {
						flg=(u8)Dc1_Gather.Fre_Value;
						HAL_UART_Transmit(&huart1, &flg, 1, 1000);
						flg=(u8)(Dc1_Gather.Fre_Value>>8);
						HAL_UART_Transmit(&huart1, &flg, 1, 1000); 
			// }
		 
		 
//		  Ad_Value =Get_Adc_Average(ADC_CHANNEL_7,20);//获取通道5的转换值，20次取平均
//		  flg=(u8)Ad_Value;
//	    HAL_UART_Transmit(&huart1, &flg, 1, 1000);
//		  flg=(u8)(Ad_Value>>8);
//	    HAL_UART_Transmit(&huart1, &flg, 1, 1000);		  
//		 if(led_flg==0)
//		 {
//			  ZK_RUN_ON();
//		 }else 
//		 {
//			 ZK_RUN_OFF();
//		 }
	 }
	 
while(1)
{  
	if(USART1_P_Use != USART1_P_Rx)//如果串口接收的有数据
		
	{             USART1_P_Use++;
	
                  AD_CONVST_H(); 

										for(num=0;num<200;num++)
										{
										} 
										AD_CONVST_L(); 
										
   while(1){   
		           if(AD7606.Dat_Flg==1)     
							  {
//										for(num=0;num<200;num++)
//										{
//										}
//										for(num=0;num<AD7606_CHANNELNUM;num++)
//										{
//												AD7606.CHn[num][0]=  ( *((volatile u16 *) AD7606_ADDRBASE));
//										}
										
												 test2[0]= (AD7606.CHn[0][0] & 0xff);
												 test2[1]= ((AD7606.CHn[0][0]>>8) & 0xff);
												 HAL_UART_Transmit(&huart1, test2, 2, 1000);	
										     AD7606.Dat_Flg=0;
								    break;
								 }
							}
		
		}		
	}
//	 while(1)
//	 {
//		   if(AD7606.Dat_Flg==1)
//			 {
//				   test2[0]= (AD7606.CHn[0][0] & 0xff);
//				   test2[1]= ((AD7606.CHn[0][0]>>8) & 0xff);
//           HAL_UART_Transmit(&huart1, test2, 2, 1000);
//				   AD7606.Dat_Flg=0;
//			 }else 
//			 {
//				 
//			 }
//                 				 
//		 }	 
   
	 
////	  I2C0MasterWriteByte(0x10,0xA9);//WRTC1置1,写允许，报警模式中断选择，选择为频率中断 VBAT模式选择 频率中断允许0x10101001
//      Rtc_MemoryAddr=0x10;
//			Rtc_Data=0X80;
//      HAL_I2C_Mem_Write(&hi2c1, 0x64, Rtc_MemoryAddr, 1, &Rtc_Data, 1, 1000);//WRTC1置1,
////			

////    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3置1
//      Rtc_MemoryAddr=0x0F;
//			Rtc_Data=0X84;
//      HAL_I2C_Mem_Write(&hi2c1, 0x64, Rtc_MemoryAddr, 1, &Rtc_Data, 1, 1000);//WRTC1置1,
////			
////			
//////    I2C0MasterWriteByte(0x11,0x8f);//ARST置1 ts3/2/1/0设置频率为1HZ
////    I2C0MasterWriteByte(0x14,0x01);//写标志位
//		  Rtc_MemoryAddr=0x14;
//			Rtc_Data=0X55;
//      HAL_I2C_Mem_Write(&hi2c1, 0x64, Rtc_MemoryAddr, 1, &Rtc_Data, 1, 1000);//WRTC1置1,

//		  Rtc_MemoryAddr=0x15;
//			Rtc_Data=0XAA;
//      HAL_I2C_Mem_Write(&hi2c1, 0x64, Rtc_MemoryAddr, 1, &Rtc_Data, 1, 1000);//WRTC1置1,
////			
//	    HAL_I2C_Mem_Read(&hi2c1, 0x65, 0x14, 1, test3, 1, 1000);
//			HAL_UART_Transmit(&huart1, test3,1, 1000);	
//	    HAL_I2C_Mem_Read(&hi2c1, 0x65, 0x15, 1, test3, 1, 1000);
//			HAL_UART_Transmit(&huart1, test3,1, 1000);			

//	 
	// temp=test3[0];
	// test3[1]= turntime(temp);
//	 
//	 
	 
//	 
//	 for(temp=0;temp<20;temp++)
//	 {
//		  *((unsigned char *)(SRAM_ADDRBASE+temp))= test2[temp];
//		 
//	 }
//		 
//	 for(temp=0;temp<20;temp++)
//	 {
//		     test3[temp]=(*((unsigned char *)(SRAM_ADDRBASE+temp))) ;
//	 }
  //Read_FramId ( );	
	
  //HAL_UART_Transmit(&huart1, test3, 20, 1000);	
	
	
	
	
	//HAL_UART_MspInit(&huart1);
    
  

	   // temp= sizeof(test2);
   // MYDMA_USART_Transmit(&huart1,(unsigned char *)test2 ,temp); //启动传输  
	 
   
		while(1)
		{
			     //MYDMA_USART_Transmit(&huart6,test2 ,6); //启动传输  
			    // for(test=0;test<1000000;
			
			   if(USART6_P_Use != USART6_P_Rx)
				 {
					 
					      HAL_UART_Transmit(&huart1, &USART6_RX_BUF[USART6_P_Use &0xfff], 1, 1000);
					     // HAL_UART_Transmit(&huart6, test2, 6, 1000);
					      MYDMA_USART_Transmit(&huart6,test2 ,6); //启动传输  
								
               while(1)					 
               {
         					 if(__HAL_DMA_GET_FLAG(&hdma_usart6_tx,DMA_FLAG_TCIF2_6))//等待DMA2_Steam7传输完成
											{
													__HAL_DMA_CLEAR_FLAG(&hdma_usart6_tx,DMA_FLAG_TCIF2_6 );//清除DMA2_Steam7传输完成标志
													HAL_UART_DMAStop(&huart6);      //传输完成以后关闭串口DMA

													   break; 

											}		
								}											
					    //  USART6_P_Use=USART6_P_Use &0xfff;
					    USART6_P_Use++;
					    
				 }
					 

//                temp= sizeof(test2);
//                MYDMA_USART_Transmit(&huart1,(unsigned char *)test2 ,temp); //启动传输  
//							 while(1)
//							{
//											if(__HAL_DMA_GET_FLAG(&hdma_usart1_tx,DMA_FLAG_TCIF3_7))//等待DMA2_Steam7传输完成
//											{
//													__HAL_DMA_CLEAR_FLAG(&hdma_usart1_tx,DMA_FLAG_TCIF3_7);//清除DMA2_Steam7传输完成标志
//													HAL_UART_DMAStop(&huart1);      //传输完成以后关闭串口DMA

//													   break; 

//											}
//											
//											
//												
//										 
//			 
//							 }
							
							 
				
			}		
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}







/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 20;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  HAL_PWREx_EnableOverDrive();

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}


/* USART1 init function */
void MX_USART1_UART_Init(void)
{

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


/* FMC initialization function */
void MX_FMC_Init(void)
{
  FMC_NORSRAM_TimingTypeDef Timing;

  /** Perform the SRAM3 memory initialization sequence
  */
  hsram3.Instance = FMC_NORSRAM_DEVICE;
  hsram3.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram3.Init */
  hsram3.Init.NSBank = FMC_NORSRAM_BANK3;
  hsram3.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram3.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
  hsram3.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram3.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram3.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram3.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
  hsram3.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hsram3.Init.WriteOperation = FMC_WRITE_OPERATION_ENABLE;
  hsram3.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
  hsram3.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hsram3.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram3.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hsram3.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram3.Init.PageSize = FMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = 5;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 45;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */

  HAL_SRAM_Init(&hsram3, &Timing, NULL);

}




/* I2C1 init function */
//void MX_I2C1_Init(void)
//{

//  hi2c1.Instance = I2C1;
//  hi2c1.Init.ClockSpeed = 100000;
//  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
//  hi2c1.Init.OwnAddress1 = 0;
//  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//  hi2c1.Init.OwnAddress2 = 0;
//  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
//  HAL_I2C_Init(&hi2c1);

//}




/** 
  * Enable DMA controller clock
  */
void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream7_IRQn interrupt configuration */
 // HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
 // HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);

}





u8 turntime(u8 time)
{
   u8 ReadFig ,ReadFigH,ReadFigL,retime;
   
   ReadFig = time;
   ReadFigL = ReadFig & 0x0F;
   ReadFigH = (ReadFig>>4)&0x07;
   retime = ReadFigH *10 + ReadFigL;
   
   return(retime);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  //__HAL_RCC_GPIOH_CLK_ENABLE();
 //// __HAL_RCC_GPIOA_CLK_ENABLE();
	
	
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();	
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
