#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"
#include "Pin.h"

#include <iostream>
#include <string>

/*
 * UART class wrapper
 */
class UART {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "UART"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {

    py::object (UART::*readAll)() = &UART::read;
    py::object (UART::*readCount)(int) = &UART::read;

    return obj
        .def(py::init<int, int, int>()) //, py::args("channel", "tx", "rx"))
                                        ////TODO: implement this somehow, Boost
                                        // does not seem to support it
        .def("init", &UART::init, py::args("baud", "bits", "parity", "stop"))
        .def("read", readAll)
        .def("read", readCount)
        .def("readLine", &UART::readLine)
        .def("any", &UART::any)
        .def("write", &UART::write);
  }

private:
  // selected UART channel - defaults to 1 as it is the first user available
  // UART
  CM5UART::Channel mChannel = CM5UART::Channel::Channel_1;

public:
  UART() {
    //
  }

  UART(int channel, int tx, int rx) {
    auto vm = CM5Stack_VM::Instance();

    // allocate pins
    vm->Get_GPIO()->Set_Pin_Mode(tx, Pin::INOUT);
    vm->Get_GPIO()->Set_Pin_Mode(rx, Pin::INOUT);

    switch (channel) {
    case 0:
      mChannel = CM5UART::Channel::Channel_0;
      break;
    case 1:
      mChannel = CM5UART::Channel::Channel_1;
      break;
    case 2:
      mChannel = CM5UART::Channel::Channel_2;
      break;
    }
  }

  virtual ~UART() = default;

  void init(int baud, int bits, int *parity, int stop) {
    // this has no effect in emulation
  }

  py::object read() {
    // convert to byte array as MicroPython expects it
    return py::object(py::handle<>(PyBytes_FromString(
        CM5Stack_VM::Instance()->Get_UART()->Read(mChannel, true).c_str())));
  }

  py::object read(int count) {
    // convert to byte array as MicroPython expects it
    return py::object(
        py::handle<>(PyBytes_FromString(CM5Stack_VM::Instance()
                                            ->Get_UART()
                                            ->Read(mChannel, true, count)
                                            .c_str())));
  }

  py::object readLine() {
    // convert to byte array as MicroPython expects it
    return py::object(
        py::handle<>(PyBytes_FromString(CM5Stack_VM::Instance()
                                            ->Get_UART()
                                            ->Read_Line(mChannel, true)
                                            .c_str())));
  }

  bool any() {
    return !(CM5Stack_VM::Instance()->Get_UART()->Empty(mChannel, true));
  }

  void write(py::str str) {
    std::string txt = py::extract<std::string>(str);

    CM5Stack_VM::Instance()->Get_UART()->Write(mChannel, true, txt);
  }
};
