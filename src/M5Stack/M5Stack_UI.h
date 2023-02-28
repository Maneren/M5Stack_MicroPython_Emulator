#pragma once

#include "../BoostPythonDefs.h"
#include "M5Screen.h"

#include "M5Line.h"
#include "M5Circle.h"
#include "M5Label.h"

// sets the default screen color
void setScreenColor(int clr) {
    auto scrn = CM5Stack_VM::Instance()->Get_Screen();

    scrn->Set_Background_Color(clr);
}

BOOST_PYTHON_MODULE(m5stack_ui) {
    Define_Class<M5Label>();
    Define_Class<M5Line>();
    Define_Class<M5Circle>();

    // stand-alone functions
    py::def("setScreenColor", &setScreenColor);

    // fonts; TODO: map all fonts to some enum
    py::scope().attr("FONT_MONT_14") = 0;
}
