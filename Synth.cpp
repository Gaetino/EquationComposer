#include "Arduino.h"
#include "Defines.h"
#include "Synth.h"

Synth::Synth()
{
  
}

uint32_t Synth::run()
{
  return(this->last_module->run());
}

