/*
 *   +----------------------+
 *   | ModuleEquationLooper |
 *   |----------------------|
 *   > sample_rate_input    |
 *   > loop_length_input    |
 *   > loop_start_input     |
 *   > equation_input       |
 *   |                output>
 *   +----------------------+
 *
 */
 
#ifndef ModuleEquationLooper_h
#define ModuleEquationLooper_h

#include "Arduino.h"
#include "Module.h"

class ModuleEquationLooper : public Module
{
  
  public:
    ModuleEquationLooper();
    uint32_t compute();
    
    // Inputs
    Module *sample_rate_input;
    Module *loop_start_input;
    Module *loop_length_input;
    Module *equation_input;
    
  private:

    int equation;
    int rate;

    uint32_t loop_start; 
    uint32_t old_loop_start;
    uint32_t loop_length;
    uint32_t playback_position;
    
    uint32_t p;           // Temporary variable for use in equations
    uint32_t q;           // Temporary variable for use in equations
    uint32_t w;           // The final output of the equation
   
    // 19.13 fixed point number (using the upper 19 bits for holding the usable
    // numbers and an additional 13 bits (0-8192) for simulating fractional values for
    // use when incrementing the variable fractional values
    uint32_t fixed_point_20_12_index;
    uint32_t increment_by;
};

#endif
