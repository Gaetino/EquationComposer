#include "Arduino.h"
#include "ModuleEquationPlayer.h"
#include "Defines.h"

ModuleEquationPlayer::ModuleEquationPlayer()
{
  t = 0;  // Set the counter to 0
  w = 0;  // Initialize variables used for temporary storage
  p = 0;
  q = 0;
  p1 = 0;
  p2 = 0;
  p3 = 0;
  reset = 0;
  fixed_point_20_12_index = 0;
}

uint32_t ModuleEquationPlayer::compute()
{

  // Read inputs
  equation     = this->readInput(equation_input) >> 7; // range: 0 - 31, which is 2^5  
  increment_by = this->readInput(sample_rate_input);   // range: 0 - 4095
  p1 = this->readInput(param1_input) >> 4;    // range: 0 - 255 (2^8)
  p2 = this->readInput(param2_input) >> 4;    // range: 0 - 255 (2^8)
  p3 = this->readInput(param3_input) >> 4;    // range: 0 - 255 (2^8)
  reset = this->readInput(reset_input) >> 4;  // range: 0 - 255 (2^8)
  
  fixed_point_20_12_index += increment_by;
  
  // shift off th 12 bits used for fractional numbers, which leaves us with a 20 bit number
  t = fixed_point_20_12_index >> 12; 
  
  switch(equation)
  {
    
    case 0:
    
      // Arppegiation
      p = t/(512+16*64)%64 & (t*(232+p2));
      q = t/(t/(4096 + p3) % 5 + 1)%p;
      w = (t>>q) + (t/(t>>15&5)>>p);
      break;      

    case 1:
      w = (t*(p1/(t%+10))&t>>p3)&((t*3)&t>>5)|(t>>4&p2);
      break;
      
    case 2:
      w = ((t*(t>>8|t>>p3)&p2&t>>8))^(t&t>>p1|t>>6);
      break;
      
    case 3:
      w = (p1&t%p3)^(t/p2);
      break;
      
    case 4:
      w = (t*(4|7&t>>13)>>((~t>>p1)&1)&p3) + ((t)*(t>>11&t>>13)*((~t>>9)&3)&p2);
      break; 
 
    case 5:
      w = (t>>p1|t|t>>6)*p3+4*(t&t>>p2|t>>6);
      break;
      
    case 6:
      w = t&((t>>2)/(t%p1))|((t<<2)/((t+2000*50)%p2))|(t*p3&t>>7);
      break;

    case 7:
      w = ((t % p1 >> p2) & p3) * (t>>12);
      break;         

    case 8:
      w = ((t%(p1+(t%p2)))^(t>>p3))*2;
      break;         

    case 9:
      w = t|(t+p1*p2)*p3;
      break; 
      
    case 10:
      w = ((t%(512-(t*351)+16))^((t>>p1)))*(2+(t>>14)%6)|((t*p2)&(t>>5))-p3;
      break; 

    case 11:
      w = (t*5&t>>11|t*9&t>>20|t*2&t>>p1|t*p2&t>>9)&p3;
      break; 

    case 12:
      w = ((t%p1>>2)&p2)*(t>>p3);
      break;
      
    case 13:
      w = ((t-467)^(p1-(w%p3)))+p2;
      break;

    case 14:
      w = (t+w+p2/p1)%(p1|t+p3);
      break;
      
    case 15:
      w = (t&p1)-(t/p2)/w/p3;
      break;

    case 16:
      w = (((1^t)<<((t/170)*p3))|p2^(p1<<t));
      break;
      
    case 17:
      w = 2^(t^p3)-(w/p2)^t%p1;
      break;
      
    case 18:
      w = (t*6)^2|(25^t)|t+4;
      break;
      
    case 19:
      w = (~t/p2|(t*p1))^(t*p3&(t>>88))&t;
      break;
      
    case 20:
      w = ( t* (( t>>9| t>>p1 ) & p2)) & p3;
      break;  

    case 21:
      w = (t*9&t>>4|t*p1&t>>7|t*3&t/p2)-1;
      break;
      
    case 22:
      w = (t%p1-p2-p1%t^p3);
      break;
      
    case 23:
      w = ((p1/t%(91&p2+p3))^((t>>8)))*(2+(t>>1)%5*p2|t)-(w>>2);
      break;
      
    case 24:
      w = ((p1/t%(91&p2+p3))^((t>>8)))*(2+(t>>1)%5*p2|t)-(w>>2);
      break; 
      
    case 25:
      w = (w/133^w-(83/p2-t))*p1/22;
      break;
      
    case 26:
      w = (p2>>((((p1%w)+w)>>t)^((t*t)/t/1))^5999*p1)%(t%p1*14-t);
      break;
      
    case 27:
      w = (p1-t%p1^w)*t/p1/p2>>9999%w;
      break;
      
    case 28:
      // Sunshine audio eurorack x6
      w = ((p1>>p3%26)*w)<<t%(11>>t)|p1<<t*p2;
      break;
      
    case 29:
      // Sunshine audio eurorack x7
      w = ((93<<w)-p1*118-p3^t/((12-p1*p2|t)%p1));
      break;
      
    case 30: 
      // Sunshine audio eurorack x8
      w = (w>>t<<w-p2)|t-p2*w+p1;
      break;
      
    case 31:
      // idm3
      w=(((t%4069)^p1+t)+(w/257)+(w/300%t)+(w/p2^t%65))%(p3*4);
      break;
      
    case 32:
      // Chewie 1
      w=(p1-((p1/t)^p1|t^922+p1))*p1/p1*((t+p2)>>p2%19);
      break;
    
    /*
    case 33: 
      // The smoker 3
      w = w^t >> (t/6988*t%p1)+(t<<t/(p2 * 4));
      break;
      
    case 34: 
      // Passthrough test
      w = p1;
      break;
    */
    
    // If you add more programs, be sure to update the
    // variable number_of_equations at the top of this script
  }

  return(w << 4);
}
