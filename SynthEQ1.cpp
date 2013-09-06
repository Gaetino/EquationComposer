#include "Arduino.h"
#include "Defines.h"
#include "SynthEQ1.h"

SynthEQ1::SynthEQ1(Module* inputs[])
{
  equation_looper.equation_input = inputs[MOD_INPUT];
  equation_looper.sample_rate_input = inputs[SR_INPUT];
  equation_looper.loop_start_input  = inputs[PARAM1_INPUT];
  equation_looper.loop_length_input = inputs[PARAM2_INPUT];
  this->last_module = &equation_looper;
}
