#include "ButtonsWidget.h"

#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

CSingle_Button_Widget::CSingle_Button_Widget(CM5Buttons::Button btn,
                                             QWidget *parent)
    : QWidget(parent), mButton(btn) {
  // guessed button width/height
  setFixedWidth(100);
  setFixedHeight(32);
}

void CSingle_Button_Widget::mousePressEvent(QMouseEvent *evt) {
  // pressed - signalize the device
  mPressed = true;
  CM5Stack_VM::Instance()->Get_Buttons()->press(mButton);

  emit repaint();
}

void CSingle_Button_Widget::mouseReleaseEvent(QMouseEvent *evt) {
  // released - signalize the device
  mPressed = false;
  CM5Stack_VM::Instance()->Get_Buttons()->release(mButton);

  emit repaint();
}

void CSingle_Button_Widget::paintEvent(QPaintEvent *event) {
  QPainter painter;
  painter.begin(this);

  const QRect r(0, 0, width(), height());
  painter.fillRect(r, QColor::fromRgb(0x22, 0x22, 0x22));

  setAttribute(Qt::WA_OpaquePaintEvent);
  painter.setRenderHint(QPainter::Antialiasing, true);

  painter.setPen(QPen(Qt::darkRed, 3));
  painter.setBrush(QColor::fromRgb(0x22, 0x22, 0x22));
  if (mPressed) {
    painter.setBrush(Qt::darkRed);
  }
  painter.drawEllipse(QPoint(50, 16), 14, 14);

  QWidget::paintEvent(event);
  painter.end();
}

CButtons_Widget::CButtons_Widget(QWidget *parent) : QWidget(parent) {
  setFixedWidth(320);

  Setup_GUI();
}

void CButtons_Widget::Setup_GUI() {
  QHBoxLayout *lay = new QHBoxLayout();

  lay->addWidget(new CSingle_Button_Widget(CM5Buttons::Button::A, this));
  lay->addWidget(new CSingle_Button_Widget(CM5Buttons::Button::B, this));
  lay->addWidget(new CSingle_Button_Widget(CM5Buttons::Button::C, this));

  setLayout(lay);
}
