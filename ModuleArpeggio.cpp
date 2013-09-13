#include "Arduino.h"
#include "ModuleArpeggio.h"
#include "Defines.h"


ModuleArpeggio::ModuleArpeggio()
{
 
}

arp ModuleLFO::compute()
{
  uint32_t scale;
  uint32_t CV;
  // Read scale input.  
  // Convert the standard 12 bit CV value to a 5-bit value, which ranges from 0 to 32
  scale = this->readInput(scale_input) >> 7;
  // Convert to 7-bit
  CV = this->readInput(CV_input) >> 5;
  
  if(scale==0) this->arpeg = {0,12,0,12,0,12,0,12};
  if(scale==0) this->arpeg = {0,12,0,12,0,12,-2,10};
  if(scale==0) this->arpeg = {0,10,12,0,10,12,0,0};
  if(scale==0) this->arpeg = {0,3,7,10,0,3,7,10};
  if(scale==0) this->arpeg = {0,3,7,10,12,10,7,3};
  if(scale==0) this->arpeg = {0,-2,0,3,0,-2,-5,-2};
  if(scale==0) this->arpeg = {0,0,12,0,0,0,12,0};
  if(scale==0) this->arpeg = {0,1,4,5,7,5,4,1};
  
  for(int i=0; i<ARPEG_STEP; i++)
  {
    arpeg[i] += CV;
  }
  
  return(arpeg);
}
