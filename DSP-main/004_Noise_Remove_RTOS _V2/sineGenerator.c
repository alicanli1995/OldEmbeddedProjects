#include "sineGenerator.h"

void sine_generator_init_q15(sine_generator_q15_t *sine_desc, q15_t sine_frequency, q15_t sampling_frequency)
{
   float32_t y[4];
	 float32_t coeff4;
	 float32_t coeff5;
	 
	 y[0] = 0;
  
	 y[1] = arm_sin_f32(2 * 		PI * sine_frequency / sampling_frequency);
	 y[2] = arm_sin_f32(2 * 2 * PI * sine_frequency / sampling_frequency);
   y[3] = arm_sin_f32(3 * 2 * PI * sine_frequency / sampling_frequency);

   coeff4 = (y[2] / y[1]) / 2 ;
   coeff5 = ((y[1] * y[3] - y[2] * y[2]) / (y[1] * y[1])) / 2;
	 
	 arm_float_to_q15(&coeff4, &(sine_desc->coeff[4]), 1);
   arm_float_to_q15(&coeff5, &(sine_desc->coeff[5]), 1);

   arm_biquad_cascade_df1_init_q15(&(sine_desc->iir_sine_generator_instance), 1, sine_desc->coeff, sine_desc->state, 1);
   arm_float_to_q15(&y[1], &(sine_desc->state[3]), 1);

}

q15_t sine_calc_sample_q15(sine_generator_q15_t *sine_desc)
{
  q15_t input, output;

  input = 0;
  arm_biquad_cascade_df1_q15(&(sine_desc->iir_sine_generator_instance), &input, &output, 1);
  return (output);
}

