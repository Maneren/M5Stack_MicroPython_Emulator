#pragma once

#include "../WidgetEventProxy.h"

#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

/*
 * User UART widget
 */
class CUART_Widget : public ProxiedWidget {
  Q_OBJECT

private:
  // console output from UART
  QTextEdit *mConsole = nullptr;
  // line input for UART
  QLineEdit *mInput = nullptr;

  // cached console text
  std::string mConsole_Text{};

signals:
  void Request_Console_Refresh();

protected slots:
  void On_Console_Refresh();
  void On_Send_Button_Clicked();

public:
  explicit CUART_Widget(QWidget *parent = nullptr) : ProxiedWidget(parent) {
    WidgetEventProxy::Instance()->Register_Listener(this);

    Setup_GUI();
  }

  // sets up the UART console GUI
  void Setup_GUI();
  // updates the console with data from UART
  void Update_Console();

  void Invoke_Repaint() override { Update_Console(); }
};
