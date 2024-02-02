#pragma once
#include "ve_pch.h"
#include "common/ve_common.h"
#include "events/ve_event.h"

namespace VE {
class VE_API Layer {
public:
   Layer(std::string name = "Default layer")
      : dbgName(std::move(name))
   {}

   virtual ~Layer() = default;

   virtual void OnAttach() {}
   virtual void OnDetach() {}
   virtual void OnUpdate() {}
   virtual void OnEvent(Event& event) {}

   inline const std::string& GetName() const { return dbgName; }

protected:
   std::string dbgName;
};
}