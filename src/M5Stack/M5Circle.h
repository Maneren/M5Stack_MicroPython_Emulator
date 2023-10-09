#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_Drawables.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * M5Circle class wrapper
 */
class M5Circle {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "M5Circle"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def(py::init<int, int, int, int, int>())
        .def("setPosition", &M5Circle::setPosition);
  }

private:
  std::shared_ptr<CDrawable_Circle> mObj;

public:
  M5Circle() {
    //
  }

  M5Circle(int x, int y, int r, int borderColor, int brushColor) {
    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Circle>(
            x, y, r, borderColor, brushColor);
  }

  void setPosition(int x, int y) { mObj->Set_Position(x, y); }

  virtual ~M5Circle() = default;

  // TODO
};
