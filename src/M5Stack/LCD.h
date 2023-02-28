#pragma once

#include "../BoostPythonDefs.h"

#include <iostream>
#include <string>

/*
 * LCD class encapsulating the "lcd" submodule
 */
class LCD {
	public:
		// Self_Init_Python_Object concept
		static constexpr const char* Get_Class_Name() {
			return "lcd";
		}

		// Self_Init_Python_Object concept
		static auto&& Define_Class_Contents(auto&& obj) {

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

		static const int BLACK = 0x000000;
		static const int NAVY = 0x000080;
		static const int DARKGREEN = 0x006400;
		static const int DARKCYAN = 0x008B8B;
		static const int MAROON = 0x800000;
		static const int PURPLE = 0xCC8899;
		static const int OLIVE = 0x808000;
		static const int LIGHTGREY = 0xD3D3D3;
		static const int DARKGREY = 0x555555;
		static const int BLUE = 0x0000FF;
		static const int GREEN = 0x00FF00;
		static const int CYAN = 0x00FFFF;
		static const int RED = 0xFF0000;
		static const int MAGENTA = 0xFF00FF;
		static const int YELLOW = 0xFFFF00;
		static const int WHITE = 0xFFFFFF;
		static const int ORANGE = 0xFFA500;
		static const int GREENYELLOW = 0xADFF2F;
		static const int PINK = 0xFFC0CB;
		static const int NONE = 0xFFFFFFFF;
};
