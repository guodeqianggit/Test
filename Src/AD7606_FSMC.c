#include "inc.h"

 
static  void Adgpio_Init(void );
static  void Adfmc_Init(void );
void AD7606_Init(void);
void TIM1_PWM_Init(u32 arr,u32 psc);
//unsigned char AD_Uart[20];

AD7606PARA_STRUCT  AD7606;
SRAM_HandleTypeDef hsram2;
TIM_HandleTypeDef htim1;
//TIM_HandleTypeDef TIM3_Handler;         //��ʱ��3PWM��� 
TIM_OC_InitTypeDef TIM1_CH1Handler;	    //��ʱ��3ͨ��4���


void AD7606_Init(void)
{
    	
   Adgpio_Init( ); 
   Adfmc_Init( );
	 
	 AD7606.Dat_Flg=0;
	 //TIM1_PWM_Init(u32 arr,u32 psc); 
	 TIM1_PWM_Init(9375-1,3-1); ////��ʱ��ʱ��180M����Ƶϵ��1������180M/45=4Mhz�ļ���Ƶ�ʣ�����625��Ϊ156.25us 



}

static  void Adfmc_Init(void )
{
	  
	 GPIO_InitTypeDef GPIO_InitStruct;
	 FMC_NORSRAM_TimingTypeDef Timing;
	
	
	__HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_FMC_CLK_ENABLE();
	
	 GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_9|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                          |GPIO_PIN_15|GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15 
                          |GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	
/** Perform the SRAM2 memory initialization sequence
  */
  hsram2.Instance = FMC_NORSRAM_DEVICE;
  hsram2.Extended = FMC_NORSRAM_EXTENDED_DEVICE;
  /* hsram2.Init */
  hsram2.Init.NSBank = FMC_NORSRAM_BANK2;
  hsram2.Init.DataAddressMux = FMC_DATA_ADDRESS_MUX_DISABLE;
  hsram2.Init.MemoryType = FMC_MEMORY_TYPE_SRAM;
  hsram2.Init.MemoryDataWidth = FMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram2.Init.BurstAccessMode = FMC_BURST_ACCESS_MODE_DISABLE;
  hsram2.Init.WaitSignalPolarity = FMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram2.Init.WrapMode = FMC_WRAP_MODE_DISABLE;
  hsram2.Init.WaitSignalActive = FMC_WAIT_TIMING_BEFORE_WS;
  hsram2.Init.WriteOperation = FMC_WRITE_OPERATION_DISABLE;
  hsram2.Init.WaitSignal = FMC_WAIT_SIGNAL_DISABLE;
  hsram2.Init.ExtendedMode = FMC_EXTENDED_MODE_DISABLE;
  hsram2.Init.AsynchronousWait = FMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram2.Init.WriteBurst = FMC_WRITE_BURST_DISABLE;
  hsram2.Init.ContinuousClock = FMC_CONTINUOUS_CLOCK_SYNC_ONLY;
  hsram2.Init.PageSize = FMC_PAGE_SIZE_NONE;
  /* Timing */
//  Timing.AddressSetupTime = 15;
//  Timing.AddressHoldTime = 15;
//  Timing.DataSetupTime = 255;
//  Timing.BusTurnAroundDuration = 15;
//  Timing.CLKDivision = 16;
//  Timing.DataLatency = 17;
//  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */
	
  Timing.AddressSetupTime = 5;
  Timing.AddressHoldTime = 15;
  Timing.DataSetupTime = 45;
  Timing.BusTurnAroundDuration = 15;
  Timing.CLKDivision = 16;
  Timing.DataLatency = 17;
  Timing.AccessMode = FMC_ACCESS_MODE_A;	
  /* Timing */
																							 // Timing.AddressSetupTime = 8;
																							//  Timing.AddressHoldTime = 3;
																							//  Timing.DataSetupTime = 18;
																							//  Timing.BusTurnAroundDuration = 3;
																							//  Timing.CLKDivision = 3;
																							//  Timing.DataLatency = 3;
																							//  Timing.AccessMode = FMC_ACCESS_MODE_A;
  /* ExtTiming */	

  HAL_SRAM_Init(&hsram2, &Timing, NULL);


	
	
	
	
	
	
}
	
static void Adgpio_Init(void )
{
	 GPIO_InitTypeDef GPIO_InitStruct;
	
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 __HAL_RCC_GPIOB_CLK_ENABLE();
	
	
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, AD_RESET_Pin|AD_CONVST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : AD_RESET_Pin AD_CONVST_Pin */
  GPIO_InitStruct.Pin = AD_RESET_Pin|AD_CONVST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
	
	AD_RESET_H();//
  /*Configure GPIO pin : AD_BUSY_Pin */
  GPIO_InitStruct.Pin = AD_BUSY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(AD_BUSY_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	AD_RESET_L();
	
	
}


//Ӳ����ʽ����CNA CNB   
//��ʱ��TIM1 CH1(PB13) ��ΪPWM����������崥��AD7606 CNA ��CNB�ź� 
//arr �Զ���װֵ
//psc	ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(u32 arr,u32 psc)
{
	  
 
	    htim1.Instance=TIM1;            //��ʱ��1
    htim1.Init.Prescaler=psc;       //��ʱ����Ƶ
    htim1.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    htim1.Init.Period=arr;          //�Զ���װ��ֵ
    htim1.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim1);       //��ʼ��PWM
    
    TIM1_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM1_CH1Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM1_CH1Handler.OCPolarity=TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&htim1,&TIM1_CH1Handler,TIM_CHANNEL_1);//����TIM3ͨ��4
	
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);//����PWMͨ��1
}

void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
 // HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
//	unsigned char temp,num;
////	 temp= ;
//	// if(BUSY_READ()==0)//����ת�����
//	// {
//		  for(num=0;num<AD7606_CHANNELNUM;num++)
//		  {
//				  AD7606.CHn[num][0]=  ( *((volatile u16 *) AD7606_ADDRBASE));
//	    }
//	    AD7606.Dat_Flg=1;
// //  }
//	 
//		EXTI->PR=1<<13;  //���LINE15�ϵ��жϱ�־λ 
	
HAL_GPIO_EXTI_IRQHandler(AD_BUSY_Pin);//�����жϴ����ú���

}


//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{   unsigned char temp,num;
   // delay_ms(100);      //����
    switch(GPIO_Pin)
    {
        case AD_BUSY_Pin:
								 if(BUSY_READ()==0)//����ת�����
								 {
										for(num=0;num<AD7606_CHANNELNUM;num++)
										{
												AD7606.CHn[num][0]=  ( *((volatile u16 *) AD7606_ADDRBASE));
										}
										AD7606.Dat_Flg=1;
							   }		
            break;
        case GPIO_PIN_2:
//            if(KEY1==0)  //LED1��ת
//            {
//                LED1=!LED1;    
//            }
            break;
        case GPIO_PIN_3:
//            if(KEY0==0)  //ͬʱ����LED0,LED1��ת 
//            {
//                LED0=!LED0;
//				LED1=!LED1;
//            }
            break;

        case GPIO_PIN_13:
//            if(KEY2==0)  
//            {
//				LED0=!LED0;//����LED0��ת
//            }
            break;
    }
}










