#pragma once

#include "../BoostPythonDefs.h"

// Arduino digitalRead function
int digitalRead(int pin) {
  // TODO
  return 0;
}

// Arduino analogRead function
int analogRead(int pin) {
  // TODO
  return 0;
}

// Arduino digitalWrite function
void digitalWrite(int pin, int level) {
  // TODO
}

// Arduino analogWrite function
void analogWrite(int pin, int level) {
  // TODO
}

// Arduino toggleIO function
void toggleIO(int pin) {
  // TODO
}

// map_value - remaps the input value to new boundaries
double map_value(double value, double from_low, double from_high, double to_low,
                 double to_high) {
  return to_low +
         ((value - from_low) / (from_high - from_low)) * (to_high - to_low);
}

BOOST_PYTHON_MODULE(easyIO) {
  // stand-alone functions
  py::def("digitalRead", &digitalRead);
  py::def("analogRead", &analogRead);
  py::def("digitalWrite", &digitalWrite);
  py::def("analogWrite", &analogWrite);
  py::def("toggleIO", &toggleIO);
  py::def("map_value", &map_value);
}
