#ifndef ModuleEquationPlayer_h
#define ModuleEquationPlayer_h

#include "Arduino.h"
#include "Module.h"

class ModuleEquationPlayer : public Module
{
  
  public:
    ModuleEquationPlayer();
    uint32_t compute();
    
    // Inputs
    Module *equation_input;
    Module *sample_rate_input;
    Module *param1_input;
    Module *param2_input;
    Module *param3_input;
    Module *reset_input;
    
  private:
    int equation;
    uint32_t t;           // Accumulator used in equations 
    uint32_t p;           // Temporary variable for use in equations
    uint32_t q;           // Temporary variable for use in equations
    uint32_t w;           // The final output of the equation
    
    uint32_t p1;
    uint32_t p2;
    uint32_t p3;
    
    uint32_t reset;
    
   
    // 19.13 fixed point number (using the upper 19 bits for holding the usable
    // numbers and an additional 13 bits (0-8192) for simulating fractional values for
    // use when incrementing the variable fractional values
    uint32_t fixed_point_20_12_index;
    uint32_t increment_by;
};

#endif
