#include "stdio.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "stdbool.h"
#include "queue.h"
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
void Master_Task_Handler(void *params);
void Slave_Task_Handler(void *params);
/////////////////****TASK CREATE****//////////////////

/////////////////****QUEUE CREATE****//////////////////
xQueueHandle xQueue;
/////////////////****QUEUE CREATE****//////////////////

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

	sprintf(MyMass,"Binary Semafor Usage Betweem 2 Tasks ! \r\n");
	Send_Message(MyMass);

	xQueue = xQueueCreate(1,sizeof(unsigned int));
	vSemaphoreCreateBinary(xSemaphore);


	if((xQueue!=NULL) && (xSemaphore!=NULL)){
		xTaskCreate(Master_Task_Handler,
				"Master_Task", 500,NULL,3,NULL);
		xTaskCreate(Slave_Task_Handler,
				"Slave_Task", 500,NULL,1,NULL);

		sprintf(MyMass,"Queue And Semaphore Creating Successfully ! \r\n");
		Send_Message(MyMass);

		vTaskStartScheduler();
	}
	else
	{
		sprintf(MyMass,"ERROR CREATING ! \r\n");
		Send_Message(MyMass);
	}
  while (1)
  {
  }
}

void Master_Task_Handler(void *params){
	unsigned int xMastPassId;
	portBASE_TYPE xStatus;
	xSemaphoreGive(xSemaphore);

	while(1)
	{
		xMastPassId = (rand() & 0x1FF);
		xStatus = xQueueSend(xQueue,&xMastPassId,portMAX_DELAY);
		if(xStatus != pdPASS){
			sprintf(MyMass,"Could not send to the Queue ! \r\n");
			Send_Message(MyMass);
		}
		else
		{
			xSemaphoreGive(xSemaphore);
			taskYIELD();
		}
	}
}
void SlaveDoWork(unsigned int pass){
	sprintf(MyMass,"SLAVE TASK RUNNING ! And Wait MS: %d \r\n",pass);
	Send_Message(MyMass);

	vTaskDelay(pdMS_TO_TICKS(pass));



}

void Slave_Task_Handler(void *params){
	unsigned int xSlaveGiveId;
	portBASE_TYPE xStatus;

	while(1)
	{
		xSemaphoreTake(xSemaphore,0);
		xStatus = xQueueReceive(xQueue,&xSlaveGiveId,portMAX_DELAY);
		if(xStatus != pdPASS){
			sprintf(MyMass,"Slave Task: Queue is empty ! \r\n");
			Send_Message(MyMass);
		}
		else
		{
			SlaveDoWork(xSlaveGiveId);
		}
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
