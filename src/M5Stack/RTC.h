#pragma once

#include "../BoostPythonDefs.h"

#include <iostream>
#include <ctime>

/*
 * RTC class wrapper for "rtc" submodule
 */
class RTC {
	public:
		// Self_Init_Python_Object concept
		static constexpr const char* Get_Class_Name() {
			return "rtc";
		}

		// Self_Init_Python_Object concept
		static auto&& Define_Class_Contents(auto&& obj) {
			return obj
				.def("settime", &RTC::settime, py::args("source", "host", "tzone"))
				.def("datetime", &RTC::datetime);
		}

	public:
		RTC() {
			//
		}

		static void settime(py::str source, py::str host, int tzone) {
			// source = 'ntp'
			// host = remote host for NTP sync
			// tzone = desired timezone

			// TODO: used this somehow?
		}

		static py::tuple datetime() {
			// returns array: Y M D ? H I S

			std::time_t t = std::time(nullptr);
#ifdef _WIN32
			std::tm ti;
			localtime_s(&ti, &t);

			std::tm* const tinfo = &ti;
#else
			std::tm* const tinfo = std::localtime(&t);
#endif

			py::list a;

			if (tinfo) {
				a.append(1900 + tinfo->tm_year);
				a.append(tinfo->tm_mon + 1);
				a.append(tinfo->tm_mday);
				a.append(0); // TODO: find the actual value
				a.append(tinfo->tm_hour);
				a.append(tinfo->tm_min);
				a.append(tinfo->tm_sec);
			}
			else {
				// fill with zeroes if we weren't able to obtain time
				for (int i = 0; i < 7; ++i) {
					a.append(0);
				}
			}

			return py::tuple(a);
		}

		virtual ~RTC() = default;
};
