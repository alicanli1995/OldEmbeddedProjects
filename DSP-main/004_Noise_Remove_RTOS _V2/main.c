#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "lowPassFilter.h"
#include "sineGenerator.h"




osThreadId sineID,noiseID,disturbedID,filteredID,syncID;


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

void sineThread(void const *args);
void noiseThread(void const *args);
void disturbedThread(void const *args);
void filteredThread(void const *args);
void syncThread(void const *args);

osThreadDef(sineThread,		  osPriorityNormal,1,0);
osThreadDef(noiseThread,		osPriorityNormal,1,0);
osThreadDef(disturbedThread,osPriorityNormal,1,0);
osThreadDef(filteredThread,	osPriorityNormal,1,0);
osThreadDef(syncThread,			osPriorityNormal,1,0);

uint32_t t = 10;

void sineThread(void const *args){
	while(true){
		osSignalWait(0x0001,0);
		osDelay(t);
		sine 	= sine_calc_sample_q15(&signalSet) / 2 ;	
	}
}

void noiseThread(void const *args){
	while(true){
		osSignalWait(0x0001,0);
		osDelay(t);
		noise = sine_calc_sample_q15(&noiseSet)  / 6 ;
	}
}

void disturbedThread(void const *args){
	while(true){
		osSignalWait(0x0001,0);
		osDelay(t);
		disturbed = noise + sine ;	
	}
}


void filteredThread(void const *args){
	while(true){
		osSignalWait(0x0001,0);
		osDelay(t);
		filtered 	= lowPassFilter(&disturbed);
	}
}


void syncThread(void const *args){
	while(true){
		osDelay(t);
		osSignalWait(0x0001,osWaitForever);
		osSignalSet(sineID,0x0001);
	}
}
uint32_t freq=0;

int main(void){

  HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	sine_generator_init_q15(&signalSet,SIGNAL_FREQ,SAMPLING_FREQ);
	sine_generator_init_q15(&noiseSet, NOISE_FREQ, SAMPLING_FREQ);
	lowPassFilterInit();
	
	sineID 			= osThreadCreate(osThread(sineThread),NULL);
	noiseID 		= osThreadCreate(osThread(noiseThread),NULL);
	disturbedID = osThreadCreate(osThread(disturbedThread),NULL);
	filteredID 	= osThreadCreate(osThread(filteredThread),NULL);
	syncID 			= osThreadCreate(osThread(syncThread),NULL);
	
	//while(true);
}



