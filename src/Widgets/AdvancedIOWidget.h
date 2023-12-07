#pragma once

#include <cstdint>
#include <vector>

#include "../M5Stack/Pin.h"
#include "../WidgetEventProxy.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>

class CAIO_Widget;

const int CAIO_INPUT_SLIDER = 0;
const int CAIO_INPUT_NUMBER = 1;
const int CAIO_INPUT_FUNCTION = 2;

class CAIO_Pin_Widget : public QWidget {
private:
  // pin number
  uint32_t mPin_No;
  // pin mode
  int mPin_Mode = Pin::_IN;
  // current pin state
  int mPin_State = 0;

  // input style (0 = slider, 1 = number, 2 = function)
  int input_Style = CAIO_INPUT_SLIDER;

  // parent widget for controlling
  CAIO_Widget *mParent;

  QGridLayout *layout;

  // inputs
  QSlider *slider_input;
  QLineEdit *number_input;
  QComboBox *function_input;

public:
  explicit CAIO_Pin_Widget(uint32_t pinNo, CAIO_Widget *parent = nullptr);

  // sets up the GUI
  void Setup_GUI();
  // sets the internal cached pin state
  void Set_State(int mode, int state);
  // triggers repainting
  void Trigger_Repaint();

  // void paintEvent(QPaintEvent *event) override;

  uint32_t Get_Pin_No() { return mPin_No; }
};

class CAIO_Widget : public ProxiedWidget {
private:
  // vector of GPIO pin widgets
  std::vector<uint32_t> selected_pins;

  QVBoxLayout *layout;
  std::vector<CAIO_Pin_Widget *> pin_widgets;

  bool is_changed;

public:
  void Invoke_Repaint() override { Trigger_Repaint(); }

public:
  explicit CAIO_Widget(QWidget *parent = nullptr) : ProxiedWidget(parent) {
    WidgetEventProxy::Instance()->Register_Listener(this);
    Setup_GUI();
  }

  // sets up the GUI
  void Setup_GUI();
  // triggers repainting of all child widgets
  void Trigger_Repaint(bool force = false);
  // sets the state for the selected pin
  void Set_Pin_Output(int pinNo, int state);

  void Add_Pin_Widget(uint32_t pinNo);
  void Remove_Pin_Widget(uint32_t pinNo);
};
