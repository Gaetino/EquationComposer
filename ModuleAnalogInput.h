/*
 *   +----------------------+
 *   | ModuleAnalogInput    |
 *   |----------------------|
 *   |                      |
 *   |               output >
 *   +----------------------+
 *
 */
 
#ifndef ModuleAnalogInput_h
#define ModuleAnalogInput_h

#include "Arduino.h"
#include "ModuleInput.h"

class ModuleAnalogInput : public ModuleInput
{
  
  public:
    
    // Methods
    ModuleAnalogInput(int input_pin);    
    uint32_t read();
    uint32_t run();
    
    // Variables
    uint32_t value;   // The value of the input
    int pin;
};

#endif
