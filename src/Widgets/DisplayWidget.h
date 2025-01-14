#pragma once

#include "../WidgetEventProxy.h"

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

/*
 * Display widget (320x240 "display" of the machine)
 */
class CDisplay_Widget : public ProxiedWidget {
public:
  explicit CDisplay_Widget(QWidget *parent = nullptr);

  void Invoke_Repaint() override { Trigger_Repaint(); }

  // triggers repainting
  void Trigger_Repaint();

  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *evt) override;
  void mouseReleaseEvent(QMouseEvent *evt) override;
  void mouseMoveEvent(QMouseEvent *evt) override;
};
