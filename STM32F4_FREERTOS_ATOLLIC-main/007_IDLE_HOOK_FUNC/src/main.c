#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"


GPIO_InitTypeDef GPIO_InitStruct;

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

void Task1_Handler(void *params);
void Task2_Handler(void *params);

void Setup_Config();
void GPIO_Config();


void vApplicationIdleHook(){
	__WFI();
}

int main(void)
{
	// 1. Adým SystemCLK Internal olarak ayarlandý
 	RCC_DeInit();		// HSI ON  | HSEOFF - PLL OFF | SYSTEMCLOCK 16Mhz OLDU
	// 2. Adým da 16 Mhz olarak ayarladýk.
	SystemCoreClockUpdate(); // Clock Updatesini yaptik ve 16 Mhz guncellemis olduk
	Setup_Config();

	xTaskCreate(Task1_Handler, "Task1", configMINIMAL_STACK_SIZE,NULL,2,&myTask1Handle);
	xTaskCreate(Task2_Handler, "Task2", configMINIMAL_STACK_SIZE,NULL,2,&myTask2Handle);

	vTaskStartScheduler();

  while (1)
  {
  }
}


void Setup_Config(){
	GPIO_Config();
}

void GPIO_Config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

}


void Task1_Handler(void *params){
	while(1)
	{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_14);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void Task2_Handler(void *params){
	while(1)
	{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_13|GPIO_Pin_15);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
