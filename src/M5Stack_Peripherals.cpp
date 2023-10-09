#include "M5Stack_Peripherals.h"

/******************************** LCD ****************************************/

bool CM5LCDScreen::Is_Changed() const { return mChanged; }

void CM5LCDScreen::Clear_Changed_Flag() { mChanged = false; }

void CM5LCDScreen::Render_To(QPainter &painter) {

  for (auto &drawable : mDrawables)
    drawable->Draw(painter);
}

void CM5LCDScreen::Clean() {
  mDrawables.clear();

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

void CM5LCDScreen::Set_Background_Color(int color) {
  //

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

void CM5LCDScreen::Set_Brightness(int brightness) {
  //

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

void CM5LCDScreen::Print_Text(const std::string &text, int posX, int posY) {
  mDrawables.push_back(std::make_shared<CDrawable_Text>(text, posX, posY, -1));

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

void CM5LCDScreen::Set_Touch_State(bool touching, int x, int y) {
  mTouching = touching;
  mTouch_X = x;
  mTouch_Y = y;

  for (auto dr : mDrawables) {
    if (dr->Touched(x, y, touching)) {
      break;
    }
  }
}

bool CM5LCDScreen::Is_Touching() const { return mTouching; }

int CM5LCDScreen::Get_Touch_X() const { return mTouch_X; }

int CM5LCDScreen::Get_Touch_Y() const { return mTouch_Y; }

/******************************** GPIO ***************************************/

void CM5GPIO::Set_Pin_Mode(int pin, int mode) {
  if (pin < 0 || pin >= GPIO_Count) {
    return;
  }
  mPins[pin].mode = mode;

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

void CM5GPIO::Set_Pin_State(int pin, int state) {
  if (pin < 0 || pin >= GPIO_Count) {
    return;
  }
  mPins[pin].state = state;

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

int CM5GPIO::Get_Pin_Mode(int pin) {
  if (pin < 0 || pin >= GPIO_Count) {
    return 0;
  }
  return mPins[pin].mode;
}

int CM5GPIO::Get_Pin_State(int pin) {
  if (pin < 0 || pin >= GPIO_Count) {
    return 0;
  }
  return mPins[pin].state;
}

bool CM5GPIO::Is_Changed() const { return mChanged; }

void CM5GPIO::Clear_Changed_Flag() { mChanged = false; }

/******************************** Buttons ************************************/

void CM5Buttons::press(Button btn) {
  Btn(btn).state = true;
  Btn(btn).wasPressed = true;
  Btn(btn).wasReleased = false;

  for (auto cb : Btn(btn).wasPressedCallbacks) {
    py::call<void>(cb);
  }
}

void CM5Buttons::release(Button btn) {
  Btn(btn).state = false;
  Btn(btn).wasReleased = true;

  for (auto cb : Btn(btn).wasReleasedCallbacks) {
    py::call<void>(cb);
  }
}

bool CM5Buttons::wasPressed(Button btn) {
  bool was = Btn(btn).wasPressed;
  Btn(btn).wasPressed = false;
  return was;
}

void CM5Buttons::wasPressedRegisterCallback(Button btn, PyObject *obj) {
  Btn(btn).wasPressedCallbacks.push_back(obj);
}

bool CM5Buttons::wasReleased(Button btn) {
  bool was = Btn(btn).wasPressed;
  Btn(btn).wasPressed = false;
  return was;
}

void CM5Buttons::wasReleasedRegisterCallback(Button btn, PyObject *obj) {
  Btn(btn).wasReleasedCallbacks.push_back(obj);
}

bool CM5Buttons::isPressed(Button btn) const { return Btn(btn).state; }

bool CM5Buttons::isReleased(Button btn) const { return !Btn(btn).state; }

/******************************** UART ***************************************/

std::string CM5UART::Read(Channel c, bool deviceSide, int maxCnt) {
  std::string r;

  auto &fifo = FIFO(c, !deviceSide);

  while (!fifo.empty() &&
         (maxCnt <= 0 || r.size() < static_cast<size_t>(maxCnt))) {
    r.push_back(fifo.front());
    fifo.pop();
  }

  return r;
}

std::string CM5UART::Read_Line(Channel c, bool deviceSide) {
  std::string r;

  auto &fifo = FIFO(c, !deviceSide);

  while (!fifo.empty()) {
    r.push_back(fifo.front());

    if (fifo.front() == '\n') {
      fifo.pop();
      break;
    }

    fifo.pop();
  }

  return r;
}

void CM5UART::Write(Channel c, bool deviceSide, const std::string &str) {

  auto &fifo = FIFO(c, deviceSide);
  for (auto ch : str) {
    fifo.push(ch);
  }

  if (deviceSide)
    WidgetEventProxy::Instance()->Emit();
}

bool CM5UART::Empty(Channel c, bool deviceSide) {
  return FIFO(c, !deviceSide).empty();
}

/******************************** Misc ***************************************/

void CM5Misc::Set_Vibration(bool state) {
  mIs_Vibrating = true;

  WidgetEventProxy::Instance()->Emit();
}

bool CM5Misc::Get_Vibration() const { return mIs_Vibrating; }

double CM5Misc::Get_Battery_Voltage() const { return mBattery_Voltage; }

bool CM5Misc::Is_Battery_Charging() const { return mIs_Charging; }

void CM5Misc::Set_Volume(int volume) {
  mVolume = volume;

  WidgetEventProxy::Instance()->Emit();
}

int CM5Misc::Get_Volume() const { return mVolume; }

void CM5Misc::Play_Tone(int tone, int beat_duration) {

  // TODO: simulate tone

  WidgetEventProxy::Instance()->Emit();

  // TODO: wait for given time

  // WidgetEventProxy::Instance()->Emit();
}
