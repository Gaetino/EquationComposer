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
  private:
    uint32_t compute();  
  
  public:    
    // Inputs
    Module *audio_input;  
    Module *cv_input;  
};

#endif
