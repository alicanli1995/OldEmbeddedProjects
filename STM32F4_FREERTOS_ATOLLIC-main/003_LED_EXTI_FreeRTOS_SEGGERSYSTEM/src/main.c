
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"

GPIO_InitTypeDef GPIO_InitStruct;
TaskHandle_t myLedTaskHandle = NULL;

void readButtonStateTask(void *params);
void ledTaskFlashTask(void *params);
void GPIO_Input(void);
void GPIO_Output(void);
void setupConfig(void);
void Button_Handler(void);

void EXTI0_IRQHandler(void){
	traceISR_ENTER();
	EXTI_ClearITPendingBit(EXTI_Line0);
	Button_Handler();
	traceISR_EXIT();

}



uint8_t buttonState = 0;


int main(void)
{
	DWT->CTRL |= (1<<0);
	RCC_DeInit();
	SystemCoreClockUpdate();
	setupConfig();
	SEGGER_SYSVIEW_Conf();
	SEGGER_SYSVIEW_Start();
	xTaskCreate(ledTaskFlashTask, "Led_Kontrol", configMINIMAL_STACK_SIZE, NULL, 2, &myLedTaskHandle);
	vTaskStartScheduler();



  while (1)
  {

  }
}

void Button_Handler(void)
{
	buttonState++;
	if(buttonState==5)
		buttonState=0;

}

void ledTaskFlashTask(void *params){
	  while (1)
	  {
		  if(buttonState == 0)
			  GPIO_ResetBits(GPIOD,GPIO_Pin_All);
		  else if(buttonState == 1){
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_All);
			  vTaskDelay(1000);
		  }
		  else if(buttonState == 2){
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_All);
			  vTaskDelay(750);
		  }
		  else if(buttonState == 3){
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_All);
			  vTaskDelay(500);
		  }
		  else if(buttonState == 4){
			  GPIO_ToggleBits(GPIOD,GPIO_Pin_All);
			  vTaskDelay(250);
		  }

	  }
}

void GPIO_Input(){

	EXTI_InitTypeDef EXTI_InitStruct = {0};

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_SetPriority(EXTI0_IRQn,1);
	NVIC_EnableIRQ(EXTI0_IRQn);

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

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}



uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
