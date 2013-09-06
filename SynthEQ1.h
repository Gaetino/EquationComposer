#ifndef SynthEQ1_h
#define SynthEQ1_h

#include "Arduino.h"
#include "Synth.h"

class SynthEQ1 : public Synth
{
  public:
  
    SynthEQ1(Module *inputs[]); 
   
    // Create modules
    // These modules will be wired together in the constructor.
    ModuleEquationLooper equation_looper;   
    
};

#endif
