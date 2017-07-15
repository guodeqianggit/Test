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
  /*I2C0MasterWriteByte(0x10,0xD2);//WRTC1��1  д���� ���ھ����������ж�ѡ�񣬱����ж�����
    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3��1
    I2C0MasterWriteByte(0x11,0x00);//ARST��1
    I2C0MasterWriteByte(0x0E,0x01);//���ж�����
    I2C0MasterWriteByte(0x07,0x00);//���ж���ֵ00��*/

    

    I2C0MasterWriteByte(0x10,0xA9);//WRTC1��1,д��������ģʽ�ж�ѡ��ѡ��ΪƵ���ж� VBATģʽѡ�� Ƶ���ж�����0x10101001
    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3��1
    I2C0MasterWriteByte(0x11,0x8f);//ARST��1 ts3/2/1/0����Ƶ��Ϊ1HZ
    I2C0MasterWriteByte(0x14,0x01);//д��־λ
  
   /* I2C0MasterWriteByte(0x14,0x01);//д��־λ
    I2C0MasterWriteByte(0x10,0xA9);//WRTC1��1,д��������ģʽ�ж�ѡ��ѡ��ΪƵ���ж� VBATģʽѡ�� Ƶ���ж�����0x10101001
    I2C0MasterWriteByte(0x11,0x8f);//ARST��1 ts3/2/1/0����Ƶ��Ϊ1HZ
    I2C0MasterWriteByte(0x0F,0x84);//WRTC2,3��1*/
    
    itime[0]=I2C0MasterRedByte(0x14);
    itime[1]=I2C0MasterRedByte(0x10);
    itime[2]=I2C0MasterRedByte(0x11);
    itime[3]=I2C0MasterRedByte(0x0F);
     
   // I2C1MasterWriteByte(0x0F,0x00);//WRTC2,3��0  д��ֹ
   // I2C1MasterWriteByte(0x10,0x52);//WRTC1��0
}
/******************************************************************************/

void  Calendar_Init()
{
    Int8U data[7] = {0x00,0x52,0x89,0x04,0x01,0x06,0x17};//�� �� ʱ ���� �� �� ��
    Int8U fig;
		fig = fig;
    fig = I2C0MasterRedByte(0x14);//��״̬�Ĵ���
    if(fig == 0x01);
    else
    {
      I2C0MasterWriteByte(0x14,0x01); 
      I2C0MasterWrite(0x00,data,7);//��ʼ����д��Ĵ���
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
        

void fhzgettime()//��ȡʱ��
{
        fhzJL[fhz_point].Sec= Second_1;//����
        fhzJL[fhz_point].Min  = Minute_1;//����
        fhzJL[fhz_point].hour = Hour_1;//��ʱ
        fhzJL[fhz_point].day = Day_1;//��ri
        fhzJL[fhz_point].month = Month_1;//��yur
        fhzJL[fhz_point].year = Year_1;
        fhzJL[fhz_point].Msec = Dlytime1;
        fhzJL[fhz_point].Msecl = ((fhzJL[fhz_point].Sec*1000)+fhzJL[fhz_point].Msec)&0x00ff;
        fhzJL[fhz_point].Msech = (((fhzJL[fhz_point].Sec*1000)+fhzJL[fhz_point].Msec)>>8)&0x00ff;

}


void readtime(void)//��ȡʱ��
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

/**************************GPIO�ж����ų�ʼ��**********************************/
/*void GpioEventInit()
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource9);//PE9 ���ӵ��ж���9
	

	
	///* ����EXTI_Line9 
	EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
}*/

void GpioEventInit()
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//	

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource3);//	

	
	/* ����EXTI_Line9 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//  
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//  
	EXTI_Init(&EXTI_InitStructure);//
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//�ⲿ�ж�4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//��ռ���ȼ�3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	
}


/********************�ж���ں���*********************************************/
Int8U Second_1,Minute_1,Hour_1,Week_1,Day_1,Month_1,Year_1,ReadTimeFlag;
 
void EXTI3_IRQHandler()
//void EXTI9_5_IRQHandler()//PE9  ���ж�
{

  //  EXTI_ClearITPendingBit(EXTI_Line9); //���LINE9�ϵ��жϱ�־λ 
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

