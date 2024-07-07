#pragma once

namespace VE {
enum class RendererAPI {
   None = 0,
   OpenGL = 1
};


class Renderer {
public:
   inline static RendererAPI GetAPI() { return rendererApi; }

private:
   inline static RendererAPI rendererApi = RendererAPI::OpenGL;
};

}