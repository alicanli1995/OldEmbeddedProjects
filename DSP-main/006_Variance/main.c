#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH 320
#define true 			 1
#define false      0 
#define NUM_TAPS	 29
#define BLOK_SIZE  32


extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
float32_t signalMean(float32_t *sig_src_arr, uint32_t sigLength);
float32_t signalVariance(float32_t *sig_src_arr,float32_t sigMean, uint32_t sigLength);


void SysTick_Handler(void);
void plotInputSignals(void);


uint32_t  sysFreq=0;
float32_t inputSample;
float32_t inputMean;
float32_t inputVariance;


int main(){
	HAL_Init();
	SystemClock_Config();
	sysFreq = HAL_RCC_GetHCLKFreq();
	arm_mean_f32(&inputSignal_f32_1kHz_15kHz[0],SIG_LENGTH,&inputMean);
	arm_var_f32(&inputSignal_f32_1kHz_15kHz[0],SIG_LENGTH, &inputVariance);
	//inputVariance = signalVariance((float32_t*)&inputSignal_f32_1kHz_15kHz[0],(float32_t)inputMean, (uint32_t)SIG_LENGTH);
	
	while(true){
	}

}


void plotInputSignals(void){
	int j;
	while(true){
		for(int i = 0 ; i < SIG_LENGTH ; ++i)
		{
				inputSample = inputSignal_f32_1kHz_15kHz[i];
				for(j=0;j<6000;j++);
		}
	}
	
}

	
float32_t signalMean(float32_t *sig_src_arr, uint32_t sigLength){
	float _mean = 0.0F;
	
	for(int i = 0 ; i < SIG_LENGTH ; i++){
		_mean = _mean + sig_src_arr[i];
	}
	_mean /= (float32_t)sigLength;
	return _mean;
	
}

float32_t signalVariance(float32_t *sig_src_arr,float32_t sigMean, uint32_t sigLength){
	float32_t _variance = 0.0F;
	for(int i = 0 ; i < SIG_LENGTH ; i++){
		_variance = _variance + pow((sig_src_arr[i]- sigMean),2);
	}
	_variance /= (sigLength-1);
	
	return _variance;
	
}

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


