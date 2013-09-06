/*
 *  +----------------------+
 *  | ModuleVCA            |
 *  |----------------------|
 *  > audio_input          |
 *  > cv_input             |
 *  |               output >
 *  +----------------------+
 */

#ifndef ModuleVCA_h
#define ModuleVCA_h

#include "Module.h"

class ModuleVCA : public Module
{
  
  public:
    
    // Methods
    uint32_t run();
    uint32_t low();
    uint32_t high();
    
    // Inputs
    Module *audio_input;  
    Module *cv_input;  
};

#endif
