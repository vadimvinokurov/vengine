#include "example_layer.h"
#include "sandbox_2d_layer.h"

class Sandbox : public VE::Application {
public:
   Sandbox()
   {
      //PushLayer(new ExampleLayer());
      PushLayer(new Sandbox2DLayer());
   }
};


int main()
{
   auto sandbox = new Sandbox();
   sandbox->Run();

   delete sandbox;
   return 0;
}