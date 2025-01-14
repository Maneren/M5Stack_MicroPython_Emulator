#include <iostream>

#include "BoostPythonDefs.h"
#include "M5Stack_Peripherals.h"
#include "WidgetEventProxy.h"

#include <QBuffer>
#include <QObject>
#include <QtMath>
#include <QtMultimedia/QAudioDeviceInfo>
#include <QtMultimedia/QAudioFormat>
#include <QtMultimedia/QAudioOutput>

/******************************** LCD ****************************************/

bool CM5LCDScreen::Is_Changed() const { return mChanged; }

void CM5LCDScreen::Clear_Changed_Flag() { mChanged = false; }

void CM5LCDScreen::Render_To(QPainter *painter) {
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
    std::cout << "Setting invalid pin number: " << pin << std::endl;
    return;
  }
  mPins[pin].mode = mode;

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

void CM5GPIO::Set_Pin_State(int pin, int state) {
  if (pin < 0 || pin >= GPIO_Count) {
    std::cout << "Setting invalid pin number: " << pin << std::endl;
    return;
  }
  mPins[pin].state = state;

  mChanged = true;
  WidgetEventProxy::Instance()->Emit();
}

int CM5GPIO::Get_Pin_Mode(int pin) {
  if (pin < 0 || pin >= GPIO_Count) {
    std::cout << "Reading invalid pin number: " << pin << std::endl;
    return 0;
  }
  return mPins[pin].mode;
}

int CM5GPIO::Get_Pin_State(int pin) {
  if (pin < 0 || pin >= GPIO_Count) {
    std::cout << "Reading invalid pin number: " << pin << std::endl;
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

const qreal SAMPLING_RATE = 44100;
const qreal FREQ_CONST = (2.0 * M_PI) / SAMPLING_RATE;

static int timeToSize(int ms, const QAudioFormat &format) {
  return (format.sampleSize() / 8) * format.sampleRate() * (ms / 1000);
}

void CM5Misc::Play_Tone(int freq, int duration_ms) {
  QAudioFormat format;
  format.setSampleRate(SAMPLING_RATE);
  format.setChannelCount(1);
  format.setSampleSize(8);
  format.setCodec("audio/pcm");
  format.setByteOrder(QAudioFormat::LittleEndian);
  format.setSampleType(QAudioFormat::SignedInt);

  int sample_count = timeToSize(duration_ms, format);

  QByteArray *buf = new QByteArray();
  buf->resize(sample_count);

  for (int i = 0; i < sample_count; i++) {
    qreal t = (qreal)(freq * i);
    t *= FREQ_CONST;
    t = qSin(t);
    // t *= TG_MAX_VAL; // normalize the value
    (*buf)[i] = (quint8)t;
  }

  QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
  if (!info.isFormatSupported(format)) {
    std::cout << format.codec().toStdString()
              << " not supported by backend, cannot play audio."
                 "Supported formats: "
              << info.supportedCodecs().join(", ").toStdString() << std::endl;
    return;
  }

  QBuffer *input = new QBuffer(buf);
  input->open(QIODevice::ReadOnly);

  QAudioOutput *audio = new QAudioOutput(info, format);
  audio->start(input);

  WidgetEventProxy::Instance()->Emit();
}
