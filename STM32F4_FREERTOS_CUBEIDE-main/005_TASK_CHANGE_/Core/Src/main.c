/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include  "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

osThreadId myTask1Handle;
osThreadId Task2Handle;
/* USER CODE BEGIN PV */
uint8_t myMassage[50];
uint8_t buttonState = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
void Task1_Handler(void const * argument);
void Task2_Handler(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

		buttonState = 1 ;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of myTask1 */
  osThreadDef(myTask1, Task1_Handler, osPriorityRealtime, 0, 128);
  myTask1Handle = osThreadCreate(osThread(myTask1), NULL);

  /* definition and creation of Task2 */
  osThreadDef(Task2, Task2_Handler, osPriorityHigh, 0, 128);
  Task2Handle = osThreadCreate(osThread(Task2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_Task1_Handler */
/**
  * @brief  Function implementing the myTask1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task1_Handler */
void Task1_Handler(void const * argument)
{
  /* USER CODE BEGIN 5 */
	osPriority p1,p2;
	sprintf(myMassage,"Task1 Calisiyor... \r\n");
	HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
	sprintf(myMassage,"Task1 Priority : %d \r\n", osThreadGetPriority(myTask1Handle));
	HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
	sprintf(myMassage,"Task2 Priority : %d \r\n", osThreadGetPriority(Task2Handle));
	HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);

  /* Infinite loop */
  for(;;)
  {
	  if(buttonState==1){
		  buttonState = 0;
		  p1 = osThreadGetPriority(myTask1Handle);
		  p2 = osThreadGetPriority(Task2Handle);
		  osThreadSetPriority(myTask1Handle, p2);
		  osThreadSetPriority(Task2Handle, p1);
			sprintf(myMassage,"Task1 Calisiyor... \r\n");
			HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
			sprintf(myMassage,"Task1 Priority : %d \r\n", osThreadGetPriority(myTask1Handle));
			HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
			sprintf(myMassage,"Task2 Priority : %d \r\n", osThreadGetPriority(Task2Handle));
			HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
	  }
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_Task2_Handler */
/**
* @brief Function implementing the Task2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task2_Handler */
void Task2_Handler(void const * argument)
{
  /* USER CODE BEGIN Task2_Handler */
	osPriority p1,p2;
	sprintf(myMassage,"Task2 Calisiyor... \r\n");
	HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
	sprintf(myMassage,"Task1 Priority : %d \r\n", osThreadGetPriority(myTask1Handle));
	HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
	sprintf(myMassage,"Task2 Priority : %d \r\n", osThreadGetPriority(Task2Handle));
	HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);

  /* Infinite loop */
  for(;;)
  {
	  if(buttonState==1){
		  buttonState = 0;
		  p1 = osThreadGetPriority(myTask1Handle);
		  p2 = osThreadGetPriority(Task2Handle);
		  osThreadSetPriority(myTask1Handle, p2);
		  osThreadSetPriority(Task2Handle, p1);
			sprintf(myMassage,"Task2 Calisiyor... \r\n");
			HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
			sprintf(myMassage,"Task1 Priority : %d \r\n", osThreadGetPriority(myTask1Handle));
			HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
			sprintf(myMassage,"Task2 Priority : %d \r\n", osThreadGetPriority(Task2Handle));
			HAL_UART_Transmit(&huart3, myMassage, strlen(myMassage), 1000);
	  }
  }
  /* USER CODE END Task2_Handler */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
