/*
 *  +----------------------+
 *  | ModuleArpeggio       |
 *  |----------------------|
 *  > scale                |
 *  > mode                 |
 *  > transpo              |
 *  |                      |
 *  |               output >
 *  +----------------------+
 */
 
#ifndef ModuleArpeggio_h
#define ModuleArpeggio_h

#include "Arduino.h"
#include "Module.h"

#define ARPEG_STEP 8

struct arp
{
    uint32_t note[ARPEG_STEP];
};

class ModuleArpeggio : public Module
{
  
  public:
    ModuleArpeggio();

    // Inputs
    Module *CV_input;
    Module *scale_input;

  private:
  
    // Functions
    arp compute_arpeg();  
    
};

#endif
