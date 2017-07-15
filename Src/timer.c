
#include "inc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

////////////////////////////////////////////////////////////////////////////////// 

 void Dc1_Gather_Deal(void);
CAP_STURCT   Fre_Gather,Dc1_Gather; 
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef TIM3_Handler,TIM4_Handler;      //��ʱ����� 

unsigned int temp2;
extern unsigned char led_flg;
/* TIM2 ͨ��3 ���벶�� init function */
void TIM2_CH3_Cap_Init(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;
  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_IC_InitTypeDef sConfigIC;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  HAL_TIM_IC_Init(&htim2);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_3);
	
	
	  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();
  
    /**TIM2 GPIO Configuration    
    PB10     ------> TIM2_CH3 
    */
    GPIO_InitStruct.Pin = CF1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
    HAL_GPIO_Init(CF1_GPIO_Port, &GPIO_InitStruct);

    /* Peripheral interrupt init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 2, 4);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
		
		

}


void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}





//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ��,��λ:Mhz
//����ʹ�õ��Ƕ�ʱ��3!(��ʱ��3����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM3_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}


void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                          //ͨ�ö�ʱ��4
    TIM4_Handler.Init.Prescaler=psc;                     //��Ƶϵ��
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM4_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM4_Handler); //ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE   
}


//��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
//�˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //ʹ��TIM3ʱ��
		HAL_NVIC_SetPriority(TIM3_IRQn,3,3);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //����ITM3�ж�   
	}
  
	if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //ʹ��TIM4ʱ��
		HAL_NVIC_SetPriority(TIM4_IRQn,3,5);    //�����ж����ȼ�����ռ���ȼ�1�������ȼ�3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //����ITM4�ж�   
	}
		
}


//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
	 // HAL_TIM_IRQHandler(&TIM4_Handler);
}

void TIM4_IRQHandler(void)
{
   // HAL_TIM_IRQHandler(&TIM3_Handler);
	  HAL_TIM_IRQHandler(&TIM4_Handler);
}

//�ص���������ʱ���жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{   temp2++;
    if(htim==(&TIM3_Handler))
    {
     
//        if(temp2>1000)
//				{
//					
//					   if(led_flg==0)
//						 {
//							  led_flg=1;
//						 }else 
//						 {
//							 led_flg=0;
//						 }
//							temp2=0; 
//				 }	 
			   			
    }
		
    if(htim==(&TIM4_Handler))
    {
     
        if(temp2>1000)
				{
					
					   if(led_flg==0)
						 {
							  led_flg=1;
						 }else 
						 {
							 led_flg=0;
						 }
							temp2=0; 
				 }	 
			   			
    }		
		
		
}


/***************************************************************************
****************************************************************************
  ���������벶�����Դ��ʵ����غ���Դ��
****************************************************************************
****************************************************************************/


TIM_HandleTypeDef TIM13_Handler;         //��ʱ��5���


//��ʱ��5ͨ��1���벶������
//arr���Զ���װֵ(TIM2,TIM5��32λ��!!)
//psc��ʱ��Ԥ��Ƶ��
void TIM13_CH1_Cap_Init(u32 arr,u16 psc)
{  
    TIM_IC_InitTypeDef TIM13_CH1Config;  
    
    TIM13_Handler.Instance=TIM13;                          //ͨ�ö�ʱ��13
    TIM13_Handler.Init.Prescaler=psc;                     //��Ƶϵ��,��RCC�ֲ�ȷ������ʱ��
    TIM13_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //���ϼ�����
    TIM13_Handler.Init.Period=arr;                        //�Զ�װ��ֵ
    TIM13_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//ʱ�ӷ�Ƶ����
    HAL_TIM_IC_Init(&TIM13_Handler);//��ʼ�����벶��ʱ�����������ǻ����Ķ�ʱ������
    
    TIM13_CH1Config.ICPolarity=TIM_ICPOLARITY_RISING;    //�����ز��񣬲�����
    TIM13_CH1Config.ICSelection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1�ϣ�ӳ�䵽TI1
    TIM13_CH1Config.ICPrescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ��ÿ�������ض��Ჶ��
    TIM13_CH1Config.ICFilter=0;                          //���������˲��������˲�
    HAL_TIM_IC_ConfigChannel(&TIM13_Handler,&TIM13_CH1Config,TIM_CHANNEL_1);//����TIM5ͨ��1
	
    HAL_TIM_IC_Start_IT(&TIM13_Handler,TIM_CHANNEL_1);   //����TIM5�Ĳ���ͨ��1�����ҿ��������ж�
    //__HAL_TIM_ENABLE_IT(&TIM13_Handler,TIM_IT_UPDATE);   //ʹ�ܸ����ж�,��ʹ�ø����жϣ���Ϊ��ʱ��Ԥװֵ�Ѿ��㹻����
	                                                        //��ν�����жϾ�����ͨ���жϴ�����
}



 void Fre_Gather_Init(void)
 {  u8 temp;
	  Fre_Gather.Type= FRE_CAP;
	  Fre_Gather.flg=0;//��δ�ɼ�������
	  Fre_Gather.Cur_Value=0;
	  Fre_Gather.Second_Value=0;
	  Fre_Gather.P_Write=0;
	  for(temp=0;temp<CAP_NUM ;temp++)//��ʼ��
	  {
	     Fre_Gather.dat[temp]=0;
		}
		
		
 }
 
  void Dc1_Gather_Init(void)
 {  u8 temp;
	  Dc1_Gather.Type= DC1_CAP;
	  Dc1_Gather.flg=0;//��δ�ɼ�������
	  Dc1_Gather.Cur_Value=0;
	  Dc1_Gather.Second_Value=0;
	  Dc1_Gather.P_Write=0;
	  Dc1_Gather.Gather_Num=0;//������ݸ�������CAP_NUM�Ž���ת��
	  for(temp=0;temp<CAP_NUM ;temp++)//��ʼ��
	  {
	     Dc1_Gather.dat[temp]=0;
		}
		
		
 }
 
 void Dc1_Gather_Deal(void)
 {  
	  u8 temp;
	 // u32 temp2;
	  if( Dc1_Gather.flg)//�����ǰ�Ѿ��ɼ�������
		{
			 Dc1_Gather.Second_Value= HAL_TIM_ReadCapturedValue(&TIM13_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
		//	 temp2=  (Dc1_Gather.Second_Value - Dc1_Gather.Cur_Value);
			 if(Dc1_Gather.Second_Value > Dc1_Gather.Cur_Value)//�����һ��������
			 {
				   Dc1_Gather.dat[Dc1_Gather.P_Write&0x07]= Dc1_Gather.Second_Value - Dc1_Gather.Cur_Value;
				   Dc1_Gather.P_Write++;
				   if(Dc1_Gather.Gather_Num < CAP_NUM)//����ɼ�����С�ڻ���������Ҳ���ǻ������п�����
				   {
						 Dc1_Gather.Gather_Num++;
					 }
					 Dc1_Gather.Cur_Value=Dc1_Gather.Second_Value;
					 
			 }else//���������
			 {
				 
				   temp2= 0xffff - Dc1_Gather.Cur_Value; 
			     Dc1_Gather.dat[Dc1_Gather.P_Write&0x07]= temp2 + Dc1_Gather.Second_Value;
				   Dc1_Gather.P_Write++;
				   if(Dc1_Gather.Gather_Num < CAP_NUM)//����ɼ�����С�ڻ���������Ҳ���ǻ������п�����
				   {
						 Dc1_Gather.Gather_Num++;
					 } 
				   Dc1_Gather.Cur_Value=Dc1_Gather.Second_Value;
				 
			 }
			 if(Dc1_Gather.Gather_Num >= CAP_NUM)//������ݻ���������ȫ����Ч����
			 {
				   for(temp=0;temp< CAP_NUM;temp++)
				   {
						  Dc1_Gather.Fre_Value+= Dc1_Gather.dat[temp];
						 
					 }
					 Dc1_Gather.Fre_Value= (Dc1_Gather.Fre_Value /( CAP_NUM * 1000));//Ƶ��100������
				   Dc1_Gather.Gather_Num=0;
			 }
			 
			
		}else//��δ�ɼ�������,�����ݱ��浽��һ��ǰ������
		{
			
			  Dc1_Gather.Cur_Value= HAL_TIM_ReadCapturedValue(&TIM13_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
			  Dc1_Gather.flg=1;
		}

		
 }
 
 
//��ʱ��5�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_IC_Init()����
//htim:��ʱ��5���
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	
	 // if(htim->Instance== TIM13){
					__HAL_RCC_TIM13_CLK_ENABLE();            //ʹ��TIM13ʱ��
					__HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOFʱ��
				
					GPIO_Initure.Pin=GPIO_PIN_8;            //PF8
					GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //�����������
					GPIO_Initure.Pull=GPIO_PULLUP ;        //����GPIO_PULLDOWN GPIO_PULLUP 
					GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
					GPIO_Initure.Alternate=GPIO_AF9_TIM13;   //PF8����ΪTIM13ͨ��1
					HAL_GPIO_Init(GPIOF,&GPIO_Initure);

					HAL_NVIC_SetPriority( TIM8_UP_TIM13_IRQn,0,0);    //�����ж����ȼ�����ռ���ȼ�2�������ȼ�0
					HAL_NVIC_EnableIRQ( TIM8_UP_TIM13_IRQn );          //����ITM13�жϣ�����Ϊ�˷�ֹ����Ƶ�ʹ������õ�
			
	//	}
		
		
}


//����״̬
//[7]:0,û�гɹ��Ĳ���;1,�ɹ�����һ��.
//[6]:0,��û���񵽵͵�ƽ;1,�Ѿ����񵽵͵�ƽ��.
//[5:0]:����͵�ƽ������Ĵ���(����32λ��ʱ����˵,1us��������1,���ʱ��:4294��)
u8  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
u32	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ(TIM2/TIM5��32λ)


//��ʱ��5�жϷ�����
//void TIM5_IRQHandler(void)
void TIM8_UP_TIM13_IRQHandler (void)
{
	HAL_TIM_IRQHandler(&TIM13_Handler);//��ʱ�����ô�����
}
 

//��ʱ�������жϣ�����������жϴ���ص������� �ú�����HAL_TIM_IRQHandler�лᱻ����
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//�����жϣ����������ʱִ��
//{
//	
//	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
//	{
//			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽸ߵ�ƽ��
//			{
//				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�ߵ�ƽ̫����
//				{
//					TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�������һ��
//					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
//				}else TIM5CH1_CAPTURE_STA++;
//			}	 
//	}		
//}


//��ʱ�����벶���жϴ���ص��������ú�����HAL_TIM_IRQHandler�лᱻ����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//�����жϷ���ʱִ��
{
	
	 if(htim->Instance== TIM13)//DC1�ɼ�Ƶ�ʲ���
	 {
   
		  Dc1_Gather_Deal( );//����Ƶ��
		 
	 }
   		 
	
	
//	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����
//	{
//		if(TIM5CH1_CAPTURE_STA&0X40)		//����һ���½��� 		
//			{	  			
//				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
//                TIM5CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM5_Handler,TIM_CHANNEL_1);//��ȡ��ǰ�Ĳ���ֵ.
//                TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
//                TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//����TIM5ͨ��1�����ز���
//			}else  								//��δ��ʼ,��һ�β���������
//			{
//				TIM5CH1_CAPTURE_STA=0;			//���
//				TIM5CH1_CAPTURE_VAL=0;
//				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
//				__HAL_TIM_DISABLE(&TIM5_Handler);        //�رն�ʱ��5
//				__HAL_TIM_SET_COUNTER(&TIM5_Handler,0);
//				TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);   //һ��Ҫ�����ԭ�������ã���
//				TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//��ʱ��5ͨ��1����Ϊ�½��ز���
//				__HAL_TIM_ENABLE(&TIM5_Handler);//ʹ�ܶ�ʱ��5
//			}		    
//	}		
	
}



