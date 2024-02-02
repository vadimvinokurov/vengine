-- premake5.lua
workspace "vengine"
	architecture "x64"
	configurations 
	{
		"Debug",
		"Release",
		"Profile",
		"Retail"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "vengine/lib3dpart/GLFW/include"

include "vengine/lib3dpart/GLFW"

project "vengine"
	location "vengine"
	kind "SharedLib"
	staticruntime "off"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "ve_pch.h"
	pchsource "vengine/src/ve_pch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/lib3dpart/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		defines
		{
			"VE_PLATFORM_WINDOWS",
			"VE_BUILD_DLL",
			"VE_ENGINE_REGION"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "VE_DEBUG"
		runtime "Debug"
		optimize "Off"
        symbols "On"
		
	filter "configurations:Release"
		defines "VE_RELEASE"
		runtime "Release"
		optimize "speed"
		
	filter "configurations:Profile"
		defines "VE_PROFILE"
		runtime "Release"
		optimize "speed"
	
	filter "configurations:Retail"
		defines "VE_RETAIL"
		runtime "Release"
		optimize "speed"
        symbols "off"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"vengine/lib3dpart/spdlog/include",
		"vengine/src"
	}
	
	links
	{
		"vengine"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		defines
		{
			"VE_PLATFORM_WINDOWS",
		}
	
	filter "configurations:Debug"
		defines "VE_DEBUG"
		runtime "Debug"
		optimize "Off"
        symbols "On"
		
	filter "configurations:Release"
		defines "VE_RELEASE"
		runtime "Release"
		optimize "speed"
		
	filter "configurations:Profile"
		defines "VE_PROFILE"
		runtime "Release"
		optimize "speed"
	
	filter "configurations:Retail"
		defines "VE_RETAIL"
		runtime "Release"
		optimize "speed"
        symbols "off"
