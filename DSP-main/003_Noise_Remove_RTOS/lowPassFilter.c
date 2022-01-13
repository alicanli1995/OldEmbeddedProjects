#include "lowPassFilter.h"


q15_t low_pass_filter_coeff[FILTER_TAPS] = {

0xFB5C,
0x021C,
0x0219, 
0x024E,  

0x02AC,   
0x0325,    
0x03B0,     
0x0445,      

0x04DC,        
0x056E,         
0x05F7,          
0x0675,           

0x06DB,            
0x072D,             
0x0766,              
0x0782,               

0x0782,                
0x0766,                 
0x072D,                  
0x06DB,                   

0x0675,                    
0x05F7,                     
0x056E,                      
0x04DC,                       

0x0445,
0x03B0,
0x0325,
0x02AC,

0x024E,
0x0219,
0x021C,
0xFB5C,

};

q15_t lowPassFilterState[FILTER_TAPS + FILTER_BLOCK_LEN];
arm_fir_instance_q15 lowPassFilterSet;

void lowPassFilterInit(void)
{
	
	arm_fir_init_q15(&lowPassFilterSet, FILTER_TAPS, low_pass_filter_coeff,lowPassFilterState, FILTER_BLOCK_LEN);
	
}

q15_t lowPassFilter(q15_t *input)
{
	q15_t out;
	arm_fir_q15(&lowPassFilterSet, input, &out , FILTER_BLOCK_LEN);
	
	return out;
	
}



