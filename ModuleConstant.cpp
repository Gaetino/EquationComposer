#include "Arduino.h"
#include "ModuleConstant.h"
#include "Defines.h"

ModuleConstant::ModuleConstant(int value)
{
  this->value = value;
}

uint32_t ModuleConstant::run()
{
  return(this->value);
}

void ModuleConstant::setValue(uint32_t new_value)
{
  this->value = new_value;
}

uint32_t ModuleConstant::getValue()
{
  return(this->value);
}


