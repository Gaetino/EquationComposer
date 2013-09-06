#include "Arduino.h"
#include "ModuleLowpassFilter.h"
#include "Defines.h"

ModuleLowpassFilter::ModuleLowpassFilter()
{
  // nada
}

uint32_t ModuleLowpassFilter::run()
{
  // Read inputs
  uint32_t audio = this->audio_input->run();               // audio range: 0 to 4095
  uint32_t cutoff = this->cutoff_input->run() >> 4;        // cutoff range: 0 to 255
  uint32_t resonance = this->resonance_input->run() >> 4;  // resonance range: 0 to 255
  
  lpf.setCutoffFreq(cutoff);
  lpf.setResonance(resonance);

  return(lpf.next(audio));
}

