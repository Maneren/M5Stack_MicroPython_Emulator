#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * M5Screen class wrapper
 */
class M5Screen {
	public:
		// Self_Init_Python_Object concept
		static constexpr const char* Get_Class_Name() {
			return "M5Screen";
		}

		// Self_Init_Python_Object concept
		static auto&& Define_Class_Contents(auto&& obj) {
			return obj.def("clean_screen", &M5Screen::clean_screen)
				.def("set_screen_bg_color", &M5Screen::set_screen_bg_color)
				.def("set_screen_brightness", &M5Screen::set_screen_brightness)
				.def("load_screen", &M5Screen::load_screen)
				.def("get_new_screen", &M5Screen::get_new_screen)
				.def("get_act_screen", &M5Screen::get_act_screen)
				.def("del_screen", &M5Screen::del_screen);
		}

	public:
		virtual ~M5Screen() = default;

		virtual void clean_screen() {
			auto scrn = CM5Stack_VM::Instance()->Get_Screen();

			scrn->Clean();
		}

		virtual void set_screen_bg_color(int color) {
			auto scrn = CM5Stack_VM::Instance()->Get_Screen();

			scrn->Set_Background_Color(color);
		}

		virtual void set_screen_brightness(int brightness) {
			auto scrn = CM5Stack_VM::Instance()->Get_Screen();

			scrn->Set_Brightness(brightness);
		}

		virtual void load_screen(int scr) {
			// NYI
		}

		virtual void get_new_screen() {
			// NYI
		}

		virtual void get_act_screen() {
			// NYI
		}

		virtual void del_screen() {
			// NYI
		}
};
