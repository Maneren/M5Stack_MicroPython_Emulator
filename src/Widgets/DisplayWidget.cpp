#include "DisplayWidget.h"

#include <QtGui/QMouseEvent>

CDisplay_Widget::CDisplay_Widget(QWidget* parent) : ProxiedWidget(parent) {
	WidgetEventProxy::Instance()->Register_Listener(this);

	// the dimensions are fixed as the display is built-in to the device
	setFixedWidth(320);
	setFixedHeight(240);
}

void CDisplay_Widget::paintEvent(QPaintEvent* event) {

	QPainter painter;
	painter.begin(this);

	const QRect r(0, 0, width(), height());
	painter.fillRect(r, Qt::black);

	setAttribute(Qt::WA_OpaquePaintEvent);
	painter.setRenderHint(QPainter::Antialiasing, false);

	auto display = CM5Stack_VM::Instance()->Get_Screen();
	display->Render_To(painter);

	QWidget::paintEvent(event);
	painter.end();
}

void CDisplay_Widget::Trigger_Repaint() {
	emit repaint();
}

void CDisplay_Widget::mousePressEvent(QMouseEvent* evt) {
	auto display = CM5Stack_VM::Instance()->Get_Screen();

	display->Set_Touch_State(true, evt->pos().x(), evt->pos().y());
}

void CDisplay_Widget::mouseReleaseEvent(QMouseEvent* evt) {
	auto display = CM5Stack_VM::Instance()->Get_Screen();

	display->Set_Touch_State(false, evt->pos().x(), evt->pos().y());
}

void CDisplay_Widget::mouseMoveEvent(QMouseEvent* evt) {
	auto display = CM5Stack_VM::Instance()->Get_Screen();

	display->Set_Touch_State(true, evt->pos().x(), evt->pos().y());
}
