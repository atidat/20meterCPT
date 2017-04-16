#include "headers.h"


#define DebugBias
#define DebugFactor
#define NormalWork

void DeviceInit(void)
{
		/*If use SW mode ,close JTAG debug tool*/
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
		//NVIC_Configuration();
	
		//RTCInit();
		//TimerInit();
	
		UARTInit();
		//analybaute();
	
		//LedInit();
		
		ADS1256_Init();
			
		/*sdcard must be configed succesee*/
		//while(SDCardInitialize());
		//sdInitStatus = SDCardInitialize();
			
}


int main()
{
   	DeviceInit();

	ADS1256_readStatus(&adcStatus);

	while(1){

#ifdef DebugBias
		GetQuintupleBias();
#endif

#ifdef DebugFactor
	  	debugGetAmpFactor();
#endif


#ifdef NormalWork

#endif


	}

	return 0;	
	//SPI_Initialize();

}