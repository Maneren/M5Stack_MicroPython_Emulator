#pragma once

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <string>

/*
 * Generic drawable element
 */
class IDrawable {
	protected:
		// X coordinate
		int mPosX = 0;
		// Y coordinate
		int mPosY = 0;

	public:
		IDrawable(int x = 0, int y = 0) : mPosX(x), mPosY(y) { }
		virtual ~IDrawable() = default;

		// draw the drawable onto the canvas
		virtual void Draw(QPainter& painter) = 0;
};

/*
 * Drawable text/label (M5Label or lcd.print(...)-produced)
 */
class CDrawable_Text : public IDrawable {
	private:
		// text to be drawn
		std::string mText = "";
		// color of the text
		int mColor = 0;

	public:
		CDrawable_Text(const std::string& text = "", int x = 0, int y = 0, int color = 0xFFFFFFFF);

		// sets a new text to the element
		void Set_Text(const std::string& text);

		virtual void Draw(QPainter& painter) override;
};

/*
 * Drawable line (M5Line)
 */
class CDrawable_Line : public IDrawable {
	private:
		// second X coordinate
		int mPosX2 = 0;
		// second Y coordinate
		int mPosY2 = 0;

		// line color
		int mColor = 0xFFFFFF;

	public:
		CDrawable_Line(int x, int y, int x2, int y2, int color = 0xFFFFFF);

		// sets the line position
		void Set_Position(int x, int y, int x2, int y2);

		virtual void Draw(QPainter& painter) override;
};

/*
 * Drawable circle (M5Circle)
 */
class CDrawable_Circle : public IDrawable {
	private:
		// circle radius
		int mRadius = 0;

		// border color
		int mBorder_Color = 0xFFFFFF;
		// fill color
		int mBrush_Color = 0xFFFFFFFF;

	public:
		CDrawable_Circle(int x, int y, int radius, int bgColor = 0xFFFFFFFF, int borderColor = 0xFFFFFF);

		// sets the center position
		void Set_Position(int x, int y);
		// sets the circle radius
		void Set_Radius(int radius);

		virtual void Draw(QPainter& painter) override;
};
