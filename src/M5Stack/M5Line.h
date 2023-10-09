#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_Drawables.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * M5Line class wrapper
 */
class M5Line {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "M5Line"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def(py::init<int, int, int, int, int>())
        .def(py::init<int, int, int, int, int, int>())
        .def("setSize", &M5Line::setSize)
        .def_readonly("PLINE", &M5Line::PLINE);
  }

private:
  std::shared_ptr<CDrawable_Line> mObj;

public:
  M5Line() {
    //
  }

  M5Line(int type, int x1, int y1, int x2, int y2) {
    mObj = CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Line>(
        x1, y1, x2, y2);
  }

  M5Line(int type, int x1, int y1, int x2, int y2, int color) {
    mObj = CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Line>(
        x1, y1, x2, y2, color);
  }

  void setSize(int x1, int y1, int x2, int y2) {
    mObj->Set_Position(x1, y1, x2, y2);
  }

  virtual ~M5Line() = default;

  // default line mode
  static constexpr int PLINE = 0;
};
