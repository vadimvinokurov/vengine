#pragma once

#include "common/ve_common.h"
#include "ve_event.h"

namespace VE {
class VE_API MouseMovedEvent : public Event {
public:
   MouseMovedEvent(float x, float y)
      : x(x)
      , y(y)
   {}

   float GetX() const { return x; }
   float GetY() const { return y; }

   std::string ToSting() const override
   {
      return std::format("MouseMovedEvent: {} {}", x, y);
   }

   EVENT_CLASS_TYPE(MouseMoved)
   EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
   float x;
   float y;
};


class VE_API MouseScrolledEvent : public Event {
public:
   MouseScrolledEvent(float xOffset, float yOffset)
      : xOffset(xOffset)
      , yOffset(yOffset)
   {}

   float GetXOffset() const { return xOffset; }
   float GetYOffset() const { return yOffset; }

   std::string ToSting() const override
   {
      return std::format("MouseScrolledEvent: {} {}", GetXOffset(), GetYOffset());
   }

   EVENT_CLASS_TYPE(MouseScrolled)
   EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
   float xOffset;
   float yOffset;
};


class VE_API MouseButtonEvent : public Event {
public:
   int GetButton() const { return button; }

   EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
   MouseButtonEvent(int button)
      : button(button)
   {}

   int button;
};


class VE_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
   MouseButtonPressedEvent(int _button)
      : MouseButtonEvent(_button)
   {}

   std::string ToSting() const override
   {
      return std::format("MouseButtonPressedEvent: {}", button);
   }

   EVENT_CLASS_TYPE(MouseButtonPressed)
};


class VE_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
   MouseButtonReleasedEvent(int _button)
      : MouseButtonEvent(_button)
   {}

   std::string ToSting() const override
   {
      return std::format("MouseButtonReleasedEvent: {}", button);
   }

   EVENT_CLASS_TYPE(MouseButtonReleased)
};
}