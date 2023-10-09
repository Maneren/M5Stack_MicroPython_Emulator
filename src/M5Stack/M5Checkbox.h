#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_Drawables.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * M5Checkbox class wrapper
 */
class M5Checkbox {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "M5Checkbox"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def(py::init<py::str, int, int, int, int>())
        .def(py::init<py::str, int, int, int, int, int>())
        .def(py::init<py::str, int, int, int, int, int, int>())
        .def("checked", &M5Checkbox::checked)
        .def("unchecked", &M5Checkbox::unchecked)
        .def("set_checked", &M5Checkbox::set_checked);
  }

private:
  std::shared_ptr<CDrawable_Checkbox> mObj;

public:
  M5Checkbox() {
    //
  }

  M5Checkbox(py::str text, int x, int y, int w, int h) {

    std::string txt = py::extract<std::string>(text);

    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Checkbox>(
            txt, x, y, w, h);
  }

  M5Checkbox(py::str text, int x, int y, int w, int h, int textColor) {

    std::string txt = py::extract<std::string>(text);

    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Checkbox>(
            txt, x, y, w, h, textColor);
  }

  M5Checkbox(py::str text, int x, int y, int w, int h, int textColor,
             int checkColor) {

    std::string txt = py::extract<std::string>(text);

    mObj =
        CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Checkbox>(
            txt, x, y, w, h, textColor, checkColor);
  }

  void checked(PyObject *cb) { mObj->Register_Checked_Callback(cb); }

  void unchecked(PyObject *cb) { mObj->Register_Unchecked_Callback(cb); }

  void set_checked(bool state) { mObj->Set_Checked(state); }

  virtual ~M5Checkbox() = default;
};
