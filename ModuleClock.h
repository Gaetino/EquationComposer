/*
 *  +----------------------+
 *  | ModuleClock          |
 *  |----------------------|
 *  |                      |
 *  |               output >
 *  +----------------------+
 */
 
#ifndef ModuleClock_h
#define ModuleClock_h

#include "Arduino.h"
#include "Module.h"

class ModuleClock : public Module
{
  public:
    ModuleClock(uint32_t bpm);
    uint32_t run();
    
  private:
    uint32_t rate;
    uint32_t counter;
    uint32_t bpm;
    uint32_t bpm_ticks[255];
};

#endif
