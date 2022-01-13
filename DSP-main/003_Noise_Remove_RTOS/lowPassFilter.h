#ifndef __LOWPASS_FLTR_H
#define __LOWPASS_FLTR_H

#include "arm_math.h"                   // ARM::CMSIS:DSP

q15_t lowPassFilter(q15_t *input);
void lowPassFilterInit(void);

#define FILTER_TAPS 			32
#define FILTER_BLOCK_LEN 	1



#endif

