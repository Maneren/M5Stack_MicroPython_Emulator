#include "MainWindow.h"

#include "Widgets/ButtonsWidget.h"
#include "Widgets/DisplayWidget.h"
#include "Widgets/GPIOWidget.h"
#include "Widgets/UARTWidget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>

CMain_Window::CMain_Window(const std::filesystem::path &pyFile)
    : QMainWindow(nullptr), mPy_File_Path(pyFile) {
  //
}

void CMain_Window::Setup_GUI() {

  // move the widget proxy signaller to this thread, so the signalling works
  WidgetEventProxy::Instance()->moveToThread(
      QApplication::instance()->thread());

  setWindowTitle("M5Stack emulator");

  // central layout
  QWidget *central = new QWidget(this);
  QVBoxLayout *centralLayout = new QVBoxLayout();
  {
    central->setLayout(centralLayout);

    // device screen and buttons
    QWidget *deviceWidget = new QWidget(central);
    QVBoxLayout *devLayout = new QVBoxLayout();
    {
      deviceWidget->setLayout(devLayout);
      deviceWidget->setStyleSheet("background-color: #222222;");

      CDisplay_Widget *dw = new CDisplay_Widget(this);
      devLayout->addWidget(dw);

      CButtons_Widget *bw = new CButtons_Widget(this);
      devLayout->addWidget(bw);
    }

    centralLayout->addWidget(deviceWidget);

    // GPIOs
    CGPIO_Widget *gp = new CGPIO_Widget(this);
    centralLayout->addWidget(gp);

    // UART (channel 1)
    CUART_Widget *ua = new CUART_Widget(this);
    centralLayout->addWidget(ua);

    centralLayout->addStretch(1);
  }
  setCentralWidget(central);

  // loads the python file and run it
  CM5Stack_VM::Instance()->Load_File(mPy_File_Path.string());
  CM5Stack_VM::Instance()->Run();
}
