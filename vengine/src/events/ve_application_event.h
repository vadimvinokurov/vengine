#pragma once
#include "ve_pch.h"
#include "common/ve_common.h"
#include "ve_event.h"

namespace VE {
class VE_API WindowResizeEvent : public Event {
public:
   WindowResizeEvent(unsigned int width, unsigned int height)
      : width(width)
      , height(height)
   {}

   unsigned int GetWidth() const { return width; }
   unsigned int GetHeight() const { return height; }

   std::string ToSting() const override
   {
      return std::format("WindowResizeEvent: {} {}", width, height);
   }

   EVENT_CLASS_TYPE(WindowResize)
   EVENT_CLASS_CATEGORY(EventCategoryApplication)
protected:
   unsigned int width;
   unsigned int height;
};


class VE_API WindowCloseEvent : public Event {
public:
   WindowCloseEvent() = default;

   EVENT_CLASS_TYPE(WindowClose)
   EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


class VE_API AppTickEvent : public Event {
public:
   AppTickEvent() = default;

   EVENT_CLASS_TYPE(AppTick)
   EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


class VE_API AppUpdateEvent : public Event {
public:
   AppUpdateEvent() = default;

   EVENT_CLASS_TYPE(AppUpdate)
   EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


class VE_API AppRenderEvent : public Event {
public:
   AppRenderEvent() = default;

   EVENT_CLASS_TYPE(AppRender)
   EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
}