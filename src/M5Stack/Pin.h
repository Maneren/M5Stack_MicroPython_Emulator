#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * Pin class wrapper
 */
class Pin {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "Pin"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {

    int (Pin::*value_get)() = &Pin::value;
    void (Pin::*value_set)(int) = &Pin::value;

    return obj.def(py::init<int>())
        .def(py::init<int, int>())
        .def(py::init<int, int, int>())
        .def(py::init<int, int, int, int>())
        .def("on", &Pin::on)
        .def("off", &Pin::off)
        .def("value", value_get)
        .def("value", value_set)
        .def_readonly("IN", &Pin::IN_)
        .def_readonly("OUT", &Pin::OUT_)
        .def_readonly("OUT_OD", &Pin::OUT_OD)
        .def_readonly("INOUT", &Pin::INOUT)
        .def_readonly("OPEN_DRAIN", &Pin::OPEN_DRAIN)
        .def_readonly("PULL_UP", &Pin::PULL_UP)
        .def_readonly("PULL_DOWN", &Pin::PULL_DOWN)
        .def_readonly("PULL_HOLD", &Pin::PULL_HOLD)
        .def_readonly("PULL_FLOAT", &Pin::PULL_FLOAT);
  }

private:
  // pin number
  int mPin = 0;

public:
  Pin() {
    //
  }

  Pin(int pin) : mPin(pin) {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_Mode(pin, _OUT);
  }

  Pin(int pin, int mode) : mPin(pin) {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_Mode(pin, mode);
  }

  Pin(int pin, int mode, int pull) : mPin(pin) {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_Mode(pin, mode);
  }

  Pin(int pin, int mode, int pull, int value) : mPin(pin) {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_Mode(pin, mode);
  }

  virtual ~Pin() = default;

  virtual void on() {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_State(mPin, 1);
  }

  virtual void off() {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_State(mPin, 0);
  }

  virtual int value() {
    return CM5Stack_VM::Instance()->Get_GPIO()->Get_Pin_State(mPin);
  }

  virtual void value(int state) {
    CM5Stack_VM::Instance()->Get_GPIO()->Set_Pin_State(mPin, state);
  }

  static constexpr int _IN = 0;
  static constexpr int _OUT = 1;
  static constexpr int _OUT_OD = 2;
  static constexpr int _INOUT = 3;
  static constexpr int _OPEN_DRAIN = 4;
  static constexpr int _PULL_UP = 0;
  static constexpr int _PULL_DOWN = 1;
  static constexpr int _PULL_HOLD = 2;
  static constexpr int _PULL_FLOAT = 3;

  static constexpr int IN_ = _IN;
  static constexpr int OUT_ = _OUT;
  static constexpr int OUT_OD = _OUT_OD;
  static constexpr int INOUT = _INOUT;
  static constexpr int OPEN_DRAIN = _OPEN_DRAIN;
  static constexpr int PULL_UP = _PULL_UP;
  static constexpr int PULL_DOWN = _PULL_DOWN;
  static constexpr int PULL_HOLD = _PULL_HOLD;
  static constexpr int PULL_FLOAT = _PULL_FLOAT;
};
