#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "lowPassFilter.h"
#include "sineGenerator.h"

#define SAMPLING_FREQ 1000
#define SIGNAL_FREQ		10
#define NOISE_FREQ		50

#define true 					1
#define false 				0
	
	
extern void SystemClock_Config(void);
void SysTick_Handler(void);

sine_generator_q15_t signalSet;
sine_generator_q15_t noiseSet;

q15_t noise, filtered, disturbed, sine;



uint32_t freq=0;

int main(void){

  HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	sine_generator_init_q15(&signalSet,SIGNAL_FREQ,SAMPLING_FREQ);
	sine_generator_init_q15(&noiseSet, NOISE_FREQ, SAMPLING_FREQ);
	lowPassFilterInit();
	
	
  while(true){
		sine 	= sine_calc_sample_q15(&signalSet) / 2 ;
		noise = sine_calc_sample_q15(&noiseSet)  / 6 ;
		disturbed = noise + sine ;
		filtered 	= lowPassFilter(&disturbed);
		HAL_Delay(1);
		
	}

	
}


void SysTick_Handler(void){
	
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
	
}
