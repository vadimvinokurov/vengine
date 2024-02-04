#pragma once

namespace VE {
class GraphicsContext {
public:
   virtual ~GraphicsContext() = default;
   virtual void SwapBuffers() = 0;
};
}