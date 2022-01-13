
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"

GPIO_InitTypeDef GPIO_InitStruct;
TaskHandle_t myLedTaskHandle;
TaskHandle_t myButtonTaskHandle;

uint32_t counter=0;


void ledTaskFlashTask(void *params);
void buttonStateTask(void *params);
void GPIO_Input(void);
void GPIO_Output(void);
void setupConfig(void);
void delay_FreeRTOS(uint32_t delayMS);

int main(void)
{

	RCC_DeInit();
	SystemCoreClockUpdate();
	setupConfig();

	xTaskCreate(ledTaskFlashTask, "Led_Kontrol", 650, NULL, 2, &myLedTaskHandle);
	xTaskCreate(buttonStateTask, "Button_Control", 650, NULL, 2, &myButtonTaskHandle);
	vTaskStartScheduler();

  while (1)
  {

  }
}

void buttonStateTask(void *params){
	while(1)
	{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==Bit_SET){
		delay_FreeRTOS(100);
		xTaskNotify(myLedTaskHandle,0x00, eIncrement);
			}
	}
}

void ledTaskFlashTask(void *params){
		uint32_t pulNotificationValue = 0;
	  while (1)
	  {
		  	 if(xTaskNotifyWait(0, 0, &pulNotificationValue, portMAX_DELAY) == pdTRUE)
		  	 {
		  		 GPIO_ToggleBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		  	 }

	  }
}

void GPIO_Input(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

}



void GPIO_Output(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void setupConfig(void)
{
	GPIO_Output();
	GPIO_Input();
}

void delay_FreeRTOS(uint32_t delayMS)
{
	uint32_t currentTick = xTaskGetTickCount();
	uint32_t delayTick =	pdMS_TO_TICKS(delayMS);		// delayMS * configTICK_RATE_HZ / 1000;
	while(xTaskGetTickCount()<(currentTick+delayTick));


}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}



uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
