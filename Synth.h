#ifndef Synth_h
#define Synth_h

#include "Arduino.h"
#include "Module.h"
#include "ModuleOsc.h"
#include "ModuleEquationPlayer.h"
#include "ModuleEquationLooper.h"
#include "ModuleLFO.h"
#include "ModuleLowpassFilter.h"
#include "ModuleVCA.h"
#include "ModuleConstant.h"
#include "ModuleClock.h"
#include "ModuleSequencer.h"
#include "ModuleADSR.h"

class Synth
{
  public:
  
    // Methods
    Synth(); // Constructor
    uint32_t run();
    
    // 'last_module' is the last module in the synth.  
    // This module's run() method will be called by the synth.
    Module *last_module; 
};

#endif
