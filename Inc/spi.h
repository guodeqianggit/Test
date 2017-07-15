#ifndef __SPI_H
#define __SPI_H
#include "stm32f4xx_hal.h"
#include "type.h"
//////////////////////////////////////////////////////////////////////////////////	 

//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#define SPI_BUFSIZE 0x100

extern  u8 Spi1_TxData[SPI_BUFSIZE], Spi1_Rxdata[SPI_BUFSIZE];

extern SPI_HandleTypeDef hspi1;  //SPI¾ä±ú

extern  void SPI1_Init(void);
extern  void SPI1_ReadWriteByte(u16 DatNum); 
#endif
