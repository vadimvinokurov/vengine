#pragma once
#include "ve_pch.h"
#include "common/ve_common.h"

namespace VE {
enum class EventType {
   None = 0,

   WindowClose,
   WindowResize,
   WindowFocus,
   WindowLostFocus,
   WindowMoved,

   AppTick,
   AppUpdate,
   AppRender,

   KeyPressed,
   KeyReleased,
   KeyTyped,

   MouseButtonPressed,
   MouseButtonReleased,
   MouseMoved,
   MouseScrolled
};


enum EventCategory {
   None = 0,
   EventCategoryApplication = BIT(0),
   EventCategoryInput = BIT(1),
   EventCategoryKeyboard = BIT(2),
   EventCategoryMouse = BIT(3),
   EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                                 \
   static EventType GetStaticType() { return EventType::##type; }              \
   virtual EventType GetEventType() const override { return GetStaticType(); } \
   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
   virtual int GetCategoryFlags() const override { return category; }


class Event {
   friend class EventDispatcher;

public:
   virtual ~Event() = default;
   virtual EventType GetEventType() const = 0;
   virtual const char* GetName() const = 0;
   virtual int GetCategoryFlags() const = 0;
   virtual std::string ToSting() const { return GetName(); }

   bool IsInCategory(EventCategory category) const
   {
      return GetCategoryFlags() & category;
   }

   bool IsHandled() const { return isHandled; }

protected:
   bool isHandled = false;
};


class EventDispatcher {
   template <typename T>
   using EventFn = std::function<bool(T&)>;

public:
   EventDispatcher(Event& event)
      : event(event)
   {}

   template <typename T>
   bool Dispatch(EventFn<T> func)
   {
      if (event.GetEventType() != T::GetStaticType()) {
         return false;
      }

      event.isHandled = func(static_cast<T&>(event));
      return true;
   }

private:
   Event& event;
};


inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
   return os << e.ToSting();
}


using EventCallback = std::function<void(Event&)>;
} //namespace VE

#define MAKE_EVENT_DISPATCHER(event) EventDispatcher dispatcher(event)
#define DISPATCH_EVENT(HOST_CLASS, EVENT_TYPE) dispatcher.Dispatch<EVENT_TYPE>(std::bind(&HOST_CLASS::On##EVENT_TYPE, this, std::placeholders::_1))