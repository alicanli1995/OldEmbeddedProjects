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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "NOKIA5110.h"
#include "FONT_IMAGE.h"
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
SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_tx;

/* USER CODE BEGIN PV */
#define DELAY   2000
uint8_t menu_sec=0,menu_say=0,menu_pick1=0,menu_pick2=0,aq = 0,back_menu=0,led_state = 0,led2=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void baslangic(){
	  N5110_Clear();
	  N5110_SetFont(SmallFont);
	  N5110_PrintStr(3, 5, "LED MENU 1", true);
	  N5110_SetFont(SmallFont);
	  N5110_PrintStr(3, 21, "LED MENU 2", true);
	  /*N5110_SetFont(SmallFont);
	  N5110_PrintStr(3, 37, "LED 3 AC!", true);*/
}
void backmenu(){
	  N5110_Clear();
	  baslangic();
	  N5110_Update();
}
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)){
		if(menu_sec == 0)
			menu_say = 1;
		//////////////////////////////////

		if(aq == 2){
			menu_pick1++;
			if(menu_pick1 == 3)
				menu_pick1 = 0;
		}
		if(aq == 3){
			menu_pick2++;
			if(menu_pick2 == 3)
			menu_pick2 = 0;
		}
		///////////////////////////////


	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)){
		if(menu_sec == 0){
			menu_say = 0;
		}

			///////////////////////////

			if(aq == 2){
				menu_pick1--;
				if(menu_pick1 < 0)
					menu_pick1 = 0;
			}
			if(aq == 3){
				menu_pick2--;
			if(menu_pick2 < 0)
				menu_pick2 = 0;
			}
		/////////////////////////////////



	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)){

		if(menu_sec == 0)
			menu_sec = 1;
		if(menu_say == 0 ){
			led_state++;
			if(menu_pick1 == 2){
				menu_sec = 0;
			    led_state = 0;
			}
			if(menu_pick1 == 0)
				if(led_state == 2){
					for(int i=0;i<200000;i++);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, SET);
					led_state = 0;
				}

			if(menu_pick1 == 1)

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, RESET);
		}


		if(menu_say == 1 ){
			led2++;
			if(menu_pick2 == 2){
				menu_sec = 0;
				led2 = 0;
			}
			if(menu_pick2 == 0)
				if(led2 == 2){
					for(int i=0;i<200000;i++);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, SET);
					led2 = 0;
				}

			if(menu_pick2 == 1)

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, RESET);
		}


		/*if(menu_say == 1){
			if(menu_pick2 == 2){
				menu_sec = 0;
			    led_state = 0;
			}
		if(menu_pick2 == 0)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, SET);
		if(menu_pick2 == 1)
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, RESET);

		}*/

	}
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
  MX_DMA_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  N5110_Init();
  baslangic();
  N5110_Update();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  if(menu_sec == 1){

		  if(menu_say == 0){
			  	  	  	aq = 2;
			  	  	  	if(menu_pick1 == 0){
				  			N5110_Clear();
					       	N5110_DrawHLine(0, 0, N5110_MAX_WIDTH, true);
					        N5110_DrawHLine(0, 16, N5110_MAX_WIDTH, true);
					        N5110_DrawVLine(0, 0, 16, true);
					        N5110_DrawVLine(N5110_MAX_WIDTH-1, 0, 16, true);
						    N5110_Update();
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 5, "LED 1 ON", true);
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 21, "LED 1 OFF", true);
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 37, "BACK MENU", true);
				  			N5110_Update();
				  			HAL_Delay(100);
			  	  	  	}
			  	  	  	else if(menu_pick1 == 1){
				  			N5110_Clear();
					        N5110_DrawHLine(0, 16, N5110_MAX_WIDTH, true);
					        N5110_DrawHLine(0, 32, N5110_MAX_WIDTH, true);
					        N5110_DrawVLine(0, 16, 16, true);
					        N5110_DrawVLine(N5110_MAX_WIDTH-1, 16, 16, true);
						    N5110_Update();
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 5, "LED 1 ON", true);
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 21, "LED 1 OFF", true);
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 37, "BACK MENU", true);
				  			N5110_Update();
				  			HAL_Delay(100);

			  	  	  	}
			  	  	  	else if(menu_pick1 == 2){
				  			N5110_Clear();
	 	       		        N5110_DrawHLine(0, 32, N5110_MAX_WIDTH, true);
	 	       		        N5110_DrawHLine(0, 47, N5110_MAX_WIDTH, true);
	 	       		        N5110_DrawVLine(0, 32, 16, true);
	 	       		        N5110_DrawVLine(N5110_MAX_WIDTH-1, 32, 16, true);
						    N5110_Update();
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 5, "LED 1 ON", true);
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 21, "LED 1 OFF", true);
				  			N5110_SetFont(SmallFont);
				  			N5110_PrintStr(3, 37, "BACK MENU", true);
				  			N5110_Update();
				  			HAL_Delay(100);

			  	  	  	}
			  		}

			  	else if(menu_say == 1)
			  	{
			  	     	aq = 3;
			  	     	if(menu_pick2 == 0){
			  	  				  			N5110_Clear();
			  	  					       	N5110_DrawHLine(0, 0, N5110_MAX_WIDTH, true);
			  	  					        N5110_DrawHLine(0, 16, N5110_MAX_WIDTH, true);
			  	  					        N5110_DrawVLine(0, 0, 16, true);
			  	  					        N5110_DrawVLine(N5110_MAX_WIDTH-1, 0, 16, true);
			  	  						    N5110_Update();
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 5, "LED 2 ON", true);
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 21, "LED 2 OFF", true);
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 37, "BACK MENU", true);
			  	  				  			N5110_Update();
			  	  				  			HAL_Delay(100);

			  	  			  	  	  	}
			  	  			  	  	  	if(menu_pick2 == 1){
			  	  				  			N5110_Clear();
			  	  					        N5110_DrawHLine(0, 16, N5110_MAX_WIDTH, true);
			  	  					        N5110_DrawHLine(0, 32, N5110_MAX_WIDTH, true);
			  	  					        N5110_DrawVLine(0, 16, 16, true);
			  	  					        N5110_DrawVLine(N5110_MAX_WIDTH-1, 16, 16, true);
			  	  						    N5110_Update();
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 5, "LED 2 ON", true);
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 21, "LED 2 OFF", true);
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 37, "BACK MENU", true);
			  	  				  			N5110_Update();
			  	  				  			HAL_Delay(100);

			  	  			  	  	  	}
			  	  			  	  	  	if(menu_pick2 == 2){
			  	  				  			N5110_Clear();
			  	  	 	       		        N5110_DrawHLine(0, 32, N5110_MAX_WIDTH, true);
			  	  	 	       		        N5110_DrawHLine(0, 47, N5110_MAX_WIDTH, true);
			  	  	 	       		        N5110_DrawVLine(0, 32, 16, true);
			  	  	 	       		        N5110_DrawVLine(N5110_MAX_WIDTH-1, 32, 16, true);
			  	  						    N5110_Update();
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 5, "LED 2 ON", true);
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 21, "LED 2 OFF", true);
			  	  				  			N5110_SetFont(SmallFont);
			  	  				  			N5110_PrintStr(3, 37, "BACK MENU", true);
			  	  				  			N5110_Update();
			  	  				  			HAL_Delay(100);

			  	  			  	  	  	}
			  	}
	  }
	  else if (menu_sec ==0)
	  {
		  if(menu_say == 0){
				  N5110_Clear();
				  baslangic();
		       	  N5110_DrawHLine(0, 0, N5110_MAX_WIDTH, true);
		          N5110_DrawHLine(0, 16, N5110_MAX_WIDTH, true);
		          N5110_DrawVLine(0, 0, 16, true);
		          N5110_DrawVLine(N5110_MAX_WIDTH-1, 0, 16, true);
			      N5110_Update();
		  }
		  else if(menu_say == 1)
		  {
					N5110_Clear();
					baslangic();
			        N5110_DrawHLine(0, 16, N5110_MAX_WIDTH, true);
			        N5110_DrawHLine(0, 32, N5110_MAX_WIDTH, true);
			        N5110_DrawVLine(0, 16, 16, true);
			        N5110_DrawVLine(N5110_MAX_WIDTH-1, 16, 16, true);
			        N5110_Update();
		  }
	  }
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, DC_Pin|RST_Pin|CE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA1 PA2 PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DC_Pin RST_Pin CE_Pin */
  GPIO_InitStruct.Pin = DC_Pin|RST_Pin|CE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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
