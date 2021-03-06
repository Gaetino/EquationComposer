/*
 ___  __        __  ___ _  __           ___  __        __   __   ___  ___  __  
|___ |  | |  | |__|  |  | |  | |\ |    |    |  | |\/| |__] |  | [__  |___ |__/ 
|___ |_\| |__| |  |  |  | |__| | \|    |___ |__| |  | |    |__| ___] |___ |  \ 
// =============================================================================
       
Copyright 2013 Bret Truchan

  The Equation Composer source code is free software: you can redistribute it 
  and/or modify it under the terms of the GNU General Public License as 
  published by the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
                                                                       
Based on:
  http://rcarduino.blogspot.com/2012/12/arduino-due-dds-part-1-sinewaves-and.html
  Equation playback based on techniques documented by Viznut

Credits:
  Circuit design, parts selection, and manufacturing oversight by John Staskevich
  Front panel design by Hannes Pasqualini
  Sound design by Sunshine Audio and Bret Truchan
  Some equations gather from around the net
  Includes some libraries from Mozzi (http://sensorium.github.io/Mozzi/)
  Additional programming by Gaétan Ro
  Special thanks to Josh from Toppobrillo for his support and mentoring

Equation testing tools:
  http://wurstcaptures.untergrund.net/music/
  http://entropedia.co.uk/generative_music/

TODO:

  - find out how to share the wavetables array between classes without taking 
    up additional memory
  - create mixer module
  - create add/subtract module
  - create ModuleVCClock (where clock is controlled via an input)
  - consider splitting ModuleLFO into: ModuleLFO(int rate) and ModuleVCLFO() 
  - try to port over the reverb effect from Mozzi
  - write documentation (as HTML)
  - add reset input to equation playback module and test
  - use better datatypes than the uint32_t that I use out of laziness
  - add clock division input to ModuleClock
  
// =========================== - 80 column - ===================================
12345678901234567890123456789012345678901234567890123456789012345678901234567890

*/


#include "defines.h"

// Each synth must be included here
#include "SynthEquationPlayer.h"
#include "SynthEquationLooper.h"
#include "SynthSubtractor.h"

#include "ModuleAnalogInput.h"
#include "ModuleDigitalInput.h"
#include "DueTimer.h"

// Setting the debug flag to 1 turns off the timer functions.  This causes the
// code to run slowly, and at that slow frequency the module is inaudible.  
// However, it does allow for us to add Serial.println() calls within the code, 
// which normally woudn't work because the interrupt code gets called at
// a higher frequency than the serial port can function.
//
// #define DEBUG 1

// Global variables
uint32_t equation = 0;
uint32_t output = 0;
double cycle = 0;

// Define the input modules, which are global.  It might seem strange
// to use a "module" just for an input, but it's necessary because of the way
// that the modules are strung together.  Each module can have inputs, and
// these inputs -must be- pointers to other modules.  That's also why there's
// such thing as a ModuleConstant, since we can't set a module's input to a
// number, like 43.  The input modules are global and are passed into each
// Synth via the constructor.

ModuleAnalogInput module_equ_input(PIN_EQU);
ModuleAnalogInput module_sr_input(PIN_SR);
ModuleAnalogInput module_mod_input(PIN_MOD);
ModuleAnalogInput module_param1_input(PIN_PARAM_1);
ModuleAnalogInput module_param2_input(PIN_PARAM_2);
ModuleAnalogInput module_param3_input(PIN_PARAM_3);
ModuleDigitalInput module_reset_input(PIN_RESET);

// Store pointers to the input modules into an array.
// This makes it less messy to pass them into the synth's constructors.

Module *inputs[] = {   
  &module_equ_input,     // equation input
  &module_sr_input,      // sample rate (frequency) input
  &module_mod_input,     // mod input
  &module_param1_input,  // parameter 1 input
  &module_param2_input,  // parameter 2 input
  &module_param3_input,  // parameter 3 input
  &module_reset_input    // reset input
};

// Create the synths
SynthSubtractor synth_subtractor(inputs);
SynthEquationPlayer synth_equation_player(inputs);
SynthEquationLooper synth_equation_looper(inputs);

void setup()
{
    
  // Testing using Serial.println() is difficult because you can't put a 
  // Serial.println() in the code that's called by the timer interrupt.  The only 
  // way I've been able to use Serial.println() is by temporarily removing the 
  // timer and by calling the TC4_Handler() function myself from within the main loop.
  
  #ifdef DEBUG
    Serial.begin(9600);
  #endif
  
  // Set the Due's analog read resolution
  analogReadResolution(ANALOG_READ_RESOLUTION);
  
  // Configure the ADCs to run faster
  // See: http://forum.arduino.cc/index.php/topic,171993.0.html
  // See: http://www.djerickson.com/arduino/
  // Currently commented out.  Eventually I'll try this, but
  // I don't want to introduce any unknowns into the code.
  //
  // REG_ADC_MR = (REG_ADC_MR & 0xFFF0FFFF) | 0x00020000;
  
  // Enable the DAC
  analogWrite(DAC1,0);

  // Configure the interrupt(s) if NOT in debug mode
  #ifndef DEBUG
    Timer0.attachInterrupt(audioRateInterrupt).setFrequency(44100).start();
  #endif
  
  // Set the pinmode for digital pins.  This is not required for the analog inputs.
  pinMode(PIN_RESET, INPUT);
  
}

void loop()
{  
  // In the main loop, the analog and digital inputs are read. The values are 
  // stored in the global input modules as well as being returned.  It wouldn't
  // make sense to poll the Arduino inputs in the timer function TC4_Handler()
  // because that function gets called at a higher frequency than the analog
  // inputs can be read (I'm assuming!).  That's why they're polled here, in
  // the main loop, at a reasonable rate.
  
  equation = module_equ_input.read();
  module_sr_input.read();
  module_mod_input.read();
  module_param1_input.read();
  module_param2_input.read();
  module_param3_input.read();
  module_reset_input.read();
  
  // If in debug mode, then call the audio_rate_interrupt manually
  #ifdef DEBUG
    audio_rate_interrupt();
  #endif
}

// This method gets called at around 44.1 Hz
void audioRateInterrupt()
{

  // When more synths are added, the bit shifting below
  // will need updating to access the additional synths.
  int synth = equation >> 10; // Convert to 2-bit value  

  switch(synth)
  {
    case 1: output = synth_subtractor.run(cycle); break;    
    case 2: output = synth_equation_looper.run(cycle); break;
    case 3: output = synth_equation_player.run(cycle); break;
    case 4: output = synth_equation_player.run(cycle); break;
  }
  
  // I'm using dacc_write_conversion_data() because it writes 12-bit data to
  // the DAC as opposed to 8-bit resolution that analogWrite() does.
  dacc_write_conversion_data(DACC_INTERFACE, output);
  
  // Increment the global time.  This variable is used by modules in their
  // output caching code. (see Module.cpp)
  cycle++;
}

