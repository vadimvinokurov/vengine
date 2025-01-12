#include "example_layer.h"

class Sandbox : public VE::Application {
public:
   Sandbox()
   {
      PushLayer(new ExampleLayer());
   }
};


int main()
{
   auto sandbox = new Sandbox();
   sandbox->Run();

   delete sandbox;
   return 0;
}