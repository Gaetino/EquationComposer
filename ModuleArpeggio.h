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
    Module *scale;
    Module *mode;
    Module *transpo;
    
  private:
  
    // Functions
    arp compute_arpeg();  
  
    // Variables
    int8_t arpeg[ARPEG_STEP];
};

#endif
