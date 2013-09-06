#ifndef Module_h
#define Module_h

#include "Arduino.h"

class Module
{
  public:
  
    // Methods
    Module(); 
    virtual uint32_t run() = 0;  // Pure virtual function.  This must be implemented in the derived class.
};

#endif
