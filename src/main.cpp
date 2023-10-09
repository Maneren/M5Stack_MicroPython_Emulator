#include "MainWindow.h"

#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char **argv) {

  if (argc != 2) {
    std::cerr << "Invalid parameter count. Usage: " << argv[0]
              << " <MicroPython file>" << std::endl;
    return 1;
  }

  QApplication app(argc, argv);

  // create main window and show it
  CMain_Window mw(std::string{argv[1]});
  mw.Setup_GUI();
  mw.show();

  return app.exec();
}
