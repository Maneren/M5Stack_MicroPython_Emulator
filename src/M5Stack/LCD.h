#pragma once

#include "../M5Stack_MicroPython.h"

#include <string>

/*
 * LCD class encapsulating the "lcd" submodule
 */
class LCD {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "lcd"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {

    void (*printFnc1)(py::str, int, int) = &LCD::print;
    void (*printFnc2)(py::str, int, int, int) = &LCD::print;

    // TODO: most of the functions

    return obj.def("clear", &LCD::clear)
        .def("print", printFnc1)
        .def("print", printFnc2)
        .def_readonly("BLACK", &LCD::BLACK)
        .def_readonly("NAVY", &LCD::NAVY)
        .def_readonly("DARKGREEN", &LCD::DARKGREEN)
        .def_readonly("DARKCYAN", &LCD::DARKCYAN)
        .def_readonly("MAROON", &LCD::MAROON)
        .def_readonly("PURPLE", &LCD::PURPLE)
        .def_readonly("OLIVE", &LCD::OLIVE)
        .def_readonly("LIGHTGREY", &LCD::LIGHTGREY)
        .def_readonly("DARKGREY", &LCD::DARKGREY)
        .def_readonly("BLUE", &LCD::BLUE)
        .def_readonly("GREEN", &LCD::GREEN)
        .def_readonly("CYAN", &LCD::CYAN)
        .def_readonly("RED", &LCD::RED)
        .def_readonly("MAGENTA", &LCD::MAGENTA)
        .def_readonly("YELLOW", &LCD::YELLOW)
        .def_readonly("WHITE", &LCD::WHITE)
        .def_readonly("ORANGE", &LCD::ORANGE)
        .def_readonly("GREENYELLOW", &LCD::GREENYELLOW)
        .def_readonly("PINK", &LCD::PINK)
        // convenience defines (not defined in M5Stack MicroPython)
        .def_readonly("NONE", &LCD::NONE)
        .def_readonly("TRANSPARENT", &LCD::NONE);
  }

public:
  LCD() {
    //
  }

  virtual ~LCD() = default;

  static void clear() {
    auto scrn = CM5Stack_VM::Instance()->Get_Screen();

    scrn->Clean();
  }

  static void print(py::str text, int x, int y) {
    std::string txt = py::extract<std::string>(text);

    auto scrn = CM5Stack_VM::Instance()->Get_Screen();

    scrn->Print_Text(txt, x, y);
  }

  static void print(py::str text, int x, int y, int color) {
    std::string txt = py::extract<std::string>(text);

    auto scrn = CM5Stack_VM::Instance()->Get_Screen();

    scrn->Print_Text(txt, x, y);
  }

  static constexpr int BLACK = 0x000000;
  static constexpr int NAVY = 0x000080;
  static constexpr int DARKGREEN = 0x006400;
  static constexpr int DARKCYAN = 0x008B8B;
  static constexpr int MAROON = 0x800000;
  static constexpr int PURPLE = 0xCC8899;
  static constexpr int OLIVE = 0x808000;
  static constexpr int LIGHTGREY = 0xD3D3D3;
  static constexpr int DARKGREY = 0x555555;
  static constexpr int BLUE = 0x0000FF;
  static constexpr int GREEN = 0x00FF00;
  static constexpr int CYAN = 0x00FFFF;
  static constexpr int RED = 0xFF0000;
  static constexpr int MAGENTA = 0xFF00FF;
  static constexpr int YELLOW = 0xFFFF00;
  static constexpr int WHITE = 0xFFFFFF;
  static constexpr int ORANGE = 0xFFA500;
  static constexpr int GREENYELLOW = 0xADFF2F;
  static constexpr int PINK = 0xFFC0CB;
  static constexpr int NONE = 0xFFFFFFFF;
};
