
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"

GPIO_InitTypeDef GPIO_InitStruct;
TaskHandle_t task_1handler = NULL;
TaskHandle_t task_2handler = NULL;

void GPIO_Input(void);
void GPIO_Output(void);
void setupConfig(void);
void Task1Handler(void *params);
void Task2Handler(void *params);
void FreeFTOSDelay(uint32_t delay);

int main(void)
{
	RCC_DeInit();
	SystemCoreClockUpdate();
	setupConfig();
	xTaskCreate(Task1Handler, "Task_1", configMINIMAL_STACK_SIZE, NULL, 4, &task_1handler);
	xTaskCreate(Task2Handler, "Task_2", configMINIMAL_STACK_SIZE, NULL, 3, &task_2handler);
	vTaskStartScheduler();
  while (1)
  {

  }
}
void Task1Handler(void *params){
	while(1){
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13);
		FreeFTOSDelay(1000);
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)){
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0));
			vTaskDelete(task_1handler);
		}
	}

}
void Task2Handler(void *params){
	while(1){
		GPIO_ToggleBits(GPIOD,GPIO_Pin_14|GPIO_Pin_15);
		FreeFTOSDelay(500);
	}
}

void GPIO_Input(){


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

void FreeFTOSDelay(uint32_t delay){
	uint32_t currentTick = xTaskGetTickCount();
	uint32_t delayTick = pdMS_TO_TICKS(delay);
	while(xTaskGetTickCount()<(currentTick+delayTick));
}

void setupConfig(void)
{
	GPIO_Output();
	GPIO_Input();
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
