#include "Arduino.h"
#include "Defines.h"
#include "Module.h"

Module::Module()
{
  // cycle is used to see if the module has already been run
  // durring the current interrupt execution.
  cycle = 10;
  output = 0; 
}

uint32_t Module::run(long cycle)
{ 
  // If the module has already been run during this cycle,
  // then return the output without recalculating it.
  if(this->cycle == cycle) return(this->output);
  
  this->cycle = cycle;
  
  // Compute the module's output and store it in the module
  this->output = this->compute();
  
  return(this->output);
}

uint32_t Module::readInput(Module *module)
{
  return(module->run(this->cycle));
}

