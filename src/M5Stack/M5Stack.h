#pragma once

#include "../BoostPythonDefs.h"
#include "M5Screen.h"
#include "Buttons.h"
#include "LCD.h"
#include "RTC.h"
#include "Power.h"
#include "Touch.h"

#include <chrono>
#include <thread>

// wait module function - wait for given amount of seconds
void wait(double duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(duration * 1000)));
}

// wait_ms module function - wait for given amount of milliseconds
void wait_ms(int duration) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long>(duration)));
}

BOOST_PYTHON_MODULE(m5stack) {
    Define_Class<M5Screen>();

    // buttons are sometimes imported as both "buttonX" and "btnX"
    Define_Class<ButtonA>();
    Define_Class<ButtonA>("btnA");
    Define_Class<ButtonB>();
    Define_Class<ButtonB>("btnB");
    Define_Class<ButtonC>();
    Define_Class<ButtonC>("btnC");

    Define_Class<LCD>();
    Define_Class<RTC>();
    Define_Class<Power>();
    Define_Class<Touch>();

    // stand-alone module funcions
    py::def("wait", &wait);
    py::def("wait_ms", &wait_ms);
}
