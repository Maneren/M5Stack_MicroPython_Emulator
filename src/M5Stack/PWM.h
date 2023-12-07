#pragma once

/*
 * PWM class wrapper
 */
class PWM {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "PWM"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) { return obj; }

public:
  PWM() {
    //
  }

  virtual ~PWM() = default;

  // TODO
};
