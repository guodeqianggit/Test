
#include "inc.h"

//////////////////////////////////////////////////////////////////////////////////	 
						  
////////////////////////////////////////////////////////////////////////////////// 	

//SPI_HandleTypeDef SPI5_Handler;  //SPI���
u8 Spi1_TxData[SPI_BUFSIZE], Spi1_Rxdata[SPI_BUFSIZE];
SPI_HandleTypeDef hspi1;
//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ 						  
//SPI�ڳ�ʼ��
//�������Ƕ�SPI5�ĳ�ʼ��

/* SPI1 init function */
void SPI1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_SPI1_CLK_ENABLE();
	
	  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_HARD_OUTPUT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  HAL_SPI_Init(&hspi1);
	

}



//void SPI5_Init(void)
//{
//    SPI5_Handler.Instance=SPI5;                         //SP5
//    SPI5_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
//    SPI5_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
//    SPI5_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
//    SPI5_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
//    SPI5_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
//    SPI5_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
//    SPI5_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
//    SPI5_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
//    SPI5_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
//    SPI5_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
//    SPI5_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
//    HAL_SPI_Init(&SPI5_Handler);//��ʼ��
//    
//    __HAL_SPI_ENABLE(&SPI5_Handler);                    //ʹ��SPI5
//	
//    SPI5_ReadWriteByte(0Xff);                           //��������
//}

//SPI5�ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_SPI_Init()����
//hspi:SPI���
//void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//{
//    GPIO_InitTypeDef GPIO_Initure;
//    
//    __HAL_RCC_GPIOF_CLK_ENABLE();       //ʹ��GPIOFʱ��
//    __HAL_RCC_SPI5_CLK_ENABLE();        //ʹ��SPI5ʱ��
//    
//    //PF7,8,9
//    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
//    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�����������
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //����
//    GPIO_Initure.Speed=GPIO_SPEED_FAST;             //����            
//    GPIO_Initure.Alternate=GPIO_AF5_SPI5;           //����ΪSPI5
//    HAL_GPIO_Init(GPIOF,&GPIO_Initure);
//}

//SPI�ٶ����ú���
//SPI�ٶ�=fAPB1/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
//fAPB1ʱ��һ��Ϊ45Mhz��
//void SPI5_SetSpeed(u8 SPI_BaudRatePrescaler)
//{
//    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
//    __HAL_SPI_DISABLE(&SPI5_Handler);            //�ر�SPI
//    SPI5_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
//    SPI5_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
//    __HAL_SPI_ENABLE(&SPI5_Handler);             //ʹ��SPI
//    
//}

//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
void  SPI1_ReadWriteByte(u16 DatNum)
{
   // u8 Rxdata;
    HAL_SPI_TransmitReceive(&hspi1,Spi1_TxData,Spi1_Rxdata,DatNum, 1000);       
 //	return Rxdata;          		    //�����յ�������		
}
