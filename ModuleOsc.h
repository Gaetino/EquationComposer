/*
 *  +----------------------+
 *  | ModuleOsc            |
 *  |----------------------|
 *  > frequency_input      |
 *  > wavetable_input      |
 *  |               output >
 *  +----------------------+
 */


#ifndef ModuleOsc_h
#define ModuleOsc_h

#include "Arduino.h"
#include "Module.h"

#define WAVE_SAMPLES 512
#define NUMBER_OF_WAVETABLES 2

class ModuleOsc : public Module
{
  
  public:
    ModuleOsc();
    uint32_t compute();
    
    // Inputs
    Module *frequency_input;   // Input module for controlling frequency
    Module *wavetable_input;   // Input module for controlling wavetable selection
    
  private:
    uint32_t wavetable_index;  // An index into the wavetables array
    uint32_t wavetable;        // Which wavetable is currently selected
    uint32_t frequency;        // An index into the increments table
    
    uint16_t wavetables[NUMBER_OF_WAVETABLES][WAVE_SAMPLES];
    uint32_t increments[128];
    
    // 10.22 fixed point number (using the upper 10 bits for addressing the indexes 
    // up to 1024 (we only need 600), and an additional 22 bits (0-4194304) for simulating fractional values for
    // use when incrementing the variable fractional values
    uint32_t fixed_point_10_22_index;
    uint32_t increment_by;
};

#endif
