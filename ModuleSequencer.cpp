#include "Arduino.h"
#include "ModuleSequencer.h"
#include "Defines.h"

ModuleSequencer::ModuleSequencer(int values[], int steps)
{
  this->values = values;
  this->steps = steps;
  this->step = 0;
  this->old_clock = 0;
}

ModuleSequencer::ModuleSequencer()
{
  // this->values = values;
  // this->steps = steps;
  
  int sequence[] = { 3000, 4094, 3000, 3600, 0, 4000, 500, 2500 };
  
  this->step = 0;
  this->old_clock = 0;
  this->values = sequence;
}

uint32_t ModuleSequencer::run()
{
  /*
  uint32_t clock = this->clock_input->run();
  
  // Step the sequencer on the rising edge 
  if((clock > MID_CV) && (old_clock < MID_CV))
  {
    step++;
    if(step >= steps) step = 0;
  }
  
  old_clock = clock;
  
  Serial.println(values[step]);

  
  return(values[step]);
    */
    
  int sequence[] = { 3000, 4094, 3000, 3600, 0, 4000, 500, 2500 };    
  
  this->values = sequence;
    
  return(values[0]);
}
