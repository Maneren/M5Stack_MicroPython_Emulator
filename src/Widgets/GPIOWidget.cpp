#include "GPIOWidget.h"

#include <QtWidgets/QGridLayout>

CGPIO_Pin_Button_Widget::CGPIO_Pin_Button_Widget(uint32_t pinNo, CGPIO_Widget* parent) : QWidget(parent), mPin_No(pinNo), mParent(parent) {
	//
}

void CGPIO_Pin_Button_Widget::Setup_GUI() {
	setFixedWidth(20);
	setFixedHeight(20);
}

void CGPIO_Pin_Button_Widget::Set_State(int mode, int level) {
	mPin_Mode = mode;
	mPin_State = level;
}

void CGPIO_Pin_Button_Widget::paintEvent(QPaintEvent* event) {

	QPainter painter;
	painter.begin(this);

	const QRect r(0, 0, width(), height());
	painter.fillRect(r, Qt::white);

	setAttribute(Qt::WA_OpaquePaintEvent);
	QPen linepen;
	linepen.setWidth(2);
	painter.setRenderHint(QPainter::Antialiasing, true);

	// depending on pin mode, draw the circle accordingly
	switch (mPin_Mode) {
		// input - outline
		case Pin::_IN:
			linepen.setColor(mPin_State ? Qt::green : Qt::red);
			painter.setPen(linepen);
			painter.drawEllipse(QPoint(width() / 2, height() / 2), (width() / 2) - 1, (height() / 2) - 1);
			break;
		// output - filled circle
		case Pin::_OUT:
			linepen.setColor(mPin_State ? Qt::green : Qt::red);
			painter.setPen(linepen);
			painter.setBrush(QBrush(mPin_State ? Qt::green : Qt::red, Qt::SolidPattern));
			painter.drawEllipse(QPoint(width() / 2, height() / 2), (width() / 2) - 1, (height() / 2) - 1);
			break;
		// alt pins - we are not interested in alternate pin function states
		default:
			linepen.setColor(Qt::blue);
			painter.setPen(linepen);
			painter.drawEllipse(QPoint(width() / 2, height() / 2), (width() / 2) - 1, (height() / 2) - 1);
			break;
	}

	auto str = QString::number(mPin_No);

	// text - pin number
	QFont fnt(painter.font().family(), 7, 99, false);
	painter.setFont(fnt);
	linepen.setColor(Qt::black);
	painter.setPen(linepen);

	QFontMetrics fm(painter.font());
	const auto tw = fm.horizontalAdvance(str);

	painter.drawText((width() / 2) - (tw / 2), (height() / 2) + 4, str);

	QWidget::paintEvent(event);
	painter.end();
}

void CGPIO_Pin_Button_Widget::mouseReleaseEvent(QMouseEvent* event) {
	// user clicked with left button - toggle in if it is in input mode
	if (mPin_Mode == Pin::_IN && event->button() == Qt::LeftButton) {
		if (mParent) {
			mPin_State = mPin_State > 0 ? 0 : 1;
			mParent->Set_Pin_Output(mPin_No, mPin_State);
		}
	}
}

void CGPIO_Pin_Button_Widget::Trigger_Repaint() {
	emit repaint();
}

void CGPIO_Widget::Setup_GUI() {

	const auto cnt = CM5GPIO::GPIO_Count;

	auto ctl = CM5Stack_VM::Instance()->Get_GPIO();

	QGridLayout* lay = new QGridLayout(this);
	setLayout(lay);

	// add pin widgets
	for (uint32_t i = 0; i < cnt; i++) {

		CGPIO_Pin_Button_Widget* btn = new CGPIO_Pin_Button_Widget(i, this);
		btn->Setup_GUI();

		btn->Set_State(ctl->Get_Pin_Mode(i), ctl->Get_Pin_State(i));

		mGPIO_Btns.push_back(btn);

		lay->addWidget(btn, i / 10, i % 10);
	}

	Trigger_Repaint(true);
}

void CGPIO_Widget::Trigger_Repaint(bool force) {

	// refresh state

	const auto cnt = CM5GPIO::GPIO_Count;

	auto ctl = CM5Stack_VM::Instance()->Get_GPIO();

	if (!ctl->Is_Changed() && !force) {
		return;
	}

	ctl->Clear_Changed_Flag();

	for (uint32_t i = 0; i < cnt; i++) {
		if (mGPIO_Btns[i])
			mGPIO_Btns[i]->Set_State(ctl->Get_Pin_Mode(i), ctl->Get_Pin_State(i));
	}

	// repaing widgets
	for (auto btn : mGPIO_Btns) {
		if (btn) {
			btn->Trigger_Repaint();
		}
	}
}

void CGPIO_Widget::Set_Pin_Output(int pinNo, int state) {

	// set pin output in controller
	auto ctl = CM5Stack_VM::Instance()->Get_GPIO();

	ctl->Set_Pin_State(pinNo, state);

	// refresh and redraw widget
	if (mGPIO_Btns[pinNo]) {
		mGPIO_Btns[pinNo]->Set_State(ctl->Get_Pin_Mode(pinNo), ctl->Get_Pin_State(pinNo));
		mGPIO_Btns[pinNo]->Trigger_Repaint();
	}

}
