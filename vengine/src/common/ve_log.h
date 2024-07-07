#pragma once

#include "common/ve_common.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace VE {
class Log final {
public:
   Log();
   static Log* Get() { return instance; }
   static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return Get()->engineLogger; }
   static std::shared_ptr<spdlog::logger>& GetClientLogger() { return Get()->clientLogger; }

private:
   std::shared_ptr<spdlog::logger> clientLogger;
   std::shared_ptr<spdlog::logger> engineLogger;

   inline static Log* instance = nullptr;
};
} //namespace VE

#ifdef VE_ENGINE_REGION
#define VE_LOG_CRITICAL(...) ::VE::Log::GetEngineLogger()->critical(__VA_ARGS__)
#define VE_LOG_ERROR(...) ::VE::Log::GetEngineLogger()->error(__VA_ARGS__)
#define VE_LOG_WARNING(...) ::VE::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define VE_LOG_MSG(...) ::VE::Log::GetEngineLogger()->info(__VA_ARGS__)
#define VE_LOG_TRACE(...) ::VE::Log::GetEngineLogger()->trace(__VA_ARGS__)
#else
#define VE_LOG_CRITICAL(...) ::VE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define VE_LOG_ERROR(...) ::VE::Log::GetClientLogger()->error(__VA_ARGS__)
#define VE_LOG_WARNING(...) ::VE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VE_LOG_MSG(...) ::VE::Log::GetClientLogger()->info(__VA_ARGS__)
#define VE_LOG_TRACE(...) ::VE::Log::GetClientLogger()->trace(__VA_ARGS__)
#endif