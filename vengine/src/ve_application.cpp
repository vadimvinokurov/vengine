#include "ve_pch.h"

#include "ve_application.h"
#include "ve_log.h"
#include "events/ve_application_event.h"

using namespace VE;

Application::Application() {
	VE::Log::Init();
}

Application::~Application() {
}

void Application::Run() {
	WindowResizeEvent e(1233, 111);
	VE_TRACE(e);
}