#pragma once

#include "common/ve_common.h"
#include "ve_event.h"

namespace VE {
	class VE_API KeyEvent : public Event{
	public:
		int GetKeyCode() const {return keyCode;}

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keyCode) : keyCode(keyCode){}
		int keyCode;
	};

	class VE_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int _keyCode, int repeatCount)
			: KeyEvent(_keyCode), repeatCount(repeatCount){}

		int GetRepeatCount() const {return repeatCount;}

		std::string ToSting() const override {
			return std::format("KeyPressedEvent: {} {} repeats", keyCode, repeatCount);
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int repeatCount;
	};

	class VE_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int _keyCode)
			: KeyEvent(_keyCode){}

		std::string ToSting() const override {
			return std::format("KeyReleasedEvent: {}", keyCode);
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};
}