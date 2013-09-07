#include "Arduino.h"
#include "Defines.h"
#include "SynthSubtractor.h"

SynthSubtractor::SynthSubtractor(Module* inputs[])
{
  // Patch up ocillator
  // osc.frequency_input = sequencer;      // Control the oscillator's requency using the SR knob
  osc.frequency_input = inputs[SR_INPUT];
  osc.wavetable_input = new ModuleConstant(0); // Select the first wavetable
  
  // Patch up LFO
  // lfo.frequency_input = inputs[PARAM2_INPUT];  // Control the frequency using the [2] knob
  // lfo.wavetable_input = new ModuleConstant(0); // select the first wavetable
  
  // Patch up ADSR
  adsr.trigger_input = new ModuleClock(30);  
  
  // Patch up lowpass filter
  lowpass_filter.audio_input = &osc;           // Route the audio from the oscillator into the filter
  lowpass_filter.cutoff_input = &adsr;         // Control the filter cutoff using the LFO
  lowpass_filter.resonance_input = new ModuleConstant(0);  // Set the resonance to 0
  
  // Patch up VCA
  // vca.cv_input = inputs[PARAM1_INPUT];
  vca.cv_input = &adsr;
  vca.audio_input = &lowpass_filter;           // Route the audio from the lowpass filter into the VCA

  this->last_module = &vca;
}

/*

If you get a compilation error that looks something like...

  SynthEQ1.cpp: In constructor 'SynthEQ1::SynthEQ1(Module**)':
  SynthEQ1.cpp:15: error: 'equation_granulator' was not declared in this scope

That probably means that you forgot to define the module in the Synth's .h
file.  I make this mistake often, so I thought I'd mention it.

*/
