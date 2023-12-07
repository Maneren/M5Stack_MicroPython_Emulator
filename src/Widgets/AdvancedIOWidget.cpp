#include "AdvancedIOWidget.h"

#include <QObject>
#include <QSlider>
#include <QtWidgets/QGridLayout>
#include <cstdint>
#include <cstdio>

CAIO_Pin_Widget::CAIO_Pin_Widget(uint32_t pinNo, CAIO_Widget *parent)
    : QWidget(parent), mParent(parent), mPin_No(pinNo) {
  //
}

void CAIO_Pin_Widget::Setup_GUI() {
  layout = new QGridLayout(this);

  slider_input = new QSlider(Qt::Horizontal, this);
  layout->addWidget(slider_input, 0, 0, 1, 2);

  number_input = new QLineEdit(this);
  layout->addWidget(number_input, 1, 0, 1, 1);

  function_input = new QComboBox(this);
  function_input->addItem("sinusoid");
  function_input->addItem("linear");
  function_input->addItem("ease");
  layout->addWidget(function_input, 1, 1, 1, 1);

  std::printf("Pin: %d\n", mPin_No);
}

void CAIO_Pin_Widget::Trigger_Repaint() { emit repaint(); }

void CAIO_Widget::Setup_GUI() {
  auto ctl = CM5Stack_VM::Instance()->Get_GPIO();

  layout = new QVBoxLayout(this);

  std::printf("Setting up GUI for advanced IO\n");

  Add_Pin_Widget(0);

  Trigger_Repaint();
}

void CAIO_Widget::Add_Pin_Widget(uint32_t pinNo) {
  pin_widgets.push_back(new CAIO_Pin_Widget(pinNo, this));

  pin_widgets.back()->Setup_GUI();

  layout->addWidget(pin_widgets.back());

  is_changed = true;

  Trigger_Repaint();
}

void CAIO_Widget::Remove_Pin_Widget(uint32_t pinNo) {
  int idx = 0;
  for (auto widget : pin_widgets) {
    if (widget->Get_Pin_No() == pinNo) {
      break;
    }
    idx++;
  }
  pin_widgets.erase(pin_widgets.begin() + idx);

  is_changed = true;

  Trigger_Repaint();
}

void CAIO_Widget::Trigger_Repaint(bool force) {
  // refresh state
  const auto cnt = CM5GPIO::GPIO_Count;

  auto ctl = CM5Stack_VM::Instance()->Get_GPIO();

  if (!this->is_changed && !force) {
    return;
  }

  // repaint all child widgets
  for (auto widget : pin_widgets) {
    widget->Trigger_Repaint();
  }

  this->is_changed = false;

  emit repaint();
}

void CAIO_Widget::Set_Pin_Output(int pinNo, int state) {
  // set pin output in controller
  auto ctl = CM5Stack_VM::Instance()->Get_GPIO();

  ctl->Set_Pin_State(pinNo, state);

  this->Trigger_Repaint();
}
