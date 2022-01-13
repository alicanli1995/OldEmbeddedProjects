#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define SIG_LENGTH 320
#define true 			 1
#define false      0 
#define NUM_TAPS	 29
#define BLOK_SIZE  32


extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LENGTH];
static float32_t firStateF32[BLOK_SIZE + SIG_LENGTH -1];

float outputSignal_F32[SIG_LENGTH];

void SysTick_Handler(void);
void plotInputSignals(void);
void plotOutputSignals(void);
void plotBothSignal(void);

uint32_t  numBlocks = SIG_LENGTH / BLOK_SIZE;
uint32_t  sysFreq=0;
float32_t inputSample,outputSample;

const float32_t firCoeffs32[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};



int main(){
	
	HAL_Init();
	SystemClock_Config();
	
	arm_fir_instance_f32 _1Khz_15Khz_sig;
	arm_fir_init_f32(&_1Khz_15Khz_sig,NUM_TAPS,(float32_t*)&firCoeffs32[0],&firStateF32[0],BLOK_SIZE);  
	
	for(int i = 0 ; i < numBlocks ; i++){
	
		arm_fir_f32(&_1Khz_15Khz_sig,&inputSignal_f32_1kHz_15kHz[0] + ( i * BLOK_SIZE), &outputSignal_F32[0] + ( i * BLOK_SIZE ) , BLOK_SIZE);
		
	}
	sysFreq = HAL_RCC_GetHCLKFreq();
	plotBothSignal();
	


	
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

void plotOutputSignals(void){
	int j;
	while(true){
		for(int i = 0 ; i < SIG_LENGTH ; ++i)
		{
				outputSample = outputSignal_F32[i];
				for(j=0;j<6000;j++);
		}
	}
	
}

void plotBothSignal(void){
	int j;
	while(true){
		for(int i = 0 ; i < SIG_LENGTH ; ++i)
		{
				inputSample = inputSignal_f32_1kHz_15kHz[i];
				outputSample = outputSignal_F32[i];
				for(j=0;j<10000;j++);
		}
	}
	
}
	
void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


