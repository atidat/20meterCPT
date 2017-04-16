#include "headers.h"



void SPI_Initialize(void)
{
			SPI_InitTypeDef  SPIx_InitStructure;
			GPIO_InitTypeDef  GPIO_InitStructure;

	
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE );	
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE );

			/*!< Config SPI2 SCK pin:PB13		*/
			GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			/*!< Config SPI2 MOSI pin:PB15		*/
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			
			/*!< Config SPI2 MISO pin:PB14,shoud I set the MISO pin as GPIO_Mode_IN_FLOATING */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			
			/*!< Config SPI2 CS pin:PB12 (there is no need to config SPI NSS pin)
			**in ADS1256 situation,SPI NSS pin is connected with GND in default
			*/
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			//Config SPI work in mode 
			SPIx_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  
			SPIx_InitStructure.SPI_Mode = SPI_Mode_Master;		
			SPIx_InitStructure.SPI_DataSize = SPI_DataSize_8b;		
			SPIx_InitStructure.SPI_CPOL = SPI_CPOL_Low;		
			SPIx_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; /*notice the spi mode*/
			SPIx_InitStructure.SPI_NSS = SPI_NSS_Soft;    
			SPIx_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;	
			SPIx_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	
			SPIx_InitStructure.SPI_CRCPolynomial = 7;

			SPI_Init(SPI2, &SPIx_InitStructure);
			
			SPI_Cmd(SPI2, ENABLE);			
}


unsigned char SPI_WriteReadByte(unsigned char TxData)
{
	unsigned  int  retry=0;
	unsigned char res;

	/*SPI_I2S_FLAG_TXE=1 means send buffer is empty*/
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 
	{
		retry++;
		if(retry>=200)
		{
			return 0;
		}
	}
	SPI_I2S_SendData(SPI2,TxData);

	retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 
	{
			retry++;
			if(retry>=200)
			{
				return 0;
			}
	}
	res = SPI_I2S_ReceiveData(SPI2);
	return (res);	
}

