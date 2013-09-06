#include "Arduino.h"
#include "ModuleEquationLooper.h"
#include "Defines.h"

// Note: It would be convienient if there were 16, 32, or 64 equations
// because it would then be easy to map the incoming CV signal, which 
// ranges from 0 to 4095 to a range such as 0 to 15.

ModuleEquationLooper::ModuleEquationLooper()
{
  w = 0;
  p = 0;
  q = 0;
  fixed_point_20_12_index = 0;
}

uint32_t ModuleEquationLooper::run()
{
  // Read inputs
  // For loop_start and loop_length, I'm dropping some of the least significant 
  // bits in order to remove any noise from the incoming signal.
  
  increment_by = this->sample_rate_input->run();              // range: 0 - 4095
  loop_length = (this->loop_length_input->run() >> 3) * 150;  // range: (0 - 511) * 150
  loop_start = (this->loop_start_input->run() >> 3) * 800;    // range: (0 - 511) * 800
  equation = this->equation_input->run() >> 8;                // range: 0 - 15, which is 2^4
  
  fixed_point_20_12_index += increment_by;
  
  // shift off th 12 bits used for fractional numbers, which leaves us with a 20 bit number
  playback_position = loop_start + (fixed_point_20_12_index >> 12); 
  
  if(playback_position >= (loop_start + loop_length))
  {
    playback_position = 0;
    fixed_point_20_12_index = 0;
  }
  
  uint32_t t = playback_position;
  
  switch(equation)
  {
    
    case 0:
    
      // Arppegiation
      p = t/(512+16*64)%64 & (t*(232));
      q = t/(t/(4096) % 5 + 1)%p;
      w = (t>>q) + (t/(t>>15&5)>>p);
      break;
      
    case 1:
      w = ((t*(t>>8|t>>2)&3&t>>8))^(t&t>>4|t>>6);    
      break;
      
    case 2:
      w = (23-((266/t)^2|t^922+2))*2/2*((t+23)>>34%22);    
      break;  
  
    case 3: // From http://canonical.org/~kragen/bytebeat/
      w = ((t<<1)^((t<<1)+(t>>7)&t>>12))|t>>(4-(1^7&(t>>19)))|t>>7; 
      break;  
      
    case 4: // from http://entropedia.co.uk/generative_music_1.2_beta
      w = t*((t>>9|t>>13)&25&t>>6);
      break;      
      
    case 5: // from https://github.com/erlehmann/algorithmic-symphonies/blob/master/quatsi-11-8-7
      w = ((t/6>>11)^(t/6>>8)&(t/6>>7)*t);
      break;      
      
    case 6: // from https://github.com/erlehmann/algorithmic-symphonies/blob/master/rolling
      w = ((t*9 & t>>4) | (t*5 & t>>7) | (t*3 & t/400)) -1;
      break;
      
    case 7: // from blueberry 2011-10-05 http://pouet.net/topic.php?which=8357&page=12
      // TODO: Troubleshoot why this doesn't play correctly
      // compare it to 
      w = (t*(((t>>9)^((t>>9)-1)^1)%13));
      break; 
      
    case 8: // tonic 2011-10-01 http://pouet.net/topic.php?which=8357&page=5 "mr. arpeggiator playing a solo"
      w = (t/8)>>(t>>9)*t/((t>>14&3)+4);
      break;
      
    case 9: // xpansive 2011-09-29 http://pouet.net/topic.php?which=8357&page=2 "Lost in Space"
      w = ((t*(t>>8|t>>9)&46&t>>8))^(t&t>>13|t>>6);
  }
  
  // I really don't know why this value needs to be shifted up 4 places,
  // but it does, in order to make the equation playback sound correct.
  return(w << 4);
}
