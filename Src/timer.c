
#include "inc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

////////////////////////////////////////////////////////////////////////////////// 

 void Dc1_Gather_Deal(void);
CAP_STURCT   Fre_Gather,Dc1_Gather; 
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef TIM3_Handler,TIM4_Handler;      //定时器句柄 

unsigned int temp2;
extern unsigned char led_flg;
/* TIM2 通道3 输入捕获 init function */
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





//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK/2)
void TIM3_Init(u16 arr,u16 psc)
{  
    TIM3_Handler.Instance=TIM3;                          //通用定时器3
    TIM3_Handler.Init.Prescaler=psc;                     //分频系数
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM3_Handler.Init.Period=arr;                        //自动装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM3_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}


void TIM4_Init(u16 arr,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                          //通用定时器4
    TIM4_Handler.Init.Prescaler=psc;                     //分频系数
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM4_Handler.Init.Period=arr;                        //自动装载值
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM4_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}


//定时器底册驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance==TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM3_IRQn,3,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM3_IRQn);          //开启ITM3中断   
	}
  
	if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //使能TIM4时钟
		HAL_NVIC_SetPriority(TIM4_IRQn,3,5);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //开启ITM4中断   
	}
		
}


//定时器3中断服务函数
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

//回调函数，定时器中断服务函数调用
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
  下面是输入捕获相关源码实验相关函数源码
****************************************************************************
****************************************************************************/


TIM_HandleTypeDef TIM13_Handler;         //定时器5句柄


//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM13_CH1_Cap_Init(u32 arr,u16 psc)
{  
    TIM_IC_InitTypeDef TIM13_CH1Config;  
    
    TIM13_Handler.Instance=TIM13;                          //通用定时器13
    TIM13_Handler.Init.Prescaler=psc;                     //分频系数,看RCC手册确定输入时钟
    TIM13_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM13_Handler.Init.Period=arr;                        //自动装载值
    TIM13_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频银子
    HAL_TIM_IC_Init(&TIM13_Handler);//初始化输入捕获时基参数，就是基本的定时器参数
    
    TIM13_CH1Config.ICPolarity=TIM_ICPOLARITY_RISING;    //上升沿捕获，捕获极性
    TIM13_CH1Config.ICSelection=TIM_ICSELECTION_DIRECTTI;//映射到TI1上，映射到TI1
    TIM13_CH1Config.ICPrescaler=TIM_ICPSC_DIV1;          //配置输入分频，不分频，每个上升沿都会捕获
    TIM13_CH1Config.ICFilter=0;                          //配置输入滤波器，不滤波
    HAL_TIM_IC_ConfigChannel(&TIM13_Handler,&TIM13_CH1Config,TIM_CHANNEL_1);//配置TIM5通道1
	
    HAL_TIM_IC_Start_IT(&TIM13_Handler,TIM_CHANNEL_1);   //开启TIM5的捕获通道1，并且开启捕获中断
    //__HAL_TIM_ENABLE_IT(&TIM13_Handler,TIM_IT_UPDATE);   //使能更新中断,不使用更新中断，因为定时器预装值已经足够大了
	                                                        //所谓更新中断就是普通的中断处理函数
}



 void Fre_Gather_Init(void)
 {  u8 temp;
	  Fre_Gather.Type= FRE_CAP;
	  Fre_Gather.flg=0;//从未采集过数据
	  Fre_Gather.Cur_Value=0;
	  Fre_Gather.Second_Value=0;
	  Fre_Gather.P_Write=0;
	  for(temp=0;temp<CAP_NUM ;temp++)//初始化
	  {
	     Fre_Gather.dat[temp]=0;
		}
		
		
 }
 
  void Dc1_Gather_Init(void)
 {  u8 temp;
	  Dc1_Gather.Type= DC1_CAP;
	  Dc1_Gather.flg=0;//从未采集过数据
	  Dc1_Gather.Cur_Value=0;
	  Dc1_Gather.Second_Value=0;
	  Dc1_Gather.P_Write=0;
	  Dc1_Gather.Gather_Num=0;//获得数据个数，够CAP_NUM才进行转换
	  for(temp=0;temp<CAP_NUM ;temp++)//初始化
	  {
	     Dc1_Gather.dat[temp]=0;
		}
		
		
 }
 
 void Dc1_Gather_Deal(void)
 {  
	  u8 temp;
	 // u32 temp2;
	  if( Dc1_Gather.flg)//如果以前已经采集过数据
		{
			 Dc1_Gather.Second_Value= HAL_TIM_ReadCapturedValue(&TIM13_Handler,TIM_CHANNEL_1);//获取当前的捕获值.
		//	 temp2=  (Dc1_Gather.Second_Value - Dc1_Gather.Cur_Value);
			 if(Dc1_Gather.Second_Value > Dc1_Gather.Cur_Value)//如果在一个周期内
			 {
				   Dc1_Gather.dat[Dc1_Gather.P_Write&0x07]= Dc1_Gather.Second_Value - Dc1_Gather.Cur_Value;
				   Dc1_Gather.P_Write++;
				   if(Dc1_Gather.Gather_Num < CAP_NUM)//如果采集数据小于缓存容量，也就是缓存中有空数据
				   {
						 Dc1_Gather.Gather_Num++;
					 }
					 Dc1_Gather.Cur_Value=Dc1_Gather.Second_Value;
					 
			 }else//如果跨周期
			 {
				 
				   temp2= 0xffff - Dc1_Gather.Cur_Value; 
			     Dc1_Gather.dat[Dc1_Gather.P_Write&0x07]= temp2 + Dc1_Gather.Second_Value;
				   Dc1_Gather.P_Write++;
				   if(Dc1_Gather.Gather_Num < CAP_NUM)//如果采集数据小于缓存容量，也就是缓存中有空数据
				   {
						 Dc1_Gather.Gather_Num++;
					 } 
				   Dc1_Gather.Cur_Value=Dc1_Gather.Second_Value;
				 
			 }
			 if(Dc1_Gather.Gather_Num >= CAP_NUM)//如果数据缓存中数据全是有效数据
			 {
				   for(temp=0;temp< CAP_NUM;temp++)
				   {
						  Dc1_Gather.Fre_Value+= Dc1_Gather.dat[temp];
						 
					 }
					 Dc1_Gather.Fre_Value= (Dc1_Gather.Fre_Value /( CAP_NUM * 1000));//频率100倍上送
				   Dc1_Gather.Gather_Num=0;
			 }
			 
			
		}else//从未采集过数据,将数据保存到第一当前数据中
		{
			
			  Dc1_Gather.Cur_Value= HAL_TIM_ReadCapturedValue(&TIM13_Handler,TIM_CHANNEL_1);//获取当前的捕获值.
			  Dc1_Gather.flg=1;
		}

		
 }
 
 
//定时器5底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_IC_Init()调用
//htim:定时器5句柄
void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
	
	 // if(htim->Instance== TIM13){
					__HAL_RCC_TIM13_CLK_ENABLE();            //使能TIM13时钟
					__HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOF时钟
				
					GPIO_Initure.Pin=GPIO_PIN_8;            //PF8
					GPIO_Initure.Mode=GPIO_MODE_AF_PP;      //复用推挽输出
					GPIO_Initure.Pull=GPIO_PULLUP ;        //下拉GPIO_PULLDOWN GPIO_PULLUP 
					GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
					GPIO_Initure.Alternate=GPIO_AF9_TIM13;   //PF8复用为TIM13通道1
					HAL_GPIO_Init(GPIOF,&GPIO_Initure);

					HAL_NVIC_SetPriority( TIM8_UP_TIM13_IRQn,0,0);    //设置中断优先级，抢占优先级2，子优先级0
					HAL_NVIC_EnableIRQ( TIM8_UP_TIM13_IRQn );          //开启ITM13中断，这是为了防止脉冲频率过低设置的
			
	//	}
		
		
}


//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)


//定时器5中断服务函数
//void TIM5_IRQHandler(void)
void TIM8_UP_TIM13_IRQHandler (void)
{
	HAL_TIM_IRQHandler(&TIM13_Handler);//定时器共用处理函数
}
 

//定时器更新中断（计数溢出）中断处理回调函数， 该函数在HAL_TIM_IRQHandler中会被调用
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//更新中断（溢出）发生时执行
//{
//	
//	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
//	{
//			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
//			{
//				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
//				{
//					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
//					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
//				}else TIM5CH1_CAPTURE_STA++;
//			}	 
//	}		
//}


//定时器输入捕获中断处理回调函数，该函数在HAL_TIM_IRQHandler中会被调用
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//捕获中断发生时执行
{
	
	 if(htim->Instance== TIM13)//DC1采集频率捕获
	 {
   
		  Dc1_Gather_Deal( );//处理频率
		 
	 }
   		 
	
	
//	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获
//	{
//		if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
//			{	  			
//				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
//                TIM5CH1_CAPTURE_VAL=HAL_TIM_ReadCapturedValue(&TIM5_Handler,TIM_CHANNEL_1);//获取当前的捕获值.
//                TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
//                TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_RISING);//配置TIM5通道1上升沿捕获
//			}else  								//还未开始,第一次捕获上升沿
//			{
//				TIM5CH1_CAPTURE_STA=0;			//清空
//				TIM5CH1_CAPTURE_VAL=0;
//				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
//				__HAL_TIM_DISABLE(&TIM5_Handler);        //关闭定时器5
//				__HAL_TIM_SET_COUNTER(&TIM5_Handler,0);
//				TIM_RESET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1);   //一定要先清除原来的设置！！
//				TIM_SET_CAPTUREPOLARITY(&TIM5_Handler,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);//定时器5通道1设置为下降沿捕获
//				__HAL_TIM_ENABLE(&TIM5_Handler);//使能定时器5
//			}		    
//	}		
	
}



