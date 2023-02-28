#include "M5Stack_Drawables.h"
#include "WidgetEventProxy.h"

CDrawable_Text::CDrawable_Text(const std::string& text, int x, int y, int color) : IDrawable(x, y), mText(text), mColor(color) {
	WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Text::Set_Text(const std::string& text) {
	mText = text;

	WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Text::Draw(QPainter& painter) {

	painter.setPen(Qt::green);

	// TODO: get real font
	QFont font = painter.font();
	font.setFamily("Courier New");
	font.setPixelSize(14);
	painter.setFont(font);

	auto txt = QString::fromStdString(mText);

	QFontMetrics fm(font);
	int h = fm.height();

	painter.drawText(QPoint{ mPosX, mPosY + h }, txt);
}

CDrawable_Line::CDrawable_Line(int x, int y, int x2, int y2, int color) : IDrawable(x, y), mPosX2(x2), mPosY2(y2), mColor(color) {
	WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Line::Draw(QPainter& painter) {

	painter.setPen(QColor::fromRgb(
		(mColor >> 16) & 0xFF,
		(mColor >> 8) & 0xFF,
		(mColor) & 0xFF
	));

	painter.drawLine(QPoint(mPosX, mPosY), QPoint(mPosX2, mPosY2));
}

void CDrawable_Line::Set_Position(int x, int y, int x2, int y2) {
	mPosX = x;
	mPosY = y;
	mPosX2 = x2;
	mPosY2 = y2;

	WidgetEventProxy::Instance()->Emit();
}

CDrawable_Circle::CDrawable_Circle(int x, int y, int radius, int bgColor, int borderColor) : IDrawable(x, y), mRadius(radius), mBorder_Color(borderColor), mBrush_Color(bgColor) {
	WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Circle::Set_Position(int x, int y) {
	mPosX = x;
	mPosY = y;

	WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Circle::Set_Radius(int radius) {
	mRadius = radius;

	WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Circle::Draw(QPainter& painter) {

	painter.setPen(QColor::fromRgb(
		(mBorder_Color >> 16) & 0xFF,
		(mBorder_Color >> 8) & 0xFF,
		(mBorder_Color) & 0xFF
	));

	if (mBrush_Color != 0xFFFFFFFF) {
		painter.setBrush(QColor::fromRgb(
			(mBrush_Color >> 16) & 0xFF,
			(mBrush_Color >> 8) & 0xFF,
			(mBrush_Color) & 0xFF
		));
	}
	else {
		painter.setBrush(Qt::transparent);
	}

	painter.drawEllipse(QPoint(mPosX, mPosY), mRadius, mRadius);

}
