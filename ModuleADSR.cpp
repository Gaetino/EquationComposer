#include "Arduino.h"
#include "ModuleADSR.h"
#include "Defines.h"

ModuleADSR::ModuleADSR()
{
  this->output = 0;
  this->state = ADSR_INACTIVE;
  
  this->set(10,1000,100,100); // default ADSR durations
  
  this->trigged = false;  
}

// 4 parameters to compute :
// attack time (time to reach 100% volume) 
// sustain value (the value where the sound must stop if the sound stay trigged) - % of the volume
// decay time (the time that the sound goes from 100% to sustain value)
// release time (time to go from sustain value to 0)


// The fixed point will be fixed at 19 bits.

void ModuleADSR::set(uint32_t attack_time, uint32_t decay_time, uint32_t sustain, uint32_t release_time)
{
  this->attack_time   = 10000/((attack_time>>2)+1); // 1 ms to 10 s
  this->sustain  = sustain<<7; // convert to 19 bits
  this->decay_time    = (524288-sustain)*50/(((decay_time>>4)+1)*44100); 
  this->release_time  = sustain*200/(((release_time>>4)+1)*44100);
}


void ModuleADSR::setAttackTime(uint32_t value)
{
  this->attack_time   = 10000/((value>>2)+1);
}

void ModuleADSR::setDecayTime(uint32_t value)
{
  this->decay_time    = (524288-sustain)*50/(((decay_time>>4)+1)*44100); 
}

void ModuleADSR::setSustain(uint32_t value)
{
  this->sustain  = value<<7; // convert from 12 bits to 19 bits
}

void ModuleADSR::setReleaseTime(uint32_t value)
{
  this->release_time  = sustain*200/(((release_time>>4)+1)*44100);
}


uint32_t ModuleADSR::compute()
{
  uint32_t trigger = readInput(this->trigger_input);
  
  // if the enveloppe is trigged and was not yet trigged before, we start the enveloppe
  if(trigger >= MID_CV && !trigged)
  {
    state = ADSR_ATTACK;
    trigged = true;
    // Serial.println("trigged");
  }
  
  // if the enveloppe is stopped to be trigged, and was trigged before, we start the release phase
  if(trigger < MID_CV && trigged)
  {
    state = ADSR_RELEASE;
    trigged = false;
    //Serial.println("untrigged");
  }
  
  
  switch(this->state)
  {
    case ADSR_ATTACK: 
      if(output >= 524288) // the volume reaches 100 % volume (19 bits)
      {
        state = ADSR_DECAY; 
        // Serial.println("decay");
      }
      else
      {
        output += attack_time; // we increase the volume until 100 %
      }
      break;    
      
    case ADSR_DECAY:
	
      // We decrease the volume until sustain value is reached
	  
      output -= decay_time;
	  
      if(output<=sustain)
      {
        state = ADSR_SUSTAIN;
	// Serial.println("sustain");
      }
      break;

    // We do nothing in the sustain case. The sound stays played until the trigger is trigged off
	  
    case ADSR_RELEASE:
      
      // We decrease the sound until 0 is reached
	 
      if(output>=release_time)
      {
        output -= release_time;       
      }
      else
      {
        state = ADSR_INACTIVE;
	// Serial.println("end");
	output = 0;
      }
      
      break;
  }
  return (output>>7); // convert from 19 bits to 12 bits
  
}

