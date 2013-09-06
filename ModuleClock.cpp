#include "Arduino.h"
#include "ModuleClock.h"
#include "Defines.h"

ModuleClock::ModuleClock(uint32_t bpm)
{
  this->counter = 0;  
  this->bpm = constrain(bpm, 0, 254);
  
  // Initialize table for different frequencies based on BPM
  for(uint32_t bpm_i=0; bpm_i < 255; bpm_i++)
  {
    bpm_ticks[bpm_i] = ((float)(60 * SAMPLE_RATE)/(float)bpm_i);
  }  

}

uint32_t ModuleClock::run()
{
  this->counter = this->counter + 1;
  
  if (this->counter == this->bpm_ticks[bpm])
  {
    this->counter = 0;
    return(MAX_CV);
  }
  else
  {
    return(0);
  }
}
