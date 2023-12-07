#pragma once

/*
 * DAC class encapsulating the Digital-To-Analog converter submodule
 */
class DAC {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "DAC"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) { return obj; }

public:
  DAC() {
    //
  }

  virtual ~DAC() = default;

  // TODO
};
