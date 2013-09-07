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
    bpm_half_ticks[bpm_i] = bpm_ticks[bpm_i] / 2;
  }  

}

uint32_t ModuleClock::run()
{
  this->counter = this->counter + 1;

  //   If we're at the end of the clock duty,
  //   then reset the counter back to 0 and return 0  
  //
  //         _____↓
  //        |     |
  //   _____|     |

  if(this->counter == this->bpm_ticks[bpm]) 
  {
    this->counter = 0;
    return(0);
  }
  
  // If we're 1/2 way (or more) through the clock duty,
  // then output the MAX_CV
  //
  //        ↓_____
  //        |     |
  //   _____|     |
  
  if (this->counter >= this->bpm_half_ticks[bpm])
  {
    return(MAX_CV);
  }
  
  // If neither of the two conditions above it true,
  // then we're at the first phase of the clock duty,
  // so return 0.
  //
  //         _____
  //        |     |
  //   __↓__|     |  
  
  else
  {
    return(0);
  }
  
}
