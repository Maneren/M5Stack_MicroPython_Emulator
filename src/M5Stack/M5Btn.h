#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_Drawables.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * M5Btn class wrapper
 */
class M5Btn {
	public:
		// Self_Init_Python_Object concept
		static constexpr const char* Get_Class_Name() {
			return "M5Btn";
		}

		// Self_Init_Python_Object concept
		static auto&& Define_Class_Contents(auto&& obj) {
			return obj
				.def(py::init<py::str, int, int, int, int>())
				.def(py::init<py::str, int, int, int, int, int>())
				.def(py::init<py::str, int, int, int, int, int, int>())
				.def("pressed", &M5Btn::pressed)
				.def("released", &M5Btn::released);
		}

	private:
		std::shared_ptr<CDrawable_Button> mObj;

	public:
		M5Btn() {
			//
		}

		M5Btn(py::str text, int x, int y, int w, int h) {

			std::string txt = py::extract<std::string>(text);

			mObj = CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Button>(txt, x, y, w, h);
		}

		M5Btn(py::str text, int x, int y, int w, int h, int textColor) {

			std::string txt = py::extract<std::string>(text);

			mObj = CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Button>(txt, x, y, w, h, textColor);
		}

		M5Btn(py::str text, int x, int y, int w, int h, int textColor, int bgColor) {

			std::string txt = py::extract<std::string>(text);

			mObj = CM5Stack_VM::Instance()->Get_Screen()->Add_Drawable<CDrawable_Button>(txt, x, y, w, h, textColor, bgColor);
		}

		void pressed(PyObject* cb) {
			mObj->Register_Pressed_Callback(cb);
		}

		void released(PyObject* cb) {
			mObj->Register_Released_Callback(cb);
		}

		virtual ~M5Btn() = default;
};
