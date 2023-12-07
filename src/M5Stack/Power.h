#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"

/*
 * Power class wrapper for "power" submodule
 */
class Power {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "power"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {
    return obj.def("isChargeFull", &Power::isChargeFull)
        .def("isCharging", &Power::isCharging)
        .def("getBatteryLevel", &Power::getBatteryLevel)
        .def("getBatVoltage", &Power::getBatVoltage)
        .def("setVibrationEnable", &Power::setVibrationEnable);
  }

public:
  Power() {
    //
  }

  static bool isChargeFull() {
    return ((BATTERY_VOLTAGE_MAX -
             CM5Stack_VM::Instance()->Get_Misc()->Get_Battery_Voltage()) /
            (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN)) >
           0.98; // consider >98% battery charge as "full"
  }

  static bool isCharging() {
    return CM5Stack_VM::Instance()->Get_Misc()->Is_Battery_Charging();
  }

  static double getBatteryLevel() {
    return 100 * ((BATTERY_VOLTAGE_MAX -
                   CM5Stack_VM::Instance()->Get_Misc()->Get_Battery_Voltage()) /
                  (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN));
  }

  static double getBatVoltage() {
    return CM5Stack_VM::Instance()->Get_Misc()->Get_Battery_Voltage();
  }

  static void setVibrationEnable(bool state) {
    CM5Stack_VM::Instance()->Get_Misc()->Set_Vibration(state);
  }

  virtual ~Power() = default;

  static constexpr double BATTERY_VOLTAGE_MIN =
      3.7; // minimum battery voltage - this should be obtained through the
           // mocked interface later
  static constexpr double BATTERY_VOLTAGE_MAX =
      4.1; // maximum battery voltage - this should be obtained through the
           // mocked interface later
};
