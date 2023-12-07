#include "MainWindow.h"

#include "Widgets/AdvancedIOWidget.h"
#include "Widgets/ButtonsWidget.h"
#include "Widgets/DisplayWidget.h"
#include "Widgets/GPIOWidget.h"
#include "Widgets/UARTWidget.h"

#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

CMain_Window::CMain_Window(const std::filesystem::path &pyFile)
    : QMainWindow(nullptr), mPy_File_Path(pyFile) {
  //
}

void CMain_Window::Setup_GUI() {
  // move the widget proxy signaller to this thread, so the signalling works
  WidgetEventProxy::Instance()->moveToThread(
      QApplication::instance()->thread());

  setWindowTitle("M5Stack emulator");

  // main layout
  QWidget *central = new QWidget(this);
  QGridLayout *centralLayout = new QGridLayout();
  {
    central->setLayout(centralLayout);

    CAIO_Widget *aio = new CAIO_Widget(this);
    centralLayout->addWidget(aio, 0, 1, 1, 1);

    // central layout
    QWidget *mainPanel = new QWidget(central);
    QVBoxLayout *mainPanelLayout = new QVBoxLayout();
    {
      mainPanel->setLayout(mainPanelLayout);

      // device screen and buttons
      QWidget *deviceWidget = new QWidget(mainPanel);
      QVBoxLayout *devLayout = new QVBoxLayout();
      {
        deviceWidget->setLayout(devLayout);
        deviceWidget->setStyleSheet("background-color: #222222;");

        CDisplay_Widget *dw = new CDisplay_Widget(this);
        devLayout->addWidget(dw);

        CButtons_Widget *bw = new CButtons_Widget(this);
        devLayout->addWidget(bw);
      }

      mainPanelLayout->addWidget(deviceWidget);

      // GPIOs
      CGPIO_Widget *gp = new CGPIO_Widget(this);
      mainPanelLayout->addWidget(gp);

      // UART (channel 1)
      CUART_Widget *ua = new CUART_Widget(this);
      mainPanelLayout->addWidget(ua);

      mainPanelLayout->addStretch(1);
    }

    centralLayout->addWidget(mainPanel, 0, 0, 2, 1);
  }

  setCentralWidget(central);

  // loads the python file and run it
  CM5Stack_VM::Instance()->Load_File(mPy_File_Path.string());
  CM5Stack_VM::Instance()->Run();
}
