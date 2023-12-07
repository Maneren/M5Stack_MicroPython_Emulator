#include "M5Stack_Drawables.h"
#include "BoostPythonDefs.h"
#include "WidgetEventProxy.h"

CDrawable_Text::CDrawable_Text(const std::string &text, int x, int y, int color)
    : IDrawable(x, y), mText(text), mColor(color) {
  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Text::Set_Text(const std::string &text) {
  mText = text;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Text::Draw(QPainter *painter) {
  painter->setPen(Qt::green);

  // TODO: get real font
  QFont font = painter->font();
  font.setFamily("Courier New");
  font.setPixelSize(14);
  painter->setFont(font);

  auto txt = QString::fromStdString(mText);

  QFontMetrics fm(font);
  int h = fm.height();

  painter->drawText(QPoint{mPosX, mPosY + h}, txt);
}

CDrawable_Line::CDrawable_Line(int x, int y, int x2, int y2, int color)
    : IDrawable(x, y), mPosX2(x2), mPosY2(y2), mColor(color) {
  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Line::Draw(QPainter *painter) {
  painter->setPen(QColor::fromRgb((mColor >> 16) & 0xFF, (mColor >> 8) & 0xFF,
                                  (mColor) & 0xFF));

  painter->drawLine(QPoint(mPosX, mPosY), QPoint(mPosX2, mPosY2));
}

void CDrawable_Line::Set_Position(int x, int y, int x2, int y2) {
  mPosX = x;
  mPosY = y;
  mPosX2 = x2;
  mPosY2 = y2;

  WidgetEventProxy::Instance()->Emit();
}

CDrawable_Circle::CDrawable_Circle(int x, int y, int radius, int bgColor,
                                   int borderColor)
    : IDrawable(x, y), mRadius(radius), mBorder_Color(borderColor),
      mBrush_Color(bgColor) {
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

void CDrawable_Circle::Draw(QPainter *painter) {
  painter->setPen(QColor::fromRgb((mBorder_Color >> 16) & 0xFF,
                                  (mBorder_Color >> 8) & 0xFF,
                                  (mBorder_Color) & 0xFF));

  if (mBrush_Color != 0xFFFFFFFF) {
    painter->setBrush(QColor::fromRgb((mBrush_Color >> 16) & 0xFF,
                                      (mBrush_Color >> 8) & 0xFF,
                                      (mBrush_Color) & 0xFF));
  } else {
    painter->setBrush(Qt::transparent);
  }

  painter->drawEllipse(QPoint(mPosX, mPosY), mRadius, mRadius);
}

CDrawable_Button::CDrawable_Button(const std::string &text, int x, int y,
                                   int width, int height, int textColor,
                                   int brushColor)
    : IDrawable(x, y), mWidth(width), mHeight(height), mText_Color(textColor),
      mBrush_Color(brushColor), mText(text) {

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Button::Set_Position(int x, int y) {
  mPosX = x;
  mPosY = y;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Button::Set_Size(int w, int h) {
  mWidth = w;
  mHeight = h;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Button::Set_Text(const std::string &text) {
  mText = text;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Button::Register_Pressed_Callback(PyObject *cb) {
  mPressed_Callback.push_back(cb);
}

void CDrawable_Button::Register_Released_Callback(PyObject *cb) {
  mReleased_Callback.push_back(cb);
}

void CDrawable_Button::Draw(QPainter *painter) {
  painter->setPen(QColor::fromRgb((mText_Color >> 16) & 0xFF,
                                  (mText_Color >> 8) & 0xFF,
                                  (mText_Color) & 0xFF));

  if (mBrush_Color != 0xFFFFFFFF) {
    painter->setBrush(QColor::fromRgb((mBrush_Color >> 16) & 0xFF,
                                      (mBrush_Color >> 8) & 0xFF,
                                      (mBrush_Color) & 0xFF));
  } else {
    painter->setBrush(Qt::transparent);
  }

  // TODO: get real font
  QFont font = painter->font();
  font.setFamily("Courier New");
  font.setPixelSize(14);
  painter->setFont(font);

  auto txt = QString::fromStdString(mText);

  QFontMetrics fm(font);
  int h = fm.height();
  int w = fm.horizontalAdvance(txt);

  painter->drawRect(mPosX, mPosY, mWidth, mHeight);
  painter->drawText(
      QPoint(mPosX + mWidth / 2 - w / 2, mPosY + 2 * h / 7 + mHeight / 2), txt);
}

bool CDrawable_Button::Touched(int x, int y, bool touch) {
  if (x >= mPosX && x < mPosX + mWidth && y >= mPosY && y <= mPosY + mHeight) {
    if (touch) {
      for (auto cb : mPressed_Callback)
        py::call<void>(cb);
    } else {
      for (auto cb : mReleased_Callback)
        py::call<void>(cb);
    }

    return true;
  }

  return false;
}

CDrawable_Checkbox::CDrawable_Checkbox(const std::string &text, int x, int y,
                                       int width, int height, int textColor,
                                       int checkColor)
    : IDrawable(x, y), mWidth(width), mHeight(height), mText_Color(textColor),
      mCheck_Color(checkColor), mText(text) {

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Checkbox::Set_Position(int x, int y) {
  mPosX = x;
  mPosY = y;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Checkbox::Set_Size(int w, int h) {
  mWidth = w;
  mHeight = h;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Checkbox::Set_Text(const std::string &text) {
  mText = text;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Checkbox::Register_Checked_Callback(PyObject *cb) {
  mChecked_Callback.push_back(cb);
}

void CDrawable_Checkbox::Register_Unchecked_Callback(PyObject *cb) {
  mUnchecked_Callback.push_back(cb);
}

void CDrawable_Checkbox::Set_Checked(bool state) {
  mIs_Checked = state;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Checkbox::Draw(QPainter *painter) {
  painter->setPen(QColor::fromRgb((mText_Color >> 16) & 0xFF,
                                  (mText_Color >> 8) & 0xFF,
                                  (mText_Color) & 0xFF));

  painter->setBrush(Qt::white);

  // TODO: get real font
  QFont font = painter->font();
  font.setFamily("Courier New");
  font.setPixelSize(14);
  painter->setFont(font);

  auto txt = QString::fromStdString(mText);

  QFontMetrics fm(font);
  int h = fm.height();
  int w = fm.horizontalAdvance(txt);

  painter->drawRect(mPosX, mPosY, 16, 16);
  if (mIs_Checked) {
    painter->setBrush(QColor::fromRgb((mCheck_Color >> 16) & 0xFF,
                                      (mCheck_Color >> 8) & 0xFF,
                                      (mCheck_Color) & 0xFF));

    painter->drawRect(mPosX + 2, mPosY + 2, 16 - 4, 16 - 4);
  }

  painter->drawText(QPoint(mPosX + 16 + 4, mPosY + 2 * h / 7 + 16 / 2), txt);
}

bool CDrawable_Checkbox::Touched(int x, int y, bool touch) {
  if (x >= mPosX && x < mPosX + (mWidth > 0 ? mWidth : 16) && y >= mPosY &&
      y <= mPosY + (mHeight > 0 ? mHeight : 16)) {
    if (!touch) {
      mIs_Checked = !mIs_Checked;
    }

    if (mIs_Checked) {
      for (auto cb : mChecked_Callback)
        py::call<void>(cb);
    } else {
      for (auto cb : mUnchecked_Callback)
        py::call<void>(cb);
    }

    WidgetEventProxy::Instance()->Emit();

    return true;
  }

  return false;
}

CDrawable_Switch::CDrawable_Switch(int x, int y, int width, int height,
                                   int bgColor, int switchColor)
    : IDrawable(x, y), mWidth(width), mHeight(height), mBg_Color(bgColor),
      mColor(switchColor) {

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Switch::Set_Position(int x, int y) {
  mPosX = x;
  mPosY = y;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Switch::Set_Size(int w, int h) {
  mWidth = w;
  mHeight = h;

  WidgetEventProxy::Instance()->Emit();
}

void CDrawable_Switch::Register_On_Callback(PyObject *cb) {
  mOn_Callback.push_back(cb);
}

void CDrawable_Switch::Register_Off_Callback(PyObject *cb) {
  mOff_Callback.push_back(cb);
}

void CDrawable_Switch::Set_State(bool state) {
  mIs_Checked = state;

  WidgetEventProxy::Instance()->Emit();
}

bool CDrawable_Switch::Get_State() const { return mIs_Checked; }

void CDrawable_Switch::Draw(QPainter *painter) {
  painter->setPen(Qt::white);

  painter->setBrush(QColor::fromRgb(
      (mBg_Color >> 16) & 0xFF, (mBg_Color >> 8) & 0xFF, (mBg_Color) & 0xFF));

  painter->drawRect(mPosX, mPosY, mWidth, mHeight);

  painter->setBrush(QColor::fromRgb((mColor >> 16) & 0xFF, (mColor >> 8) & 0xFF,
                                    (mColor) & 0xFF));

  painter->drawRect(mPosX + 2 + (mIs_Checked ? ((mWidth - 2) / 2) : 0),
                    mPosY + 2, (mWidth - 4) / 2, mHeight - 4);
}

bool CDrawable_Switch::Touched(int x, int y, bool touch) {
  if (x >= mPosX && x < mPosX + mWidth && y >= mPosY && y <= mPosY + mHeight) {
    if (touch) {
      mIs_Checked = !mIs_Checked;
    }

    if (mIs_Checked) {
      for (auto cb : mOn_Callback)
        py::call<void>(cb);
    } else {
      for (auto cb : mOff_Callback)
        py::call<void>(cb);
    }

    WidgetEventProxy::Instance()->Emit();

    return true;
  }

  return false;
}
