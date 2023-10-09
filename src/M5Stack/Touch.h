#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * Touch class wrapper to provide "touch" submodule
 */
class Touch {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "touch"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def("read", &Touch::read);
  }

public:
  Touch() {
    //
  }

  static py::tuple read() {
    py::list a;

    auto scrn = CM5Stack_VM::Instance()->Get_Screen();
    if (scrn->Is_Touching()) {
      a.append(scrn->Get_Touch_X());
      a.append(scrn->Get_Touch_Y());
    } else {
      // append zeroes if no touch is in progress
      // TODO: find out actual values
      a.append(0);
      a.append(0);
    }
    return py::tuple(a);
  }

  virtual ~Touch() = default;
};
