#include "stdio.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "stdbool.h"
#include "semphr.h"
#include "stdlib.h"

void Send_Message(char *message);
void Setup_Config();
void GPIO_Config();
void USART_Config();


char MyMass[49];

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

/////////////////****TASK CREATE****//////////////////
void Task1_Handler(void *params);
void Task2_Handler(void *params);
/////////////////****TASK CREATE****//////////////////
/////////////////****SEMAPHORES CREATE****//////////////////
xSemaphoreHandle xSemaphore;

/////////////////****SEMAPHORES CREATE****//////////////////




int main(void)
{
	// 1. Adým SystemCLK Internal olarak ayarlandý
	RCC_DeInit();		// HSI ON  | HSEOFF - PLL OFF | SYSTEMCLOCK 16Mhz OLDU
	// 2. Adým da 16 Mhz olarak ayarladýk.
	SystemCoreClockUpdate(); // Clock Updatesini yaptik ve 16 Mhz guncellemis olduk
	Setup_Config();

	 vSemaphoreCreateBinary(xSemaphore);
	 if(xSemaphore != NULL){
	sprintf(MyMass,"Demo of Mutex with Binary Semaphore..! \r\n");
	Send_Message(MyMass);

	xTaskCreate(Task1_Handler,
			"Task1_Handler", 500,NULL,3,NULL);
	xTaskCreate(Task2_Handler,
			"Task2_Handler", 500,NULL,3,NULL);
	vTaskStartScheduler();
	 }

  while (1)
  {
  }
}

void Task1_Handler(void *params){
	const char *pvTaskMsg = "Task1 is running ! \r\n";

	while(1)
	{
		sprintf(MyMass,"%s",pvTaskMsg);
		Send_Message(MyMass);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}


void Task2_Handler(void *params){
	const char *pvTaskMsg = "Task2 is running ! \r\n";
	while(1)
	{
		sprintf(MyMass,"%s",pvTaskMsg);
		Send_Message(MyMass);
		vTaskDelay(pdMS_TO_TICKS(500));
	}
}


void Setup_Config(){
	GPIO_Config();
	USART_Config();
}

void GPIO_Config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void USART_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStruct);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	NVIC_SetPriority(USART2_IRQn,5);
	NVIC_EnableIRQ(USART2_IRQn);
	USART_Cmd(USART2,ENABLE);
}


void Send_Message(char *message)
{
	for(int i = 0 ; i < strlen(message);i++)
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
		USART_SendData(USART2,message[i]);
	}

}
