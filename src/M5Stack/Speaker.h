#pragma once

#include "../BoostPythonDefs.h"
#include "../M5Stack_MicroPython.h"

#include <iostream>

/*
 * Speaker class wrapper for "speaker" submodule
 */
class Speaker {
public:
  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "speaker"; }

  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) {

    void (*volSet)(int) = &Speaker::volume;
    int (*volGet)() = &Speaker::volume;

    return obj.def("volume", volSet)
        .def("volume", volGet)
        .def("playTone", &Speaker::playTone)
        .def("tone", &Speaker::playTone); // redefinition for different dialects
                                          // of MicroPython
  }

public:
  Speaker() {
    //
  }

  static void volume(int level) {
    CM5Stack_VM::Instance()->Get_Misc()->Set_Volume(level);
  }

  static int volume() {
    return CM5Stack_VM::Instance()->Get_Misc()->Get_Volume();
  }

  static void playTone(int tone, int beat_duration) {
    CM5Stack_VM::Instance()->Get_Misc()->Play_Tone(tone, beat_duration);
  }

  virtual ~Speaker() = default;
};
