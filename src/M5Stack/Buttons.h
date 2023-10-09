#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * Base for all buttons of M5Stack Core2 device
 */
template <typename TChild> class Button_Base {
public:
  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {

    bool (*wasPressedRet)() = &Button_Base::wasPressed;
    void (*wasPressedCb)(PyObject *) = &Button_Base::wasPressed;
    bool (*wasReleasedRet)() = &Button_Base::wasReleased;
    void (*wasReleasedCb)(PyObject *) = &Button_Base::wasReleased;

    // TODO: wasPressedFor, ...

    return obj.def("wasPressed", wasPressedRet)
        .def("wasPressed", wasPressedCb)
        .def("wasReleased", wasReleasedRet)
        .def("wasReleased", wasReleasedCb)
        .def("isPressed", &Button_Base::isPressed)
        .def("isReleased", &Button_Base::isReleased);
  }

public:
  virtual ~Button_Base() = default;

  static bool wasPressed() {
    return CM5Stack_VM::Instance()->Get_Buttons()->wasPressed(
        TChild::Get_Button());
  }

  static void wasPressed(PyObject *obj) {
    CM5Stack_VM::Instance()->Get_Buttons()->wasPressedRegisterCallback(
        TChild::Get_Button(), obj);
  }

  static bool wasReleased() {
    return CM5Stack_VM::Instance()->Get_Buttons()->wasReleased(
        TChild::Get_Button());
  }

  static void wasReleased(PyObject *obj) {
    CM5Stack_VM::Instance()->Get_Buttons()->wasReleasedRegisterCallback(
        TChild::Get_Button(), obj);
  }

  static bool isPressed() {
    return CM5Stack_VM::Instance()->Get_Buttons()->isPressed(
        TChild::Get_Button());
  }

  static bool isReleased() {
    return CM5Stack_VM::Instance()->Get_Buttons()->isReleased(
        TChild::Get_Button());
  }
};

/*
 * Button A (left)
 */
class ButtonA : public Button_Base<ButtonA> {

public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "buttonA"; }

public:
  static CM5Buttons::Button Get_Button() { return CM5Buttons::Button::A; }
};

/*
 * Button B (middle)
 */
class ButtonB : public Button_Base<ButtonB> {

public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "buttonB"; }

public:
  static CM5Buttons::Button Get_Button() { return CM5Buttons::Button::B; }
};

/*
 * Button C (right)
 */
class ButtonC : public Button_Base<ButtonC> {

public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "buttonC"; }

public:
  static CM5Buttons::Button Get_Button() { return CM5Buttons::Button::C; }
};
