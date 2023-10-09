#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_Drawables.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * M5Switch class wrapper
 */
class M5Switch {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "M5Switch"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def(py::init<int, int, int, int>())
        .def(py::init<int, int, int, int, int>())
        .def(py::init<int, int, int, int, int, int>())
        .def("on", &M5Switch::on)
        .def("off", &M5Switch::off)
        .def("get_state", &M5Switch::get_state)
        .def("set_state", &M5Switch::set_state);
  }

private:
  std::shared_ptr<CDrawable_Switch> mObj;

public:
  M5Switch() {
    //
  }

  M5Switch(int x, int y, int w, int h) {
    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Switch>(
            x, y, w, h);
  }

  M5Switch(int x, int y, int w, int h, int bgColor) {
    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Switch>(
            x, y, w, h, bgColor);
  }

  M5Switch(int x, int y, int w, int h, int bgColor, int color) {
    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Switch>(
            x, y, w, h, bgColor, color);
  }

  void on(PyObject *cb) { mObj->Register_On_Callback(cb); }

  void off(PyObject *cb) { mObj->Register_Off_Callback(cb); }

  bool get_state() { return mObj->Get_State(); }

  void set_state(bool state) { mObj->Set_State(state); }

  virtual ~M5Switch() = default;
};
