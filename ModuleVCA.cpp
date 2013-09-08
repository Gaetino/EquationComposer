#include "ModuleVCA.h"
#include "Defines.h"

uint32_t ModuleVCA::compute()
{
  // Read inputs
  uint32_t audio = this->readInput(audio_input);
  uint32_t cv    = this->readInput(cv_input) ; 
  
  return((audio * cv) >> 12 );
}
