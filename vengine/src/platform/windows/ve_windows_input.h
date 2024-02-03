#pragma once
#include "ve_input.h"

namespace VE {

class VE_API WindowsInput : public Input {
public:
   WindowsInput();

protected:
   virtual bool IsKeyPressedImpl(int keycode) override;
   virtual bool IsKeyMouseButtonPressedImpl(int keycode) override;
   virtual std::pair<float, float> GetMousePositionImpl() override;
};

} //namespace VE