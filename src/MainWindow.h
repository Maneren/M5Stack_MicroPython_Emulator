#pragma once

#include <filesystem>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

/*
 * Main application window
 */
class CMain_Window : public QMainWindow {
  Q_OBJECT

private:
  const std::filesystem::path mPy_File_Path;

public:
  explicit CMain_Window(const std::filesystem::path &pyFile);
  void Setup_GUI();
};
