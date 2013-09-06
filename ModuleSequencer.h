/*
 *  +----------------------+
 *  | ModuleSequencer      |
 *  |----------------------|
 *  > clock_input          |
 *  |                      |
 *  |               output >
 *  +----------------------+
 */
 
#ifndef ModuleSequencer_h
#define ModuleSequencer_h

#include "Arduino.h"
#include "Module.h"

class ModuleSequencer : public Module
{
  
  public:
    ModuleSequencer(int values[], int size);
    ModuleSequencer();
    uint32_t run();
    
    // Inputs
    Module *clock_input;
    
  private:
    int step;
    int steps;
    int *values;
    uint32_t old_clock;
};

#endif
