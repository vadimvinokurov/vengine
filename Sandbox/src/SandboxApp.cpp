#include <vengine.h>

class Sandbox : public VE::Application {
};


int main()
{
   auto sandbox = new Sandbox();
   sandbox->Run();

   delete sandbox;
   return 0;
}