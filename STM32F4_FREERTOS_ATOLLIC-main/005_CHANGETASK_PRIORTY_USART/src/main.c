#include "stdio.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "stdbool.h"

GPIO_InitTypeDef GPIO_InitStruct;

EXTI_InitTypeDef EXTI_InitStruct;


char MyMass[30];


uint8_t buttonState=0;

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

void Task1_Handler(void *params);
void Task2_Handler(void *params);
void delay(uint32_t time);
void Setup_Config();
void GPIO_Config();
void USART_Config();
void Send_Message(char *message);
void EXTI_Init1();

void EXTI0_IRQHandler(){
	EXTI_ClearITPendingBit(EXTI_Line0);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
		buttonState = 1;

}



int main(void)
{
	// 1. Adým SystemCLK Internal olarak ayarlandý
	RCC_DeInit();		// HSI ON  | HSEOFF - PLL OFF | SYSTEMCLOCK 16Mhz OLDU
	// 2. Adým da 16 Mhz olarak ayarladýk.
	SystemCoreClockUpdate(); // Clock Updatesini yaptik ve 16 Mhz guncellemis olduk
	Setup_Config();
	//sprintf(MyMass,"RTOSA HOSGELDINIZ \r\n");
//	Send_Message(MyMass);

	//printf("STARTING_MY_PROJECT \r\n");
	// 3. Adým Görev oluþturma
	xTaskCreate(Task1_Handler, "Task1", configMINIMAL_STACK_SIZE,NULL,2,&myTask1Handle);
	xTaskCreate(Task2_Handler, "Task2", configMINIMAL_STACK_SIZE,NULL,3,&myTask2Handle);

	vTaskStartScheduler();

  while (1)
  {
  }
}


void Setup_Config(){
	GPIO_Config();
	USART_Config();
	EXTI_Init1();
}

void GPIO_Config(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	GPIO_Init(GPIOB,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);
}
void EXTI_Init1(){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_SetPriority(EXTI0_IRQn,2);
	NVIC_EnableIRQ(EXTI0_IRQn);

}
void USART_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	USART_InitTypeDef USART_InitStruct={0};
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3,&USART_InitStruct);
	USART_Cmd(USART3,ENABLE);
}

/*void Send_Message(char *message)
{
	for(int i = 0 ; i < strlen(message);i++)
	{
		while(USART_GetFlagStatus(USART3,USART_FLAG_TXE) != SET);
		USART_SendData(USART3,message[i]);
	}

}*/
void USART_Puts(USART_TypeDef* USARTx, volatile char *s)
{
	while(*s)
	{
		while(!(USARTx ->SR & 0x00000040));
		USART_SendData(USARTx, *s);
		*s++;
	}
}

void Task1_Handler(void *params){
	UBaseType_t p1,p2;
	sprintf(MyMass,"TASK-1_RUNNING \r\n");
	USART_Puts(USART3,MyMass);
	sprintf(MyMass,"TASK-1 PRIORTY : %d\r\n",uxTaskPriorityGet(myTask1Handle));
	USART_Puts(USART3,MyMass);
	sprintf(MyMass,"TASK-2 PRIORTY : %d\r\n",uxTaskPriorityGet(myTask2Handle));
	USART_Puts(USART3,MyMass);

	while(1)
	{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15);
		delay(400000);
		sprintf(MyMass,"TASK-1_RUNNING \r\n");
		USART_Puts(USART3,MyMass);
		if(buttonState == 1){

			buttonState = 0;
			p1 = uxTaskPriorityGet(myTask1Handle);
			p2 = uxTaskPriorityGet(myTask2Handle);
			vTaskPrioritySet(myTask1Handle,p2);
			vTaskPrioritySet(myTask2Handle,p1);

		}

	}
}

void Task2_Handler(void *params){
	UBaseType_t p1,p2;
	sprintf(MyMass,"TASK-2_RUNNING \r\n");
	USART_Puts(USART3,MyMass);
	sprintf(MyMass,"TASK-1 PRIORTY : %d\r\n",uxTaskPriorityGet(myTask1Handle));
	USART_Puts(USART3,MyMass);
	sprintf(MyMass,"TASK-2 PRIORTY : %d\r\n",uxTaskPriorityGet(myTask2Handle));
	USART_Puts(USART3,MyMass);

	while(1)
	{
		GPIO_ToggleBits(GPIOD,GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15);
		delay(1600000);
		sprintf(MyMass,"TASK-2_RUNNING \r\n");
		USART_Puts(USART3,MyMass);
		if(buttonState == 1){
			USART_Puts(USART3,MyMass);
			buttonState = 0;
			p1 = uxTaskPriorityGet(myTask1Handle);
			p2 = uxTaskPriorityGet(myTask2Handle);
			vTaskPrioritySet(myTask1Handle,p2);
			vTaskPrioritySet(myTask2Handle,p1);
		}

	}
}
void delay(uint32_t time){
	while(time--);
}
