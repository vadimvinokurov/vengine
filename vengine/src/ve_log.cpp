#include "ve_log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace VE;

void Log::Init(){
    spdlog::set_pattern("%^[%T] %n: %v%$");
    engineLogger = spdlog::stdout_color_mt("vengine");
    engineLogger->set_level(spdlog::level::trace);
    clientLogger = spdlog::stdout_color_mt("app");
    clientLogger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Log::GetEngineLogger(){
    return engineLogger;
}

std::shared_ptr<spdlog::logger>& Log::GetClientLogger(){
    return clientLogger;
}