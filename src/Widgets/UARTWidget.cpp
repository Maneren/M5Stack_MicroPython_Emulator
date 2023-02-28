#include "UARTWidget.h"

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>

void CUART_Widget::Setup_GUI() {

	QVBoxLayout* lay = new QVBoxLayout(this);
	setLayout(lay);

	// console output
	mConsole = new QTextEdit(this);
	mConsole->setFixedHeight(128);
	mConsole->setReadOnly(true);
	lay->addWidget(mConsole);

	// input from user
	mInput = new QLineEdit(this);
	lay->addWidget(mInput);

	// send button
	QPushButton* send = new QPushButton("Send", this);
	lay->addWidget(send);

	connect(this, SIGNAL(Request_Console_Refresh()), this, SLOT(On_Console_Refresh()));
	connect(send, SIGNAL(clicked()), this, SLOT(On_Send_Button_Clicked()));
}

void CUART_Widget::Update_Console() {

	// try to obtain a string from UART, if there is any
	if (auto ctl = CM5Stack_VM::Instance()->Get_UART()) {

		while (!ctl->Empty(CM5UART::Channel::Channel_1, false)) {
			auto s = ctl->Read(CM5UART::Channel::Channel_1, false);

			mConsole_Text += s;
		}

		emit Request_Console_Refresh();
	}
}

void CUART_Widget::On_Console_Refresh() {
	mConsole->setText(QString::fromStdString(mConsole_Text));

	mConsole->verticalScrollBar()->setValue(mConsole->verticalScrollBar()->maximum());
}

void CUART_Widget::On_Send_Button_Clicked() {

	// extract the string, empty the input
	const std::string text = mInput->text().toStdString();
	mInput->setText("");

	if (auto ctl = CM5Stack_VM::Instance()->Get_UART()) {
		ctl->Write(CM5UART::Channel::Channel_1, false, text);
	}
}
