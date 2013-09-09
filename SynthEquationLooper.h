#ifndef SynthEquationLooper_h
#define SynthEquationLooper_h

#include "Arduino.h"
#include "Synth.h"

class SynthEquationLooper : public Synth
{
  public:
  
    SynthEquationLooper(Module *inputs[]); 
   
    // Create modules
    // These modules will be wired together in the constructor.
    ModuleEquationLooper equation_looper;   
    
};

#endif
