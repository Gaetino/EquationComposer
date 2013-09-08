#include "Arduino.h"
#include "ModuleLowpassFilter.h"
#include "Defines.h"

ModuleLowpassFilter::ModuleLowpassFilter()
{
  // nada
}

uint32_t ModuleLowpassFilter::compute()
{
  // Read inputs
  uint32_t audio = this->readInput(audio_input);               // audio range: 0 to 4095
  uint32_t cutoff = this->readInput(cutoff_input) >> 4;        // cutoff range: 0 to 255
  uint32_t resonance = this->readInput(resonance_input) >> 4;  // resonance range: 0 to 255
  
  lpf.setCutoffFreq(cutoff);
  lpf.setResonance(resonance);

  return(lpf.next(audio));
}

