#include <vengine.h>

class Sandbox :public VE::Application {

};

void main() {
	Sandbox* sandbox = new Sandbox();
	sandbox->Run();

	delete sandbox;
}