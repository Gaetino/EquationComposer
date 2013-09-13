#include "Arduino.h"
#include "ModuleArpeggio.h"
#include "Defines.h"


ModuleArpeggio::ModuleArpeggio()
{
 
}

arp ModuleArpeggio::compute_arpeg()
{
  uint32_t scale;
  int8_t CV;
  // Read scale input.  
  // Convert the standard 12 bit CV value to a 3-bit value, which ranges from 0 to 7
  scale = this->scale_input->run() >> 9;
  // Convert to 7-bit
  CV = this->CV_input->run() >> 5;
  
  if(scale==0) this->arpeg = {0,12,0,12,0,12,0,12};
  if(scale==1) this->arpeg = {0,12,0,12,0,12,-2,10};
  if(scale==2) this->arpeg = {0,10,12,0,10,12,0,0};
  if(scale==3) this->arpeg = {0,3,7,10,0,3,7,10};
  if(scale==4) this->arpeg = {0,3,7,10,12,10,7,3};
  if(scale==5) this->arpeg = {0,-2,0,3,0,-2,-5,-2};
  if(scale==6) this->arpeg = {0,0,12,0,0,0,12,0};
  if(scale==7) this->arpeg = {0,1,4,5,7,5,4,1};
  
  for(int i=0; i<ARPEG_STEP; i++)
  {
    arpeg[i] += CV;
  }
  
  return(arpeg);
}
