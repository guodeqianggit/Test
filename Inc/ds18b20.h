#ifndef __DS18B20_H
#define __DS18B20_H 
#include "inc.h"   

// extern short temperature;

//IO方向设置
#define DS18B20_IO_IN()  {GPIOA->MODER&=~(3<<(8*2));GPIOA->MODER|=0<<8*2;}	//PA8输入模式
#define DS18B20_IO_OUT() {GPIOA->MODER&=~(3<<(8*2));GPIOA->MODER|=1<<8*2;} 	//PA8输出模式
 
////IO操作函数											   
#define	DS18B20_DQ_OUT PAout(8) //数据端口	PA8
#define	DS18B20_DQ_IN  PAin(8)  //数据端口	PA8
   	
extern u8 DS18B20_Init(void);			//初始化DS18B20
extern short DS18B20_Get_Temp(void);	//获取温度
void DS18B20_Start(void);		//开始温度转换
void DS18B20_Write_Byte(u8 dat);//写入一个字节
u8 DS18B20_Read_Byte(void);		//读出一个字节
u8 DS18B20_Read_Bit(void);		//读出一个位
u8 DS18B20_Check(void);			//检测是否存在DS18B20
void DS18B20_Rst(void);			//复位DS18B20    
#endif















