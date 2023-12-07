#pragma once

#include <vector>

#include "../M5Stack/Pin.h"
#include "../WidgetEventProxy.h"

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

class CGPIO_Widget;

/*
 * GPIO pin widget, controllable
 */
class CGPIO_Pin_Button_Widget : public QWidget {
private:
  // pin number
  uint32_t mPin_No;
  // pin mode
  int mPin_Mode = Pin::_IN;
  // current pin state
  int mPin_State = 0;

  // parent widget for controlling
  CGPIO_Widget *mParent;

protected:
  void mouseReleaseEvent(QMouseEvent *event) override;

public:
  explicit CGPIO_Pin_Button_Widget(uint32_t pinNo,
                                   CGPIO_Widget *parent = nullptr);

  // sets up the GUI
  void Setup_GUI();
  // sets the internal cached pin state
  void Set_State(int mode, int state);
  // triggers repainting
  void Trigger_Repaint();

  void paintEvent(QPaintEvent *event) override;
};

/*
 * GPIO widget
 */
class CGPIO_Widget : public ProxiedWidget {
private:
  // vector of GPIO pin widgets
  std::vector<CGPIO_Pin_Button_Widget *> mGPIO_Btns;

public:
  void Invoke_Repaint() override { Trigger_Repaint(); }

public:
  explicit CGPIO_Widget(QWidget *parent = nullptr) : ProxiedWidget(parent) {
    WidgetEventProxy::Instance()->Register_Listener(this);
    Setup_GUI();
  }

  // updates pin state in controller and redraws the widget accordingly
  void Set_Pin_Output(int pinNo, int state);

  // sets up the GUI
  void Setup_GUI();
  // triggers repainting of all child widgets
  void Trigger_Repaint(bool force = false);
};
