#pragma once

#include "../BoostPythonDefs.h"
#include "ADC.h"
#include "DAC.h"
#include "PWM.h"
#include "Pin.h"
#include "UART.h"

BOOST_PYTHON_MODULE(machine) {
  Define_Class<Pin>();
  Define_Class<PWM>();
  Define_Class<ADC>();
  Define_Class<DAC>();
  Define_Class<UART>();
}
