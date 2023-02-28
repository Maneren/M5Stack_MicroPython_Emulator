#pragma once

#include "../BoostPythonDefs.h"

#include <iostream>

/*
 * Power class wrapper for "power" submodule
 */
class Power {
	public:
		// Self_Init_Python_Object concept
		static constexpr const char* Get_Class_Name() {
			return "power";
		}

		// Self_Init_Python_Object concept
		static auto&& Define_Class_Contents(auto&& obj) {
			return obj
				.def("isChargeFull", &Power::isChargeFull)
				.def("isCharging", &Power::isCharging)
				.def("getBatteryLevel", &Power::getBatteryLevel)
				.def("getBatVoltage", &Power::getBatVoltage);
		}

	public:
		Power() {
			//
		}

		static bool isChargeFull() {
			return false; // TODO: mock this
		}

		static bool isCharging() {
			return false; // TODO: mock this
		}

		static double getBatteryLevel() {
			return 0.95; // TODO: mock this
		}

		static double getBatVoltage() {
			return 4.0; // TODO: mock this
		}

		virtual ~Power() = default;
};
