#include "ModuleVCA.h"
#include "Defines.h"

uint32_t ModuleVCA::run()
{
  // Read inputs
  uint32_t audio = this->audio_input->run();
  uint32_t cv    = this->cv_input->run() ; 
  
  return((audio * cv) >> 12 );
}
