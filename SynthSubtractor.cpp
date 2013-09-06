#include "Arduino.h"
#include "Defines.h"
#include "SynthSubtractor.h"

SynthSubtractor::SynthSubtractor(Module* inputs[])
{

  // Example with LFO controlling filter cutoff

  // Create sequencer
  // int sequence[8] = { 3000, 4094, 3000, 3600, 0, 4000, 500, 2500 }; // Just some random notes
  // ModuleSequencer *sequencer = new ModuleSequencer(sequence, 8);
  // sequencer->clock_input = new ModuleClock(120);

  sequencer.clock_input = new ModuleConstant(120);
  
  // Patch up ocillator
  // osc.frequency_input = sequencer;      // Control the oscillator's requency using the SR knob
  osc.frequency_input = &sequencer;
  osc.wavetable_input = new ModuleConstant(0); // Select the first wavetable
  
  // Patch up LFO
  lfo.frequency_input = inputs[PARAM2_INPUT];  // Control the frequency using the [2] knob
  lfo.wavetable_input = new ModuleConstant(0); // select the first wavetable
  
  // Patch up lowpass filter
  lowpass_filter.audio_input = &osc;           // Route the audio from the oscillator into the filter
  lowpass_filter.cutoff_input = &lfo;          // Control the filter cutoff using the LFO
  lowpass_filter.resonance_input = new ModuleConstant(0);  // Set the resonance to 0
  
  // Patch up VCA
  // vca.cv_input = inputs[RESET_INPUT];
  // vca.cv_input = new ModuleClock(120);

  vca.cv_input = inputs[PARAM1_INPUT];         // Control the VCA level using the [1] knob
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
