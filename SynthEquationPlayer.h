#ifndef SynthEquationPlayer_h
#define SynthEquationPlayer_h

#include "Arduino.h"
#include "Synth.h"

class SynthEquationPlayer : public Synth
{
  public:
  
    SynthEquationPlayer(Module *inputs[]); 
   
    // Create modules
    // These modules will be wired together in the constructor.
    ModuleEquationPlayer equation_player;   
    
};

#endif
