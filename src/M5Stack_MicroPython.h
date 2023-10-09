#pragma once

#include <array>
#include <chrono>
#include <filesystem>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "BoostPythonDefs.h"
#include "SelfInitSingleton.h"
#include "WidgetEventProxy.h"

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>

#include "M5Stack_Drawables.h"
#include "M5Stack_Peripherals.h"

/*
 * M5Stack MicroPython virtual machine
 */
class CM5Stack_VM : public Self_Init_Singleton<CM5Stack_VM, true> {

private:
  // main Python module
  py::object mMain_Module;
  // main Python namespace
  py::object mMain_Namespace;

  // loaded Python file contents
  std::string mPy_File_Contents;

  // screen instance
  std::shared_ptr<CM5LCDScreen> mScreen;
  // GPIO instance
  std::shared_ptr<CM5GPIO> mGPIO;
  // buttons instance
  std::shared_ptr<CM5Buttons> mButtons;
  // UART (channel 1) instance
  std::shared_ptr<CM5UART> mUART;
  // miscellanous controller
  std::shared_ptr<CM5Misc> mMisc;

protected:
  // thread for Python interpreter
  std::unique_ptr<std::thread> mPy_Thread;
  // Python interpret thread method
  void Py_Thread_Fnc();

public:
  CM5Stack_VM();

  // Loads file to be interpreted
  bool Load_File(const std::filesystem::path &path);
  // retrieves file contents
  const std::string &Get_File_Contents() const;

  // run the loaded file
  void Run();

  // retrieve screen instance, create if not exists
  std::shared_ptr<CM5LCDScreen> &Get_Screen() {
    if (!mScreen)
      mScreen = std::make_shared<CM5LCDScreen>();

    return mScreen;
  }

  // retrieve GPIO instance, create if not exists
  std::shared_ptr<CM5GPIO> &Get_GPIO() {
    if (!mGPIO)
      mGPIO = std::make_shared<CM5GPIO>();

    return mGPIO;
  }

  // retrieve buttons instance, create if not exists
  std::shared_ptr<CM5Buttons> &Get_Buttons() {
    if (!mButtons)
      mButtons = std::make_shared<CM5Buttons>();

    return mButtons;
  }

  // retrieve UART instance, create if not exists
  std::shared_ptr<CM5UART> &Get_UART() {
    if (!mUART)
      mUART = std::make_shared<CM5UART>();

    return mUART;
  }

  // retrieve misc controller instance, create if not exists
  std::shared_ptr<CM5Misc> &Get_Misc() {
    if (!mMisc)
      mMisc = std::make_shared<CM5Misc>();

    return mMisc;
  }

  // Self_Init_Python_Object concept
  static constexpr const char *Get_Class_Name() { return "CM5Stack_VM"; }
  // Self_Init_Python_Object concept
  static auto &&Define_Class_Contents(auto &&obj) { return obj; }
};
