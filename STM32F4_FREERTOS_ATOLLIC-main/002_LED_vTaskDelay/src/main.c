
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "FreeRTOS.h"
#include "task.h"

GPIO_InitTypeDef GPIO_InitStruct;
TaskHandle_t myButtonTaskHandle = NULL;
TaskHandle_t myLedTaskHandle = NULL;

void readButtonStateTask(void *params);
void ledTaskFlashTask(void *params);
void GPIO_Input(void);
void GPIO_Output(void);
void setupConfig(void);

uint8_t buttonState=0;


int main(void)
{

	RCC_DeInit();
	SystemCoreClockUpdate();
	setupConfig();
	xTaskCreate(readButtonStateTask, "Buton_Okuma", configMINIMAL_STACK_SIZE, NULL, 3, &myButtonTaskHandle);
	xTaskCreate(ledTaskFlashTask, "Led_Kontrol", configMINIMAL_STACK_SIZE, NULL, 3, &myLedTaskHandle);
	vTaskStartScheduler();



  while (1)
  {

  }
}

void readButtonStateTask(void *params){
	  while (1)
	  {
		  if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_SET){
			  while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)== Bit_SET);
			  buttonState++;
			  if (buttonState == 5)
				  buttonState =0;
		  }

	  }
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

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}



uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
