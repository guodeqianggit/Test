#include "includes.h"
#include "stm32f4xx_conf.h"
#include "system_stm32f4xx.h"
#include "delay.h"


extern Int16U Dlytime1;
extern EVENTTRU m_objReguTime[];
extern unsigned int event_point;

    Int16U itime[15];
void SD2405_Init()
{
  /*I2C0MasterWriteByte(0x10,0xD2);//WRTC1置1  写允许 周期警报，报警中断选择，报警中断允许
    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3置1
    I2C0MasterWriteByte(0x11,0x00);//ARST置1
    I2C0MasterWriteByte(0x0E,0x01);//秒中断允许
    I2C0MasterWriteByte(0x07,0x00);//秒中断数值00秒*/

    

    I2C0MasterWriteByte(0x10,0xA9);//WRTC1置1,写允许，报警模式中断选择，选择为频率中断 VBAT模式选择 频率中断允许0x10101001
    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3置1
    I2C0MasterWriteByte(0x11,0x8f);//ARST置1 ts3/2/1/0设置频率为1HZ
    I2C0MasterWriteByte(0x14,0x01);//写标志位
  
   /* I2C0MasterWriteByte(0x14,0x01);//写标志位
    I2C0MasterWriteByte(0x10,0xA9);//WRTC1置1,写允许，报警模式中断选择，选择为频率中断 VBAT模式选择 频率中断允许0x10101001
    I2C0MasterWriteByte(0x11,0x8f);//ARST置1 ts3/2/1/0设置频率为1HZ
    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3置1*/
    
    itime[0]=I2C0MasterRedByte(0x14);
    itime[1]=I2C0MasterRedByte(0x10);
    itime[2]=I2C0MasterRedByte(0x11);
    itime[3]=I2C0MasterRedByte(0x0F);
     
   // I2C1MasterWriteByte(0x0F,0x00);//WRTC2,3置0  写禁止
   // I2C1MasterWriteByte(0x10,0x52);//WRTC1置0
}
/******************************************************************************/

void  Calendar_Init()
{
    Int8U data[7] = {0x00,0x52,0x89,0x04,0x01,0x06,0x17};//秒 分 时 星期 日 月 年
    Int8U fig;
		fig = fig;
    fig = I2C0MasterRedByte(0x14);//读状态寄存器
    if(fig == 0x01);
    else
    {
      I2C0MasterWriteByte(0x14,0x01); 
      I2C0MasterWrite(0x00,data,7);//起始日历写入寄存器
		//  I2C0MasterWriteByte(0x06,0x14);
    }
    
//   itime[5] = I2C0MasterRedByte(0x00);
//   itime[6] = I2C0MasterRedByte(0x01);
//   itime[7] = I2C0MasterRedByte(0x02);
//   itime[8] = I2C0MasterRedByte(0x03);
//   itime[9] = I2C0MasterRedByte(0x04);
//   itime[10] = I2C0MasterRedByte(0x05);
//   itime[11] = I2C0MasterRedByte(0x06);
   
}


Int8U turntime(Int8U time)
{
   Int8U ReadFig ,ReadFigH,ReadFigL,retime;
   
   ReadFig = time;
   ReadFigL = ReadFig & 0x0F;
   ReadFigH = (ReadFig>>4)&0x07;
   retime = ReadFigH *10 + ReadFigL;
   
   return(retime);
}
        

void fhzgettime()//获取时间
{
        fhzJL[fhz_point].Sec= Second_1;//读秒
        fhzJL[fhz_point].Min  = Minute_1;//读分
        fhzJL[fhz_point].hour = Hour_1;//读时
        fhzJL[fhz_point].day = Day_1;//读ri
        fhzJL[fhz_point].month = Month_1;//读yur
        fhzJL[fhz_point].year = Year_1;
        fhzJL[fhz_point].Msec = Dlytime1;
        fhzJL[fhz_point].Msecl = ((fhzJL[fhz_point].Sec*1000)+fhzJL[fhz_point].Msec)&0x00ff;
        fhzJL[fhz_point].Msech = (((fhzJL[fhz_point].Sec*1000)+fhzJL[fhz_point].Msec)>>8)&0x00ff;

}


void readtime(void)//获取时间
{
    Second_1 = turntime(I2C0MasterRedByte(0x00));
    Minute_1 = turntime(I2C0MasterRedByte(0x01));
    Hour_1 = turntime(I2C0MasterRedByte(0x02));
    Week_1 = turntime(I2C0MasterRedByte(0x03));
    Day_1 = turntime(I2C0MasterRedByte(0x04));
    Month_1 = turntime(I2C0MasterRedByte(0x05));
    Year_1 = I2C0MasterRedByte(0x06);
	  Year_1 = turntime(I2C0MasterRedByte(0x06));
}

/**************************GPIO中断引脚初始化**********************************/
/*void GpioEventInit()
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PE9 连接到中断线9
	

	
	///* 配置EXTI_Line9 
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
}*/

void GpioEventInit()
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//	

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);//	

	
	/* 配置EXTI_Line9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//  
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//  
	EXTI_Init(&EXTI_InitStructure);//
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
}


/********************中断入口函数*********************************************/
Int8U Second_1,Minute_1,Hour_1,Week_1,Day_1,Month_1,Year_1,ReadTimeFlag;
 
void EXTI3_IRQHandler()
//void EXTI9_5_IRQHandler()//PE9  秒中断
{

  //  EXTI_ClearITPendingBit(EXTI_Line9); //清除LINE9上的中断标志位 
	EXTI_ClearITPendingBit(EXTI_Line3); 

    sd2405sec = 1;
    
    Dlytime1 = 0;
    Second_1++;
    if(Second_1>59)
    {
      Second_1=0;
      Minute_1++;
    }
    if(Minute_1>59)
    {
      Minute_1=0;
      Hour_1++;
    }
    if(Hour_1>23)
    {
      Hour_1=0;
      ReadTimeFlag=1;
    }
    
}

