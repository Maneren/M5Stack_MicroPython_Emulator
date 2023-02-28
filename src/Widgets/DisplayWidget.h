#pragma once

#include <vector>
#include <memory>

#include "../M5Stack_MicroPython.h"
#include "../WidgetEventProxy.h"

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

/*
 * Display widget (320x240 "display" of the machine)
 */
class CDisplay_Widget : public ProxiedWidget
{
	public:
		explicit CDisplay_Widget(QWidget* parent = nullptr);

		void Invoke_Repaint() override {
			Trigger_Repaint();
		}

		// triggers repainting
		void Trigger_Repaint();

		void paintEvent(QPaintEvent* event) override;
		void mousePressEvent(QMouseEvent* evt) override;
		void mouseReleaseEvent(QMouseEvent* evt) override;
		void mouseMoveEvent(QMouseEvent* evt) override;
};
