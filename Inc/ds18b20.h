#ifndef __DS18B20_H
#define __DS18B20_H 
#include "inc.h"   

// extern short temperature;

//IO��������
#define DS18B20_IO_IN()  {GPIOA->MODER&=~(3<<(8*2));GPIOA->MODER|=0<<8*2;}	//PA8����ģʽ
#define DS18B20_IO_OUT() {GPIOA->MODER&=~(3<<(8*2));GPIOA->MODER|=1<<8*2;} 	//PA8���ģʽ
 
////IO��������											   
#define	DS18B20_DQ_OUT PAout(8) //���ݶ˿�	PA8
#define	DS18B20_DQ_IN  PAin(8)  //���ݶ˿�	PA8
   	
extern u8 DS18B20_Init(void);			//��ʼ��DS18B20
extern short DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    
#endif














