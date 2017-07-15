#include "inc.h"
DEVICE_STUS Fram_Init (void);

void Read_FramId (void);
 DEVICE_STUS Fram_Init (void)
 {
	    DEVICE_STUS Fram_Stus;
	 
	    SPI1_Init();//³õÊ¼»¯SPI¿Ú
	    
	 
 }


 void Read_FramId (void)
 {
    Spi1_TxData[0]=0x9f;
	  Spi1_TxData[1]=0x00; 
	  Spi1_TxData[2]=0x00; 
	  Spi1_TxData[3]=0x00; 
	  Spi1_TxData[4]=0x00;  
	  Spi1_TxData[5]=0x00; 
	  Spi1_TxData[6]=0x00; 
	  Spi1_TxData[7]=0x00; 
	  Spi1_TxData[8]=0x00; 
	  Spi1_TxData[9]=0x00;	 
	  SPI1_ReadWriteByte(10);
	 
 }
 

