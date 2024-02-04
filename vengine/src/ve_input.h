#pragma once

#include "common/ve_common.h"

namespace VE {
class Input {
public:
   static std::unique_ptr<Input> Create();
   virtual ~Input() = default;

   static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }
   static bool IsKeyMouseButtonPressed(int keycode) { return instance->IsKeyMouseButtonPressedImpl(keycode); }
   static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImpl(); }

protected:
   virtual bool IsKeyPressedImpl(int keycode) = 0;
   virtual bool IsKeyMouseButtonPressedImpl(int keycode) = 0;
   virtual std::pair<float, float> GetMousePositionImpl() = 0;

   inline static Input* instance = nullptr;
};
}