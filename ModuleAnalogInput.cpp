#include "ModuleAnalogInput.h"
#include "Defines.h"

ModuleAnalogInput::ModuleAnalogInput(int input_pin)
{
  this->value = 0;
  this->pin = input_pin;
}

uint32_t ModuleAnalogInput::read()
{
    // analogRead resolution is set to 10 bits, so it's necessary
    // to convert this input to 12 bits to cover the entire 0 - 4095 
    // range that's standard for all modules.
    this->value = analogRead(this->pin) << 2;
    return(this->value);
}

// I'm not really sure why I have to redefine this 
// method and not just call the version in the base
// class?  My C++ is obviously a bit rusty.

uint32_t ModuleAnalogInput::run()
{ 
  return(this->value);
}
