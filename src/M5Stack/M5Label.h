#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_Drawables.h"
#include "../M5Stack_MicroPython.h"

/*
 * M5Label class wrapper
 */
class M5Label {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "M5Label"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def(py::init<py::str, int, int, int, int, py::object *>())
        .def("set_text", &M5Label::setText);
  }

private:
  std::shared_ptr<CDrawable_Text> mObj;

public:
  M5Label() {
    //
  }

  M5Label(py::str lab, int x, int y, int color, int font, py::object *parent) {

    std::string str = py::extract<std::string>(lab);

    mObj = CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Text>(
        str, x, y, color);
  }

  void setText(py::str lab) {
    std::string str = py::extract<std::string>(lab);
    mObj->Set_Text(str);
  }

  virtual ~M5Label() = default;
};
