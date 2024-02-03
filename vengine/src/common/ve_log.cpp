#include "ve_pch.h"
#include "ve_assert.h"
#include "ve_log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

using namespace VE;


Log::Log()
{
   ASSERT_MSG(!instance, "Instance already registered");
   instance = this;

   spdlog::set_pattern("%^[%T] %n: %v%$");
   engineLogger = spdlog::stdout_color_mt("vengine");
   engineLogger->set_level(spdlog::level::trace);
   clientLogger = spdlog::stdout_color_mt("app");
   clientLogger->set_level(spdlog::level::trace);
}