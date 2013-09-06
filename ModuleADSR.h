/*
 *  +------------------------+
 *  | ModuleADSR             |
 *  |------------------------|
 *  > trigger input          |
 *  |                 output >
 *  +------------------------+
 */
/*
#ifndef ModuleADSR_h
#define ModuleADSR_h

#include "Arduino.h"
#include "Module.h"

// Constants for internal ADSR states
#define ADSR_ATTACK 0
#define ADSR_DECAY 1
#define ADSR_SUSTAIN 2
#define ADSR_RELEASE 3
#define ADSR_INACTIVE 4

class ModuleADSR : public Module
{
  public:
    ModuleADSR();
    uint32_t run();
    
  private:
    uint16_t state;         // ADSR_ATTACK, ADSR_DECAY, etc..
    uint32_t counter;
    
    uint32_t attack_time;   // measured in milliseconds
    uint32_t decay_time;    // measured in milliseconds
    uint32_t sustain_time;  // measured in milliseconds
    uint32_t release_time;  // measured in milliseconds
    
    uint32_t attack_level;   // 0 to 255
    uint32_t decay_level;    // 0 to 255
    
    // Inputs
    Module *trigger_input; 
};

#endif
*/
