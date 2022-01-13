#include "stdio.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "stdbool.h"
#include "queue.h"
#include "timers.h"


void Setup_Config();
void GPIO_Config();
void USART_Config();
void ERROR_MSG(char *cmdTaskMassage);
void EXIT_API();



#define LED_ON 			1
#define LED_OFF 		2
#define LED_TOGGLE_ON	3
#define	LED_TOGGLE_OFF	4
#define LED_STATS		5
#define	EXIT			6


void vApplicationIdleHook(){
	__WFI();
}

GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

char MyMass[100];
char Disp[]= {"\r\nLed_ON ->		1  \r\nLed_OFF ->		2  \r\nLed_TOGGLE_On->	3 \r\nLed_TOGGLE_OFF->	4  \r\nLed_STATUS->	5\r\nEXIT_APP->		6 \r\n  \r\n Type Option : "};


uint8_t  CommandBuffer[30];
uint8_t  CommandLenght=0;

TaskHandle_t task1MenuHandler = NULL;
TaskHandle_t task2CommandHandler = NULL;
TaskHandle_t task3CommandProccesHandler = NULL;
TaskHandle_t task4UartHandler = NULL;
QueueHandle_t Uart_Write = NULL;
QueueHandle_t Command_Write = NULL;
TimerHandle_t TIMERHANDLE = NULL;




void task1_MenuDispHandler(void *params);
void task2_CommandHandlingHandler(void *params);
void task3_CommandProccesHandler(void *params);
void task4_UartWriteHandler(void *params);
void Send_Message(char *message);
uint8_t GetCommandVal(uint8_t *buffer);
uint8_t getArg(uint8_t *buffer);
void Led_On(void);
void Led_Off(void);
void Led_Toggle_On(uint32_t Timer);
void Led_Toggle_Off(void);
void Led_Status(char *LedState);
void EXIT_App(void);
void LED_TOGGLE_FOR_TIMER(void);
void Error_Msg(char *ERROR);


void USART2_IRQHandler()
{
	uint8_t  rxChar;
	BaseType_t xHigherProiortyTaskWoken = pdFALSE;

	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)){
		rxChar = USART_ReceiveData(USART2);
		CommandBuffer[CommandLenght++] = rxChar & 0xFF;
		if(rxChar == 10){
			CommandLenght = 0;
			xTaskNotifyFromISR(task1MenuHandler,0,eNoAction,&xHigherProiortyTaskWoken);
			xTaskNotifyFromISR(task2CommandHandler,0,eNoAction,&xHigherProiortyTaskWoken);

		}

		USART_ClearFlag(USART2,USART_FLAG_RXNE);
	}
	if(xHigherProiortyTaskWoken == pdTRUE){
		taskYIELD();
	}

}



typedef struct APP_Command{
	uint8_t Command_NUM;
	uint8_t Command_ARG[10];

}APP_Command_t;

int main(void)
{
	// 1. Adým SystemCLK Internal olarak ayarlandý
	RCC_DeInit();		// HSI ON  | HSEOFF - PLL OFF | SYSTEMCLOCK 16Mhz OLDU
	// 2. Adým da 16 Mhz olarak ayarladýk.
	SystemCoreClockUpdate(); // Clock Updatesini yaptik ve 16 Mhz guncellemis olduk
	Setup_Config();

	sprintf(MyMass,"Queue Trying Program ! \r\n");
	Send_Message(MyMass);


	Uart_Write = xQueueCreate(10,sizeof(char*));
	Command_Write = xQueueCreate(10,sizeof(APP_Command_t*));

	if(Uart_Write != NULL && Command_Write != NULL){

		sprintf(MyMass,"Queue Creating Successfully ! \r\n");
		Send_Message(MyMass);

		xTaskCreate(task1_MenuDispHandler,
				"Menu_Disp", 500,NULL,1,&task1MenuHandler);
		xTaskCreate(task2_CommandHandlingHandler,
				"Command_Handling", 500,NULL,2,&task2CommandHandler);
		xTaskCreate(task3_CommandProccesHandler,
				"Procces_Handler", 500,NULL,2,&task3CommandProccesHandler);
		xTaskCreate(task4_UartWriteHandler,
				"Uart_Write", 500,NULL,2,&task4UartHandler);

		vTaskStartScheduler();
	}
	else
	{
		sprintf(MyMass,"Failed To Create ! \r\n");
		Send_Message(MyMass);
	}


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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);
	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
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
void task1_MenuDispHandler(void *params){
	char *rxdata = Disp;
	while(1){

		xQueueSend(Uart_Write,&rxdata,portMAX_DELAY);
		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);

	}
}

void task2_CommandHandlingHandler(void *params){
	uint8_t commandCode=0;
	APP_Command_t *appCmd;
	while(1){

		xTaskNotifyWait(0,0,NULL,portMAX_DELAY);
		commandCode = GetCommandVal(CommandBuffer);
		appCmd = (APP_Command_t*)pvPortMalloc(sizeof(APP_Command_t));

		taskENTER_CRITICAL();


		appCmd->Command_NUM = commandCode;
		getArg(appCmd->Command_ARG);


		taskEXIT_CRITICAL();

		xQueueSend(Command_Write,&appCmd,portMAX_DELAY);
	}
}

void task3_CommandProccesHandler(void *params){
	APP_Command_t *RxAppcmd;
	char cmdTaskMassage[50];
	char ErrorMsg[50];
	uint16_t ToggleTime = pdMS_TO_TICKS(500);


	while(1){

		xQueueReceive(Command_Write,(void*)&RxAppcmd,portMAX_DELAY);
		if(RxAppcmd->Command_NUM == LED_ON)
		{
			Led_On();
		}

		else if(RxAppcmd->Command_NUM == LED_OFF)
		{
			Led_Off();
		}
		else if(RxAppcmd->Command_NUM == LED_TOGGLE_ON)
		{
			Led_Toggle_On(ToggleTime);
		}
		else if(RxAppcmd->Command_NUM == LED_TOGGLE_OFF)
		{
			Led_Toggle_Off();
		}
		else if(RxAppcmd->Command_NUM == LED_STATS)
		{
			Led_Status(cmdTaskMassage);
		}

		else if(RxAppcmd->Command_NUM == EXIT)
		{
			EXIT_API();
		}
		else
		{
			ERROR_MSG(ErrorMsg);
		}
	}
}

void EXIT_API()
{
	sprintf(MyMass,"Gorevler Basari Ile Silindi! \r\n");
	Send_Message(MyMass);
	sprintf(MyMass,"ISR Basari Ile Silindi! \r\n");
	Send_Message(MyMass);
	sprintf(MyMass,"NVIC Basari Ile Silindi! \r\n");
	Send_Message(MyMass);
	//DELETE TASK!

	vTaskDelete(task1MenuHandler);
	vTaskDelete(task2CommandHandler);
	vTaskDelete(task3CommandProccesHandler);
	vTaskDelete(task4UartHandler);


	//DISABLE ISR

	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);

	//	NVIC SHUT DOWN
	NVIC_DisableIRQ(USART2_IRQn);

}

void ERROR_MSG(char *errorErrorMsg){

	sprintf(errorErrorMsg,"WRONG VALUE,Please Try Again \r\n");
	xQueueSend(Uart_Write,&errorErrorMsg,portMAX_DELAY);


}


void task4_UartWriteHandler(void *params){
	char *txdata31= NULL;
	while(1){
	    xQueueReceive(Uart_Write,&txdata31,portMAX_DELAY);
		Send_Message(txdata31);
	}
}


void Led_On(void){
	GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}

void Led_Off(void){
	GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

}

void Led_Toggle_On(uint32_t Timer){
	if(TIMERHANDLE==NULL){
			// TIMER CREATE SOFTWARE
		TIMERHANDLE =xTimerCreate("TOGGLE_TIMER",Timer,pdTRUE,NULL,LED_TOGGLE_FOR_TIMER);

			//SOFTWARE TIMER START
		xTimerStart(TIMERHANDLE,portMAX_DELAY);
	}
	else
	{
		xTimerStart(TIMERHANDLE,portMAX_DELAY);
	}

}

void Led_Toggle_Off(void){
	xTimerStop(TIMERHANDLE,portMAX_DELAY);
}

void Led_Status(char *LedState){
	sprintf(LedState,"\r\nLed Status: %d\r\n",GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_12));
	//Send_Message(MyMass);
	xQueueSend(Uart_Write,&LedState,portMAX_DELAY);
}

void EXIT_App(void){

}

void LED_TOGGLE_FOR_TIMER(void){
	GPIO_ToggleBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}

uint8_t getArg(uint8_t *buffer){
	return buffer[0];
}

uint8_t GetCommandVal(uint8_t *buffer){
	return buffer[0]-48;
}
