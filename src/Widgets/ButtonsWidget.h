#pragma once

#include "../M5Stack_MicroPython.h"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

/*
 * Widget of a single UI button - this is a hardware button (one of three below
 * the display)
 */
class CSingle_Button_Widget : public QWidget {
  Q_OBJECT

private:
  // button index
  CM5Buttons::Button mButton;

  // is the button pressed?
  bool mPressed = false;

public:
  CSingle_Button_Widget(CM5Buttons::Button btn, QWidget *parent);

  void mousePressEvent(QMouseEvent *evt) override;
  void mouseReleaseEvent(QMouseEvent *evt) override;
  void paintEvent(QPaintEvent *event) override;
};

/*
 * Widget containing 3 of hardware buttons below display
 */
class CButtons_Widget : public QWidget {
  Q_OBJECT

public:
  explicit CButtons_Widget(QWidget *parent = nullptr);
  void Setup_GUI();
};
