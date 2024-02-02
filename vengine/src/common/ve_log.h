#pragma once

#include "common/ve_common.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


namespace VE {
class VE_API Log {
public:
   static void Init();
   inline static std::shared_ptr<spdlog::logger>& GetEngineLogger();
   inline static std::shared_ptr<spdlog::logger>& GetClientLogger();

private:
   inline static std::shared_ptr<spdlog::logger> clientLogger;
   inline static std::shared_ptr<spdlog::logger> engineLogger;
};
} //namespace VE

#ifdef VE_ENGINE_REGION
#define VE_CRITICAL(...) ::VE::Log::GetEngineLogger()->critical(__VA_ARGS__)
#define VE_ERROR(...) ::VE::Log::GetEngineLogger()->error(__VA_ARGS__)
#define VE_WARNING(...) ::VE::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define VE_INFO(...) ::VE::Log::GetEngineLogger()->info(__VA_ARGS__)
#define VE_TRACE(...) ::VE::Log::GetEngineLogger()->trace(__VA_ARGS__)
#else
#define VE_CRITICAL(...) ::VE::Log::GetClientLogger()->critical(__VA_ARGS__)
#define VE_ERROR(...) ::VE::Log::GetClientLogger()->error(__VA_ARGS__)
#define VE_WARNING(...) ::VE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VE_INFO(...) ::VE::Log::GetClientLogger()->info(__VA_ARGS__)
#define VE_TRACE(...) ::VE::Log::GetClientLogger()->trace(__VA_ARGS__)
#endif