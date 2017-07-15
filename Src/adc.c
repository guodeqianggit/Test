#include "inc.h"
//#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//ADC驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

ADC_HandleTypeDef ADC3_Handler;//ADC句柄
//ADC_HandleTypeDef hadc3;
//初始化ADC
//ch: ADC_channels 
//通道值 0~16取值范围为：ADC_CHANNEL_0~ADC_CHANNEL_16
void MY_ADC_Init(void)
{   
	
  ADC_ChannelConfTypeDef ADC3_ChanConf;
	
    ADC3_Handler.Instance=ADC3;
    ADC3_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;   //4分频，ADCCLK=PCLK2/4=90/4=22.5MHZ
    ADC3_Handler.Init.Resolution=ADC_RESOLUTION_12B;             //12位模式
    ADC3_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //右对齐
    ADC3_Handler.Init.ScanConvMode=DISABLE;                      //非扫描模式
    ADC3_Handler.Init.EOCSelection=DISABLE;                      //关闭EOC中断
    ADC3_Handler.Init.ContinuousConvMode=DISABLE;                //关闭连续转换
    ADC3_Handler.Init.NbrOfConversion=1;                         //1个转换在规则序列中 也就是只转换规则序列1 
    ADC3_Handler.Init.DiscontinuousConvMode=DISABLE;             //禁止不连续采样模式
    ADC3_Handler.Init.NbrOfDiscConversion=0;                     //不连续采样通道数为0
    ADC3_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //软件触发
    ADC3_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//使用软件触发
    ADC3_Handler.Init.DMAContinuousRequests=DISABLE;             //关闭DMA请求
    HAL_ADC_Init(&ADC3_Handler);           

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
//  hadc3.Instance = ADC3;
//  hadc3.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
//  hadc3.Init.Resolution = ADC_RESOLUTION_12B;
//  hadc3.Init.ScanConvMode = DISABLE;
//  hadc3.Init.ContinuousConvMode = DISABLE;
//  hadc3.Init.DiscontinuousConvMode = DISABLE;
//  hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
//  hadc3.Init.DataAlign = ADC_DATAALIGN_RIGHT;
//  hadc3.Init.NbrOfConversion = 1;
//  hadc3.Init.DMAContinuousRequests = DISABLE;
//  hadc3.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
//  HAL_ADC_Init(&hadc3);

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
//  sConfig.Channel = ADC_CHANNEL_7;
// sConfig.Rank = 1;
// sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
// HAL_ADC_ConfigChannel(&ADC3_Handler, &sConfig);
//    ADC3_ChanConf.Channel=ADC_CHANNEL_7;                                   //通道
//    ADC3_ChanConf.Rank=1;                                       //第1个序列，序列1
//    ADC3_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //采样时间
//    ADC3_ChanConf.Offset=0;                 
//    HAL_ADC_ConfigChannel(&ADC3_Handler,&ADC3_ChanConf);        //通道配置

	//初始化 
}

//ADC底层驱动，引脚配置，时钟使能
//此函数会被HAL_ADC_Init()调用
//hadc:ADC句柄
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC3_CLK_ENABLE();            //使能ADC3时钟
    __HAL_RCC_GPIOF_CLK_ENABLE();			//开启GPIOA时钟
	
    GPIO_Initure.Pin=GPIO_PIN_9;            //PF9
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //模拟
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
}

//获得ADC值
//ch: 通道值 0~16，取值范围为：ADC_CHANNEL_0~ADC_CHANNEL_16
//返回值:转换结果
u16 Get_Adc(u32 ch)   
{
    ADC_ChannelConfTypeDef ADC3_ChanConf;
    
    ADC3_ChanConf.Channel=ch;                                   //通道
    ADC3_ChanConf.Rank=1;                                       //第1个序列，序列1
    ADC3_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //采样时间
    ADC3_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&ADC3_Handler,&ADC3_ChanConf);        //通道配置
	
    HAL_ADC_Start(&ADC3_Handler);                               //开启ADC
	
    HAL_ADC_PollForConversion(&ADC3_Handler,10);                //轮询转换
 
	return (u16)HAL_ADC_GetValue(&ADC3_Handler);	        //返回最近一次ADC1规则组的转换结果
}
//获取指定通道的转换值，取times次,然后平均 
//times:获取次数
//返回值:通道ch的times次转换结果平均值
u16 Get_Adc_Average(u32 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
