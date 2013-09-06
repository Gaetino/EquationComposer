#include "ModuleDigitalInput.h"
#include "Defines.h"

ModuleDigitalInput::ModuleDigitalInput(int input_pin)
{
  this->value = 0;
  this->pin = input_pin;
}

uint32_t ModuleDigitalInput::read()
{
    this->value = digitalRead(this->pin);
    return(this->value * MAX_CV);
}

uint32_t ModuleDigitalInput::run()
{ 
  return(this->value);
}
