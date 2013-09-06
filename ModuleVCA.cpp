#include "ModuleVCA.h"
#include "Defines.h"

uint32_t ModuleVCA::run()
{
  // Read inputs
  uint32_t audio = this->audio_input->run();
  uint32_t cv    = this->cv_input->run() >> 4;  // convert from 12 bits to 8 bits
  
  return((audio * cv) >> 8 );
}
