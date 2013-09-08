/*
 *  +------------------------+
 *  | ModuleADSR             |
 *  |------------------------|
 *  > trigger input          |
 *  |                 output >
 *  +------------------------+
 */
 
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
    uint32_t compute();
	
    void set(uint32_t attack_time, uint32_t decay_time, uint32_t sustain, uint32_t release_time);
    void setAttackTime(uint32_t value);
    void setDecayTime(uint32_t value);
    void setSustain(uint32_t value);
    void setReleaseTime(uint32_t value);
    
    // Inputs
    Module *trigger_input;     
    
  private:
    uint16_t state;         // ADSR_ATTACK, ADSR_DECAY, etc..
    uint32_t counter;
    uint32_t output;
    boolean trigged;
    
    uint32_t attack_time;   // measured in milliseconds
    uint32_t decay_time;    // measured in milliseconds
    uint32_t sustain;  // measured in milliseconds
    uint32_t release_time;  // measured in milliseconds

};

#endif

