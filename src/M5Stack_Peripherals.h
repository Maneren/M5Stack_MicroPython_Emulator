#pragma once

#include <memory>
#include <array>
#include <queue>
#include <vector>
#include <string>

#include "BoostPythonDefs.h"
#include "WidgetEventProxy.h"

#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include "M5Stack_Drawables.h"

/*
 * LCD screen
 */
class CM5LCDScreen {
	private:
		// contents changed
		bool mChanged = false;
		// is there a touch event?
		bool mTouching = false;
		// position of touch (X)
		int mTouch_X = 0;
		// position of touch (Y)
		int mTouch_Y = 0;

		// a vector of all drawables
		std::vector<std::shared_ptr<IDrawable>> mDrawables;

	public:
		static constexpr int Display_Width = 320;
		static constexpr int Display_Height = 240;

		// is the display changed?
		bool Is_Changed() const;
		// clear the changed flag
		void Clear_Changed_Flag();

		// renders all drawables to the given painter/canvas
		void Render_To(QPainter& painter);

		// clears the screen, removes drawables
		void Clean();
		// sets the background color
		void Set_Background_Color(int color);
		// sets screen brightness
		void Set_Brightness(int brightness);

		// prints the text to a given position
		void Print_Text(const std::string& text, int posX, int posY);

		// sets touch state and position
		void Set_Touch_State(bool touching, int x, int y);

		// is there a touch event?
		bool Is_Touching() const;
		// retrieves X position of touch
		int Get_Touch_X() const;
		// retrueves Y position of touch
		int Get_Touch_Y() const;

		// constructs a new drawable to the vector
		template<typename T, typename... TArgs>
		std::shared_ptr<T> Add_Drawable(TArgs&&... args) {
			auto sptr = std::make_shared<T>(std::forward<TArgs>(args)...);

			mDrawables.push_back(sptr);

			return sptr;
		}
};

/*
 * GPIO controller
 */
class CM5GPIO {
	public:
		static constexpr size_t GPIO_Count = 40;

	private:
		// pin state struct
		struct TPin_State {
			int mode;
			int state;
		};

		// array of pin states
		std::array<TPin_State, GPIO_Count> mPins;

		// has something changed?
		bool mChanged = false;

	public:
		// sets pin mode to given mode
		void Set_Pin_Mode(int pin, int mode);
		// sets pin state to given state
		void Set_Pin_State(int pin, int state);
		// retrieves pin mode
		int Get_Pin_Mode(int pin);
		// retrieves pin state
		int Get_Pin_State(int pin);

		// did something change?
		bool Is_Changed() const;
		// clear the changed flag
		void Clear_Changed_Flag();
};

/*
 * M5Stack buttons controller
 */
class CM5Buttons {
	public:
		enum class Button {
			A, // left
			B, // middle
			C, // right

			count
		};

		// convenience macro
		static constexpr size_t Button_Count = static_cast<size_t>(Button::count);

	private:
		// button state structure
		struct TButton_State {
			// when the button was pressed
			std::chrono::time_point<std::chrono::steady_clock> pressTime;
			// when the button was released
			std::chrono::time_point<std::chrono::steady_clock> releaseTime;

			// callbacks for button press
			std::vector<PyObject*> wasPressedCallbacks;
			// callbacks for button release
			std::vector<PyObject*> wasReleasedCallbacks;

			// is pressed?
			bool state = false;
			// was pressed since last time we checked?
			bool wasPressed = false;
			// was released since last time we checked?
			bool wasReleased = false;
		};

		// array of buttons
		std::array<TButton_State, Button_Count> mButtons;

		auto& Btn(Button btn) {
			return mButtons[static_cast<size_t>(btn)];
		}

		auto& Btn(Button btn) const {
			return mButtons[static_cast<size_t>(btn)];
		}

	public:
		// press the button
		void press(Button btn);
		// release the button
		void release(Button btn);

		// was the button pressed since last time we checked?
		bool wasPressed(Button btn);
		// register callback for button press
		void wasPressedRegisterCallback(Button btn, PyObject* obj);
		// was the button released since last time we checked?
		bool wasReleased(Button btn);
		// register callback for button release
		void wasReleasedRegisterCallback(Button btn, PyObject* obj);
		// is the button pressed now?
		bool isPressed(Button btn) const;
		// is the button released now?
		bool isReleased(Button btn) const;
};

/*
 * M5Stack UART controller (all channels)
 */
class CM5UART {
	public:
		enum class Channel {
			Channel_0, // programming UART
			Channel_1, // user UART
			Channel_2, // user UART

			count
		};

		static constexpr size_t UART_Channel_Count = static_cast<size_t>(Channel::count);

	private:
		// FIFOs for transmission
		std::array<std::queue<char>, UART_Channel_Count> mTX_FIFOs;
		// FIFOs for receiving
		std::array<std::queue<char>, UART_Channel_Count> mRX_FIFOs;

		auto& FIFO(Channel c, bool tx) {
			return tx ? mTX_FIFOs[static_cast<size_t>(c)] : mRX_FIFOs[static_cast<size_t>(c)];
		}

		auto& FIFO(Channel c, bool tx) const {
			return tx ? mTX_FIFOs[static_cast<size_t>(c)] : mRX_FIFOs[static_cast<size_t>(c)];
		}

	public:
		// reads a given amount of characters (or all)
		std::string Read(Channel c, bool deviceSide, int maxCnt = 0);
		// reads a line from UART
		std::string Read_Line(Channel c, bool deviceSide);
		// writes a given string to UART
		void Write(Channel c, bool deviceSide, const std::string& str);
		// is the RX FIFO empty?
		bool Empty(Channel c, bool deviceSide);
};
