#pragma once

#include <QtGui/QPaintEvent>
#include <QtGui/QPainter>
#include <string>

struct _object;
typedef _object PyObject;

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
  IDrawable(int x = 0, int y = 0) : mPosX(x), mPosY(y) {}
  virtual ~IDrawable() = default;

  // draw the drawable onto the canvas
  virtual void Draw(QPainter &painter) = 0;
  // process the touchscreen touch - not mandatory
  virtual bool Touched(int x, int y, bool touch = true) { return false; }
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
  CDrawable_Text(const std::string &text = "", int x = 0, int y = 0,
                 int color = 0xFFFFFFFF);

  // sets a new text to the element
  void Set_Text(const std::string &text);

  virtual void Draw(QPainter &painter) override;
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

  virtual void Draw(QPainter &painter) override;
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
  CDrawable_Circle(int x, int y, int radius, int bgColor = 0xFFFFFFFF,
                   int borderColor = 0xFFFFFF);

  // sets the center position
  void Set_Position(int x, int y);
  // sets the circle radius
  void Set_Radius(int radius);

  virtual void Draw(QPainter &painter) override;
};

/*
 * Drawable button (M5Btn)
 */
class CDrawable_Button : public IDrawable {
private:
  // button width
  int mWidth = 0;
  // button height
  int mHeight = 0;

  // text color
  int mText_Color = 0x2222EE;
  // fill color
  int mBrush_Color = 0xFAFAFA;

  // button text
  std::string mText;

  // pressed button callbacks
  std::vector<PyObject *> mPressed_Callback;
  // released button callbacks
  std::vector<PyObject *> mReleased_Callback;

public:
  CDrawable_Button(const std::string &text, int x, int y, int width, int height,
                   int textColor = 0x2222EE, int brushColor = 0xFAFAFA);

  // sets the button position
  void Set_Position(int x, int y);
  // sets the button size
  void Set_Size(int w, int h);
  // sets the button text
  void Set_Text(const std::string &text);
  // registers clicked callback
  void Register_Pressed_Callback(PyObject *cb);
  // registers released callback
  void Register_Released_Callback(PyObject *cb);

  virtual void Draw(QPainter &painter) override;
  virtual bool Touched(int x, int y, bool touch = true) override;
};

/*
 * Drawable checkbox (M5Checkbox)
 */
class CDrawable_Checkbox : public IDrawable {
private:
  // checkbox width
  int mWidth = 0;
  // checkbox height
  int mHeight = 0;

  // text color
  int mText_Color = 0x2222EE;
  // check color
  int mCheck_Color = 0xFAFAFA;

  // checkbox text
  std::string mText;

  // checked checkbox callbacks
  std::vector<PyObject *> mChecked_Callback;
  // unchecked checkbox callbacks
  std::vector<PyObject *> mUnchecked_Callback;

  // is checked?
  bool mIs_Checked = false;

public:
  CDrawable_Checkbox(const std::string &text, int x, int y, int width,
                     int height, int textColor = 0x2222EE,
                     int checkColor = 0xFAFAFA);

  // sets the checkbox position
  void Set_Position(int x, int y);
  // sets the checkbox size
  void Set_Size(int w, int h);
  // sets the checkbox text
  void Set_Text(const std::string &text);
  // registers checked checkbox callback
  void Register_Checked_Callback(PyObject *cb);
  // registers unchecked checkbox callback
  void Register_Unchecked_Callback(PyObject *cb);
  // set checked state
  void Set_Checked(bool state);

  virtual void Draw(QPainter &painter) override;
  virtual bool Touched(int x, int y, bool touch = true) override;
};

/*
 * Drawable switch (M5Switch)
 */
class CDrawable_Switch : public IDrawable {
private:
  // switch width
  int mWidth = 0;
  // switch height
  int mHeight = 0;

  // background color
  int mBg_Color = 0x2222EE;
  // switch color
  int mColor = 0xFAFAFA;

  // on switch callbacks
  std::vector<PyObject *> mOn_Callback;
  // off switch callbacks
  std::vector<PyObject *> mOff_Callback;

  // is checked?
  bool mIs_Checked = false;

public:
  CDrawable_Switch(int x, int y, int width, int height, int bgColor = 0xFAFAFA,
                   int switchColor = 0x2222EE);

  // sets the switch position
  void Set_Position(int x, int y);
  // sets the switch size
  void Set_Size(int w, int h);
  // registers on switch callback
  void Register_On_Callback(PyObject *cb);
  // registers off switch callback
  void Register_Off_Callback(PyObject *cb);
  // set checked state
  void Set_State(bool state);
  // get switch state
  bool Get_State() const;

  virtual void Draw(QPainter &painter) override;
  virtual bool Touched(int x, int y, bool touch = true) override;
};
