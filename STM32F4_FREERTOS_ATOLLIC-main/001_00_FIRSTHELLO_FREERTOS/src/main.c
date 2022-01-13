#include "stdio.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "stdbool.h"

GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;

char MyMass[200];
bool UART_ACCESS_KEY = 1;
bool UART_ACCESS_KEY1 = 1;
bool UART_ACCESS_KEY2 = 0;

int _write(int32_t file, uint8_t *ptr, int32_t len){

	for(int i = 0; i< len;i++)
	{
		ITM_SendChar((*ptr++));
	}
	return len;

}

TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

void Task1_Handler(void *params);
void Task2_Handler(void *params);

void Setup_Config(void);
void GPIO_Config(void);
void USART_Config(void);
void Send_Message(char *message);


int main(void)
{
	// 1. Adým SystemCLK Internal olarak ayarlandý
	RCC_DeInit();		// HSI ON  | HSEOFF - PLL OFF | SYSTEMCLOCK 16Mhz OLDU
	// 2. Adým da 16 Mhz olarak ayarladýk.
	SystemCoreClockUpdate(); // Clock Updatesini yaptik ve 16 Mhz guncellemis olduk
	Setup_Config();
	//sprintf(MyMass,"RTOSA HOSGELDINIZ \r\n");
	Send_Message(MyMass);

	//printf("STARTING_MY_PROJECT \r\n");
	// 3. Adým Görev oluþturma
	xTaskCreate(Task1_Handler, "Task1", configMINIMAL_STACK_SIZE,NULL,4,&myTask1Handle);
	xTaskCreate(Task2_Handler, "Task2", configMINIMAL_STACK_SIZE,NULL,4,&myTask2Handle);

	vTaskStartScheduler();

  while (1)
  {


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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void USART_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStruct);
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


void Task1_Handler(void *params){
	while(1)
	{
	if(UART_ACCESS_KEY == 1){
		UART_ACCESS_KEY = 0;
		Send_Message("STARTING_MY_TASK_1 \r\n");
		UART_ACCESS_KEY = 1;
		taskYIELD();
		}
	}
}
void Task2_Handler(void *params){
	while(1)
	{
	if(UART_ACCESS_KEY == 1){
		UART_ACCESS_KEY = 0;
		Send_Message("STARTING_MY_TASK_2 \r\n");
		UART_ACCESS_KEY = 1;
		taskYIELD();
		}
	}
}
