#pragma once

#include "../BoostPythonDefs.h"

#include <iostream>

/*
 * ADC class encapsulating Analog-To-Digital converter submodule
 */
class ADC {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "ADC"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) { return obj; }

public:
  ADC() {
    //
  }

  virtual ~ADC() = default;

  // TODO
};
