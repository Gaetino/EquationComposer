/*
#include "Arduino.h"
#include "ModuleADSR.h"
#include "Defines.h"

ModuleADSR::ModuleADSR()
{
  this->output_range_low = 0;
  this->output_range_high = 255;
  
  this->counter = 0;
  this->output = 0;
  this->state = ADSR_INACTIVE;
  
  this->setTimes(10,500,500,500); // default ADSR durations
  this->setLevels(255,100); // default attack, decay levels
}

// Shorthand way of setting all of the times (in milliseconds)

void ModuleADSR::setTimes(uint32_t attack_time, uint32_t decay_time, uint32_t sustain_time, uint32_t release_time)
{
  // The values that are stored for attack_time, decay_time, sustain_time, and
  // release_time represent the target value for this->counter to reach, assuming
  // that it is incremented at SAMPLE_RATE per second.
  
  this->attack_time   = (float)(SAMPLE_RATE * attack_time)/1000.0;
  this->decay_time    = (float)(SAMPLE_RATE * decay_time)/1000.0;
  this->sustain_time  = (float)(SAMPLE_RATE * sustain_time)/1000.0;
  this->release_time  = (float)(SAMPLE_RATE * release_time)/1000.0;
}

// Shorthand way of setting all of the ADSR levels

void ModuleADSR::setLevels(uint32_t attack_level, uint32_t decay_level)
{
  this->attack_level  = attack_level;
  this->decay_level   = decay_level;
}


// Long winded ways of setting the individual attack, decay, sustain, and release times

void ModuleADSR::setAttackTime(uint32_t duration_in_milliseconds)
{
  this->attack_time = (float)(SAMPLE_RATE * duration_in_milliseconds)/1000.0;
}

void ModuleADSR::setDecayTime(uint32_t duration_in_milliseconds)
{
  this->decay_time = (float)(SAMPLE_RATE * duration_in_milliseconds)/1000.0;
}

void ModuleADSR::setSustainTime(uint32_t duration_in_milliseconds)
{
  this->sustain_time = (float)(SAMPLE_RATE * duration_in_milliseconds)/1000.0;
}

void ModuleADSR::setReleaseTime(uint32_t duration_in_milliseconds)
{
  this->release_time = (float)(SAMPLE_RATE * duration_in_milliseconds)/1000.0;
}

// Long winded ways of setting the levels for each stage of the ADSR

void ModuleADSR::setAttackLevel(int level)
{
  this->attack_level = level;
}

void ModuleADSR::setDecayLevel(int level)
{
  this->decay_level = level;
}


uint32_t ModuleADSR::run()
{
  uint32_t trigger = this->trigger_input->run();
  trigger = this->mapInput(trigger, this->trigger_input, 0, 1);
  
  // TODO: Only trigger ADSR if trigger has changed from 0 to 1
  
  if(trigger == 1)
  {
    state = ADSR_ATTACK;
    counter = 1;
  }
  
  
  switch(this->state)
  {
    case ADSR_ATTACK: 
      
      if(counter == attack_time) 
      {
        state = ADSR_DECAY;
        counter = 1;
        output = attack_level;
      }
      else
      {
        output = (float)((float)counter / (float)attack_time) * attack_level;
      }
      
      break;    
      
    case ADSR_DECAY:

      if(counter == decay_time) 
      {
        state = ADSR_SUSTAIN;
        counter = 1;
        output = decay_level;
      }
      else
      {
        output = attack_level - ((float)((float)counter / (float)decay_time) * (attack_level - decay_level));
      }

      break;

    case ADSR_SUSTAIN:
      
      if(counter == sustain_time)
      {
        state = ADSR_RELEASE;
        counter = 1;
      }
      else
      {
        // no need to change the value of output.  It should be set correctly already.
      }
      
      break;

    case ADSR_RELEASE:
      
      if(counter == release_time)
      {
        output = 0;
        counter = 1;
        state = ADSR_INACTIVE;
      }
      else
      {
        output = decay_level - ((float)((float)counter / (float)release_time) * decay_level);
      }
      
      break;
  }
  
  if (state != ADSR_INACTIVE) counter++;
  
  return(output);
}
*/
