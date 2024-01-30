#include <vengine.h>

class Sandbox : public VE::Application {
};


void main()
{
   auto sandbox = new Sandbox();
   sandbox->Run();

   delete sandbox;
}